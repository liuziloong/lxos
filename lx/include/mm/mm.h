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

#ifndef MM_MM_H
#define MM_MM_H

#include "lx/types.h"

#define MM_REGION_SIZE_MIN_LOG2 13
#define MM_REGION_SIZE_MAX_LOG2 31

#define MM_REGION_SIZE_MIN (1 << MM_REGION_SIZE_MIN_LOG2) /* 8K bytes */
#define MM_REGION_SIZE_MAX (1 << MM_REGION_SIZE_MAX_LOG2) /* 2G bytes */

#define MM_REGION_NUM_MIN 1
#define MM_REGION_NUM_MAX 8

#define MM_ALIGN_LOG2    2
#define MM_ALIGN_SIZE    (1 << MM_ALIGN_LOG2) /* 32-bit architecture: align to 4 bytes */
#define MM_ALIGN_MASK    (MM_ALIGN_SIZE - 1)
#define MM_ALIGN_UP(x)   (((x) + MM_ALIGN_MASK) & ~MM_ALIGN_MASK)
#define MM_ALIGN_DOWN(x) ((x) & ~MM_ALIGN_MASK)

/*
 * The region provided by hardware, there may be more than one region.
 */
typedef struct mm_region {
    void   *addr;
    size_t  size;
} mm_region_t;

#ifdef CONFIG_LX_MM_DEBUG
//extern mm_alloc_node_t *g_mm_alloc_node;
#endif

void mm_init(void);

void *mm_malloc(size_t size);

void *mm_zalloc(size_t size);

void *mm_realloc(void *oldmem, size_t size);

void mm_free(void *mem);

#endif /* MM_MM_H */

