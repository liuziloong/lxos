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

#ifndef MM_TLSF_H
#define MM_TLSF_H

#include "lx/list.h"
#include "lx/types.h"

#include "mm/mm.h"

#define TLSF_ALIGN_LOG2 MM_ALIGN_LOG2 /* 32-bit architecture: MM_ALIGN_LOG2 = 2 */

#define TLSF_SL_INDEX_LOG2 4

#define TLSF_FL_SHIFT (TLSF_SL_INDEX_LOG2 + TLSF_ALIGN_LOG2)

#define TLSF_FL_INDEX ((MM_REGION_SIZE_MAX_LOG2 - 1) - TLSF_FL_SHIFT + 1) /* First level index count */
#define TLSF_SL_INDEX (1 << TLSF_SL_INDEX_LOG2)                           /* Second level index count */

#define TLSF_BLOCK_FREE  0x00000001
#define TLSF_BLOCK_USED  0x00000002
#define TLSF_BLOCK_MASK ~(TLSF_BLOCK_FREE | TLSF_BLOCK_USED)

#define TLSF_REGION_MAGIC 0X4C584C58 /* "LXLX" = 0X4C584C58 */

#define TLSF_DYE   0X58       /* 'X' = 0X58 */
#define TLSF_DYES  0X58585858 /* "XXXX" = 0X58585858 */
#define TLSF_MAGIC 0X4C584F53 /* "LXOS" = 0X4C584F53 */

#define TLSF_BLOCK_MIN (1 << TLSF_FL_SHIFT)
#define TLSF_BLOCK_MAX (MM_REGION_SIZE_MAX - sizeof(tlsf_block_head_t) - sizeof(tlsf_block_end_t))

/*
 * FL: first level
 * SL: second level
 * FL = 30 - 6 + 1 = 25
 * SL = 16
 *
 *    |  FL  |                   30                    | ... |                  6                  |
 * -------------------------------------------------------------------------------------------------
 * SL |   0  | 2^30+0*(2^30/2^4)  ~ 2^30+1*(2^30/2^4)  | ... | 2^6+0*(2^6/2^4)  ~ 2^6+1*(2^6/2^4)  |
 * -------------------------------------------------------------------------------------------------
 * SL |   1  | 2^30+1*(2^30/2^4)  ~ 2^30+2*(2^30/2^4)  | ... | 2^6+1*(2^6/2^4)  ~ 2^6+2*(2^6/2^4)  |
 * -------------------------------------------------------------------------------------------------
 * SL |   2  | 2^30+2*(2^30/2^4)  ~ 2^30+3*(2^30/2^4)  | ... | 2^6+2*(2^6/2^4)  ~ 2^6+3*(2^6/2^4)  |
 * -------------------------------------------------------------------------------------------------
 * SL |   3  | 2^30+3*(2^30/2^4)  ~ 2^30+4*(2^30/2^4)  | ... | 2^6+3*(2^6/2^4)  ~ 2^6+4*(2^6/2^4)  |
 * -------------------------------------------------------------------------------------------------
 * SL |  ..  |                   ...                   | ... |                 ...                 |
 * -------------------------------------------------------------------------------------------------
 * SL |  15  | 2^30+14*(2^30/2^4) ~ 2^30+15*(2^30/2^4) | ... | 2^6+14*(2^6/2^4) ~ 2^6+15*(2^6/2^4) |
 * -------------------------------------------------------------------------------------------------
 */

/*
 * The head of a block.
 */
typedef struct tlsf_block_head {
#ifdef CONFIG_LX_MM_DEBUG_MAGIC
    int magic; /* "LXOS" = 0X4C584F53 */
#endif

#ifdef CONFIG_LX_MM_DEBUG_TID
    tid_t tid; /* default: -1 */
#endif

    size_t size;
    list_t list;
} tlsf_block_head_t;

/*
 * The end of a block.
 */
typedef struct tlsf_block_end {
#ifdef CONFIG_LX_MM_DEBUG_MAGIC
    int magic; /* "LXOS" = 0X4C584F53 */
#endif

    tlsf_block_head_t *self;
} tlsf_block_end_t;

/*
 * The manager of the whole memory.
 */
typedef struct tlsf_manager {
    uint32_t fl_bitmap;
    uint32_t sl_bitmap[TLSF_FL_INDEX];

    tlsf_block_head_t *blocks[TLSF_FL_INDEX][TLSF_SL_INDEX];
} tlsf_manager_t;

extern tlsf_manager_t g_tlsf_manager; /* Only one manager in system */

void tlsf_init(void);

void *tlsf_malloc(size_t size);

void *tlsf_zalloc(size_t size);

void *tlsf_realloc(void *oldmem, size_t size);

void tlsf_free(void *mem);

void tlsf_check(void);

#endif /* MM_TLSF_H */

