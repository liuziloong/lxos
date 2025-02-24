/*
 * Copyright 2023 Andy andrew.lxos@gmail.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "tlsf.h"

#include "mm/mm.h"
#include "port/mm.h"

#include "kernel/thread.h"

#include "lx/bitmap.h"
#include "lx/log.h"
#include "lx/misc.h"
#include "lx/string.h"

extern thread_t *g_current;

tlsf_manager_t g_tlsf_manager;

#ifdef CONFIG_LX_MM_DEBUG_CHECK
tlsf_block_head_t *g_tlsf_used_block = NULL;
#endif

#ifdef CONFIG_LX_MM_DEBUG_BITMAP_SHOW

static void _tlsf_debug_bitmap_show(void)
{
    int fl = 0;
    int sl = 0;

    LOG("FL-BITMAP = 0x%x\r\n\n", g_tlsf_manager.fl_bitmap);
    LOG("FL : SL-BITMAP\t");

    for (sl = 0; sl < TLSF_SL_INDEX; sl++) {
        LOG("SL-%d\t", sl);
    }

    LOG("\r\n");

    for (fl = 0; fl < TLSF_FL_INDEX; fl++) {
        if (fl < 10) {
            LOG("0%d : 0x%x :\t", fl, g_tlsf_manager.sl_bitmap[fl]);
        } else {
            LOG("%d : 0x%x :\t", fl, g_tlsf_manager.sl_bitmap[fl]);
        }

        for (sl = 0; sl < TLSF_SL_INDEX; sl++) {
            if (g_tlsf_manager.blocks[fl][sl] != NULL) {
                LOG("%x\t", g_tlsf_manager.blocks[fl][sl]->size);
            } else {
                LOG("0\t");
            }
        }
        LOG("\r\n");
    }

    LOG("\r\n");
}

#endif /* CONFIG_LX_MM_DEBUG_BITMAP_SHOW */

#ifdef CONFIG_LX_MM_DEBUG_CHECK

static void _tlsf_debug_free_block_check(void)
{
    int fl = 0;
    int sl = 0;

    tlsf_block_head_t *cur = NULL;

    LOGD("......MM-TLSF: Free Block Check Now......\n");

    for (fl = 0; fl < TLSF_FL_INDEX; fl++) {
        for (sl = 0; sl < TLSF_SL_INDEX; sl++) {
            if (g_tlsf_manager.blocks[fl][sl] != NULL) {
                LOGD("MM-TLSF: Free Block Check. FL = %d, SL = %d.\n", fl, sl);
                cur = g_tlsf_manager.blocks[fl][sl];
                do {
                    if (cur->magic != TLSF_MAGIC) {
                        LOGE("MM-TLSF: Free Block Magic Error!!! ADDR = 0x%x, FL = %d, SL = %d.\n", cur, fl, sl);
                        return;
                    }

                    LOGD("MM-TLSF: Free Block Info: 0x%x ~ %d(0x%x).\n", cur, cur->size, cur->size);
                    cur = container_of(cur->list.next, tlsf_block_head_t, list);
                } while (&(g_tlsf_manager.blocks[fl][sl]->list) != &(cur->list));
            }
        }
    }
}

static void _tlsf_debug_used_block_check(void)
{
    int *i = NULL;

    size_t size = 0;

    tlsf_block_head_t *cur = NULL;
    tlsf_block_end_t  *end = NULL;

    if (g_tlsf_used_block == NULL) {
        return;
    }

    LOGD("......MM-TLSF: Used Block Check Now......\n");

    cur = g_tlsf_used_block;
    end = (tlsf_block_end_t *)((int)cur + sizeof(tlsf_block_head_t) + cur->size);

    do {
        if ((cur->magic != TLSF_MAGIC) && (end->magic == TLSF_MAGIC)) {
            LOGE("MM-TLSF: Used Block Head Magic Error!!! ADDR = 0x%x.\n", cur);
            return;
        } else if ((cur->magic == TLSF_MAGIC) && (end->magic != TLSF_MAGIC)) {
            LOGE("MM-TLSF: Used Block End Magic Error!!! ADDR = 0x%x.\n", cur);
            return;
        } else if ((cur->magic != TLSF_MAGIC) && (end->magic != TLSF_MAGIC)) {
            LOGE("MM-TLSF: Used Head&End Magic Error!!! ADDR = 0x%x.\n", cur);
            return;
        }

        size = 0;
        for (i = (int *)((int)cur + sizeof(tlsf_block_head_t)); *i != TLSF_DYES; i++) {
            size += (1 << TLSF_ALIGN_LOG2);
        }

        LOGD("MM-TLSF: Used Block Info: 0x%x, Used / Total = %d(0x%x) / %d(0x%x).\n", cur, size, size, cur->size, cur->size);
        cur = container_of(cur->list.next, tlsf_block_head_t, list);
    } while (&(g_tlsf_used_block->list) != &(cur->list));
}

static void _tlsf_debug_used_block_insert(tlsf_block_head_t *block)
{
    if (g_tlsf_used_block == NULL) {
        g_tlsf_used_block = block;
        return;
    }

    list_insert_before(&(g_tlsf_used_block->list), &(block->list));
}

static void _tlsf_debug_used_block_remove(tlsf_block_head_t *block)
{
    if (block->list.next == &(block->list)) {
        g_tlsf_used_block = NULL;
    } else {
        g_tlsf_used_block = container_of(block->list.next, tlsf_block_head_t, list);

        list_remove(&(block->list));
    }
}

#endif /* CONFIG_LX_MM_DEBUG_CHECK */

static void _tlsf_block_mapping(size_t size, int *fl, int *sl)
{
    int tmp = bitmap_fls(size);

    *fl = tmp - TLSF_FL_SHIFT;
    *sl = ((~(1 << tmp)) & size) >> (tmp - TLSF_SL_INDEX_LOG2);
}

static void _tlsf_free_block_insert(tlsf_block_head_t *block)
{
    int fl = 0;
    int sl = 0;

    size_t size = block->size;

    tlsf_block_head_t *cur = NULL;

    _tlsf_block_mapping(size, &fl, &sl);

    g_tlsf_manager.fl_bitmap     |= 1 << fl;
    g_tlsf_manager.sl_bitmap[fl] |= 1 << sl;

    cur = g_tlsf_manager.blocks[fl][sl];

    LOGD("MM-TLSF: Free Block Insert: FL = %d, SL = %d.\n", fl, sl);

    if (cur == NULL) {
        LOGD("MM-TLSF: This is the first region or block.\n");

        g_tlsf_manager.blocks[fl][sl] = block;

        return;
    }

    do {
        if (block->size <= cur->size) {
            if (&(cur->list) == &(g_tlsf_manager.blocks[fl][sl]->list)) {
                list_insert_before(&(cur->list), &(block->list));

                g_tlsf_manager.blocks[fl][sl] = block;

                return;
            }

            list_insert_before(&(cur->list), &(block->list));

            return;
        }

        cur = container_of(cur->list.next, tlsf_block_head_t, list);
    } while (cur != g_tlsf_manager.blocks[fl][sl]);

    /* block is the largest */
    list_insert_before(&(cur->list), &(block->list));
}

static void _tlsf_free_block_remove(tlsf_block_head_t *block, int fl, int sl)
{
    if (block->list.next == &(block->list)) {
        g_tlsf_manager.sl_bitmap[fl]  &= ~(1 << sl);
        if (g_tlsf_manager.sl_bitmap[fl] == 0) {
            g_tlsf_manager.fl_bitmap &= ~(1 << fl);
        }
        g_tlsf_manager.blocks[fl][sl]  = NULL;
    } else {
        g_tlsf_manager.blocks[fl][sl] = container_of(block->list.next, tlsf_block_head_t, list);;
        list_remove(&(block->list));
    }
}

static void *_tlsf_block_split(tlsf_block_head_t *block, size_t size)
{
    void *mem = NULL;

    size_t total = block->size;

    tlsf_block_end_t  *end  = NULL;
    tlsf_block_head_t *head = NULL;

    /* NEW END of The Front Block */
#ifdef CONFIG_LX_MM_DEBUG_CHECK
    end = (tlsf_block_end_t *)((int)block + sizeof(tlsf_block_head_t) + size);
#else
    end = (tlsf_block_end_t *)((int)block + sizeof(tlsf_block_head_t) + size - sizeof(list_t));
#endif

    memset((void *)end, 0, sizeof(tlsf_block_end_t));

#ifdef CONFIG_LX_MM_DEBUG_MAGIC
    end->magic = TLSF_MAGIC;
#endif

    end->self = (tlsf_block_head_t *)((int)block | TLSF_BLOCK_USED);

    /* NEW HEAD of The Back Block */
    head = (tlsf_block_head_t *)((int)end + sizeof(tlsf_block_end_t));

    memset((void *)head, 0, sizeof(tlsf_block_head_t));

#ifdef CONFIG_LX_MM_DEBUG_MAGIC
    head->magic = TLSF_MAGIC;
#endif

#ifdef CONFIG_LX_MM_DEBUG_TID
    head->tid = g_current->tid;
#endif

#ifdef CONFIG_LX_MM_DEBUG_CHECK
    head->size = total - size - sizeof(tlsf_block_head_t) - sizeof(tlsf_block_end_t);
#else
    head->size = total - size - sizeof(tlsf_block_head_t) - sizeof(tlsf_block_end_t) + sizeof(list_t);
#endif

    list_init(&(head->list));

    /* Insert The Left Block */
    _tlsf_free_block_insert(head);

    block->size = size;

#ifdef CONFIG_LX_MM_DEBUG_CHECK
    mem = (void *)((int)block + sizeof(tlsf_block_head_t));
#else
    mem = (void *)((int)block + sizeof(tlsf_block_head_t) - sizeof(list_t));
#endif

    return mem;
}

static tlsf_block_head_t *_tlsf_block_merge(tlsf_block_head_t *block)
{
    int fl = 0;
    int sl = 0;

    tlsf_block_head_t *head = NULL;
    tlsf_block_end_t  *end  = NULL;

    /* prev block */
    end = (tlsf_block_end_t *)((int)block - sizeof(tlsf_block_end_t));

    if ((*((int *)end) != TLSF_REGION_MAGIC) && ((int)(end->self) & TLSF_BLOCK_FREE)) {
#ifdef CONFIG_LX_MM_DEBUG_MAGIC
        if (end->magic != TLSF_MAGIC) {
            LOGE("MM-TLSF: Block Merge Error: prev-end magic wrong!!! End Addr = 0x%x\n", end);
            return NULL;
        }
#endif

        head = (tlsf_block_head_t *)((int)(end->self) & TLSF_BLOCK_MASK);

        _tlsf_block_mapping(head->size, &fl, &sl);

        _tlsf_free_block_remove(head, fl, sl);

#ifdef CONFIG_LX_MM_DEBUG_CHECK
        head->size += sizeof(tlsf_block_end_t) + sizeof(tlsf_block_head_t) + block->size;
#else
        head->size += sizeof(tlsf_block_end_t) + sizeof(tlsf_block_head_t) + block->size - sizeof(list_t);
#endif

#ifdef CONFIG_LX_MM_DEBUG_CHECK
       end = (tlsf_block_end_t *)((int)head + sizeof(tlsf_block_head_t) + head->size);
#else
       end = (tlsf_block_end_t *)((int)head + sizeof(tlsf_block_head_t) + head->size - sizeof(list_t));
#endif

       end->self = (tlsf_block_head_t *)(((int)(head) & TLSF_BLOCK_MASK) | TLSF_BLOCK_FREE);

       block = head;
    }

    /* next block */
#ifdef CONFIG_LX_MM_DEBUG_CHECK
    head = (tlsf_block_head_t *)((int)block + sizeof(tlsf_block_head_t)
           + block->size + sizeof(tlsf_block_end_t));
#else
    head = (tlsf_block_head_t *)((int)block + sizeof(tlsf_block_head_t)
           + block->size + sizeof(tlsf_block_end_t) - sizeof(list_t));
#endif

    if (*((int *)head) == TLSF_REGION_MAGIC) {
        LOGD("MM-TLSF: Block Merge: This is the end of the region.\n");
        return NULL;
    }

#ifdef CONFIG_LX_MM_DEBUG_MAGIC
    if (head->magic != TLSF_MAGIC) {
        LOGE("MM-TLSF: Block Merge Error: next-head magic wrong!!! End Addr = 0x%x\n", head);
        return NULL;
    }
#endif

#ifdef CONFIG_LX_MM_DEBUG_CHECK
    end = (tlsf_block_end_t *)((int)head + sizeof(tlsf_block_head_t) + head->size);
#else
    end = (tlsf_block_end_t *)((int)head + sizeof(tlsf_block_head_t) + head->size - sizeof(list_t));
#endif

#ifdef CONFIG_LX_MM_DEBUG_MAGIC
    if (end->magic != TLSF_MAGIC) {
        LOGE("MM-TLSF: Block Merge Error: next-end magic wrong!!! End Addr = 0x%x\n", end);
        return NULL;
    }
#endif

    if ((int)(end->self) & TLSF_BLOCK_FREE) {
        _tlsf_block_mapping(head->size, &fl, &sl);

        _tlsf_free_block_remove(head, fl, sl);

#ifdef CONFIG_LX_MM_DEBUG_CHECK
        block->size += sizeof(tlsf_block_end_t) + sizeof(tlsf_block_head_t) + head->size;
#else
        block->size += sizeof(tlsf_block_end_t) + sizeof(tlsf_block_head_t) + head->size - sizeof(list_t);
#endif

        end->self = (tlsf_block_head_t *)(((int)(block) & TLSF_BLOCK_MASK) | TLSF_BLOCK_FREE);
    }

    return block;
}

static tlsf_block_head_t *_tlsf_block_find_suitable(size_t size, int *fl, int *sl)
{
    int f = 0;
    int s = 0;

    uint32_t fl_bitmap = 0;
    uint32_t sl_bitmap = 0;

    tlsf_block_head_t *cur = NULL;

    _tlsf_block_mapping(size, &f, &s);

    fl_bitmap = g_tlsf_manager.fl_bitmap & (~0U << f);
    *fl       = bitmap_ffs(fl_bitmap);
    if (*fl > f) {
        sl_bitmap = g_tlsf_manager.sl_bitmap[*fl];
        *sl       = bitmap_ffs(sl_bitmap);

        return g_tlsf_manager.blocks[*fl][*sl];
    } else if (*fl == f) {
        sl_bitmap = g_tlsf_manager.sl_bitmap[*fl] & (~0U << s);
        *sl       = bitmap_ffs(sl_bitmap);
        if (*sl > s) {
            return g_tlsf_manager.blocks[*fl][*sl];
        } else if (*sl == s) {
            cur = g_tlsf_manager.blocks[*fl][*sl];
            while (size > cur->size) {
                cur = container_of(cur->list.next, tlsf_block_head_t, list);
                if (cur == g_tlsf_manager.blocks[*fl][*sl]) {
                    break;
                }
            }

            if (size < cur->size) {
                return cur;
            }
        }

        fl_bitmap = g_tlsf_manager.fl_bitmap & (~0U << (f + 1));
        *fl       = bitmap_ffs(fl_bitmap);
        if (*fl > f) {
            sl_bitmap = g_tlsf_manager.sl_bitmap[f];
            *sl       = bitmap_ffs(sl_bitmap);

            return g_tlsf_manager.blocks[*fl][*sl];
        }
    }

    return NULL;
}

static void _tlsf_region_insert(void *mem, size_t size)
{
    tlsf_block_head_t *head = (tlsf_block_head_t *)mem;
    tlsf_block_end_t  *end  = (tlsf_block_end_t *)((int)mem + size - sizeof(tlsf_block_end_t));

    memset(head, 0, sizeof(tlsf_block_head_t));

#ifdef CONFIG_LX_MM_DEBUG_MAGIC
    head->magic = TLSF_MAGIC;
#endif

#ifdef CONFIG_LX_MM_DEBUG_TID
    head->tid = 0; /* mem_init called by INIT-THREAD */
#endif

#ifdef CONFIG_LX_MM_DEBUG_CHECK
    head->size = size - sizeof(tlsf_block_head_t) - sizeof(tlsf_block_end_t);
#else
    head->size = size - sizeof(tlsf_block_head_t) - sizeof(tlsf_block_end_t) + sizeof(list_t);
#endif

    list_init(&(head->list));

    memset(end, 0, sizeof(tlsf_block_end_t));

#ifdef CONFIG_LX_MM_DEBUG_MAGIC
    end->magic = TLSF_MAGIC;
#endif

    end->self = (tlsf_block_head_t *)((int)head | TLSF_BLOCK_FREE);

#ifdef CONFIG_LX_MM_DEBUG_BITMAP_SHOW
    LOG("MM-TLSF: BLOCK-INFO: Head = 0x%x, End = 0x%x, Size = %d ~ 0x%x (exclude head and end).\r\n\n",
        head, end, head->size, head->size);
#endif

    _tlsf_free_block_insert(head);
}

void tlsf_init(void)
{
    int num = 0;

    void *head = NULL; /* region head: sizeof(tlsf_block_end_t)*/
    void *end  = NULL; /* region end : 4 bytes */

    LOGD("MM-TLSF: REGION_NUM = %d, TLSF_FL_INDEX = %d, TLSF_SL_INDEX = %d.\n\n",
         g_mm_region_num, TLSF_FL_INDEX, TLSF_SL_INDEX);

    for (num = 0; num < g_mm_region_num; num++) {
#ifdef CONFIG_LX_MM_DEBUG_BITMAP_SHOW
        LOG("MM-TLSF: REGION = %d / %d\r\n\n", num + 1, g_mm_region_num);
        LOG("MM-TLSF: Region-Start = 0x%x, Region-Size = %d ~ 0x%x (include head and end).\r\n\n",
            g_mm_region[num].addr, g_mm_region[num].size, g_mm_region[num].size);
#endif

        head = g_mm_region[num].addr;
        end  = (void *)((int)(g_mm_region[num].addr) + g_mm_region[num].size - (1 << TLSF_ALIGN_LOG2));

        *((int *)head) = TLSF_REGION_MAGIC;
        *((int *)end)  = TLSF_REGION_MAGIC;

        g_mm_region[num].addr  = (void *)((int)(g_mm_region[num].addr) + sizeof(tlsf_block_end_t));
        g_mm_region[num].size -= (sizeof(tlsf_block_end_t) + (1 << TLSF_ALIGN_LOG2));

        _tlsf_region_insert(g_mm_region[num].addr, g_mm_region[num].size);

#ifdef CONFIG_LX_MM_DEBUG_BITMAP_SHOW
        _tlsf_debug_bitmap_show();
#endif
    }
}

void *tlsf_malloc(size_t size)
{
    int fl = 0;
    int sl = 0;

    void *mem = NULL;

    size_t real_size = 0;

    tlsf_block_head_t *block = NULL;
    tlsf_block_end_t  *end   = NULL;

    LOGD("......MM-TLSF: Tlsf Malloc Now......\n");

    real_size = MM_ALIGN_UP(size);
    if (real_size > TLSF_BLOCK_MAX) {
        LOGW("MM-TLSF: Malloc Size Error!!! Size = %d.\n", real_size);
        return NULL;
    } else if (real_size < TLSF_BLOCK_MIN) {
        real_size = TLSF_BLOCK_MIN;
    }

    block = _tlsf_block_find_suitable(real_size, &fl, &sl);
    if (block == NULL) {
        LOGW("MM-TLSF: Malloc Error!!!\n");
        return NULL;
    }

    _tlsf_free_block_remove(block, fl, sl);

#ifdef CONFIG_LX_MM_DEBUG_CHECK
    if ((block->size - real_size - sizeof(tlsf_block_head_t) - sizeof(tlsf_block_end_t)) < TLSF_BLOCK_MIN ) {
        real_size = block->size;

        end       = (tlsf_block_end_t *)((int)block + sizeof(tlsf_block_head_t) + real_size);
        end->self = (tlsf_block_head_t *)(((int)block & TLSF_BLOCK_MASK) | TLSF_BLOCK_USED);

        mem = (void *)((int)block + sizeof(tlsf_block_head_t));
    } else {
        mem = _tlsf_block_split(block, real_size);
    }
#else
    if ((block->size - real_size - sizeof(tlsf_block_head_t) - sizeof(tlsf_block_end_t) + sizeof(list_t)) < TLSF_BLOCK_MIN ) {
        real_size = block->size;

        end       = (tlsf_block_end_t *)((int)block + sizeof(tlsf_block_head_t) + real_size - sizeof(list_t));
        end->self = (tlsf_block_head_t *)(((int)block & TLSF_BLOCK_MASK) | TLSF_BLOCK_USED);

        mem = (void *)((int)block + sizeof(tlsf_block_head_t) - sizeof(list_t));
    } else {
        mem = _tlsf_block_split(block, real_size);
    }
#endif

    if (mem != NULL) {
#ifdef CONFIG_LX_MM_DEBUG_CHECK
       memset(mem, TLSF_DYE, real_size);

        _tlsf_debug_used_block_insert((tlsf_block_head_t *)((int)mem - sizeof(tlsf_block_head_t)));
#endif
    }

    return mem;
}

void *tlsf_zalloc(size_t size)
{
    void *mem = NULL;

    tlsf_block_head_t *head = NULL;

    LOGD("......MM-TLSF: Tlsf Zalloc Now......\n");

    mem = tlsf_malloc(size);

    if (mem != NULL) {
#ifdef CONFIG_LX_MM_DEBUG_CHECK
        head = (tlsf_block_head_t *)((int)mem - sizeof(tlsf_block_head_t *));
#else
        head = (tlsf_block_head_t *)((int)mem - sizeof(tlsf_block_head_t *) + sizeof(list_t));
#endif
        memset(mem, 0, head->size);
    }

    return mem;
}

void *tlsf_realloc(void *oldmem, size_t size)
{
    void *mem = NULL;

    LOGD("......MM-TLSF: Tlsf Realloc Now......\n");

    if ((oldmem == NULL) || (size == 0)) {
        LOGE("MM-TLSF: Realloc Input Error!!!\n");
        return NULL;
    }

    mem = tlsf_malloc(size);
    if (mem == NULL) {
        LOGE("MM-TLSF: Realloc Error!!!\n");
        return NULL;
    }

    memcpy(mem, oldmem, size);

    tlsf_free(oldmem);

    return mem;
}

void tlsf_free(void *mem)
{
    tlsf_block_head_t *head  = NULL;
    tlsf_block_end_t  *end   = NULL;

    if (mem == NULL) {
        LOGE("MM-TLSF: Free Error: mem == NULL!!!\n");
        return;
    }

    LOGD("......MM-TLSF: Tlsf Free Now......\n");

#ifdef CONFIG_LX_MM_DEBUG_CHECK
    head = (tlsf_block_head_t *)((int)mem - sizeof(tlsf_block_head_t));
#else
    head = (tlsf_block_head_t *)((int)mem - sizeof(tlsf_block_head_t) + sizeof(list_t));
#endif

#ifdef CONFIG_LX_MM_DEBUG_MAGIC
    if (head->magic != TLSF_MAGIC) {
        LOGE("MM-TLSF: Free Error: head magic wrong!!! Head Addr = 0x%x\n", head);
        return;
    }
#endif

    end = (tlsf_block_end_t *)((int)mem + head->size);

#ifdef CONFIG_LX_MM_DEBUG_MAGIC
    if (end->magic != TLSF_MAGIC) {
        LOGE("MM-TLSF: Free Error: end magic wrong!!! End Addr = 0x%x\n", end);
        return;
    }
#endif

#ifdef CONFIG_LX_MM_DEBUG_CHECK
    _tlsf_debug_used_block_remove(head);
#endif

    end->self = (tlsf_block_head_t *)(((int)(end->self) & TLSF_BLOCK_MASK) | TLSF_BLOCK_FREE);

    head = _tlsf_block_merge(head);
    if (head == NULL) {
        return;
    }

    _tlsf_free_block_insert(head);

    mem = NULL;
}

void tlsf_check(void)
{
#ifdef CONFIG_LX_MM_DEBUG_CHECK
    _tlsf_debug_free_block_check();
    _tlsf_debug_used_block_check();
#else
    LOGW("MM-TLSF: Check Not Support!!!\n");
#endif
}

