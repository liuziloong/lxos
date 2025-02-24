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

#ifndef KERNEL_TICK_H
#define KERNEL_TICK_H

#include "lx/types.h"

typedef union {
    uint32_t ticks_32;
    uint64_t ticks_64;
} systicks_t;

uint32_t systicks_32_get(void);

uint64_t systicks_64_get(void);

uint32_t ticks_to_msecs(const uint32_t ticks);

uint32_t ticks_to_usecs(const uint32_t ticks);

uint32_t msecs_to_ticks(const uint32_t msecs);

uint32_t usecs_to_ticks(const uint32_t usecs);

#endif /* KERNEL_TICK_H */

