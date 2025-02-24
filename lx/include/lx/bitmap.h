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

#ifndef LX_BITMAP_H
#define LX_BITMAP_H

#include "lx/types.h"

/*
 * bitmap_ffs: 0X0000 0000, return -1; 0X0000 0001, return 0; 0X0000 0006, return 1.
 *
 * bitmap_fls: 0X0000 0000, return -1; 0X0000 0001, return 0; 0X0000 0006, return 2.
 */
#if defined (__GNUC__) && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))

static inline int bitmap_ffs(uint32_t x)
{
    return __builtin_ffs(x) - 1;
}

static inline int bitmap_fls(uint32_t x)
{
    return (x ? 32 - __builtin_clz(x) : 0) - 1;
}

#elif defined (__ARMCC_VERSION)

static inline int bitmap_ffs(uint32_t x)
{
    return (32 - __clz(x & (~x + 1))) - 1;
}

static inline int bitmap_fls(uint32_t x)
{
    return (x ? 32 - __clz(x) : 0) - 1;
}

#else

static inline int _bitmap_clz(uint32_t x)
{
    int n = 0;

    if (!x) {
        return 32;
    }

    if (!(x & 0XFFFF0000)) {
        x <<= 16;
        n  += 16;
    }

    if (!(x & 0XFF000000)) {
        x <<= 8;
        n  += 8;
    }

    if (!(x & 0XF0000000)) {
        x <<= 4;
        n  += 4;
    }

    if (!(x & 0XC0000000)) {
        x <<= 2;
        n  += 2;
    }

    if (!(x & 0X80000000)) {
        x <<= 1;
        n  += 1;
    }

    return n;
}

static inline int bitmap_ffs(uint32_t x)
{
    return (32 - _bitmap_clz(x & (~x + 1))) - 1;
}

static inline int bitmap_fls(uint32_t x)
{
    return (x ? 32 - _bitmap_clz(x) : 0) - 1;
}

#endif

#endif /* LX_BITMAP_H */

