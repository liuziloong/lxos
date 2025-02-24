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

#include "kernel/tick.h"

#include "lx/types.h"

systicks_t g_systicks;

uint32_t systicks_get(void)
{
    return g_systicks.ticks_32;
}

uint64_t systicks64_get(void)
{
    return g_systicks.ticks_64;
}

uint32_t ticks_to_msecs(const uint32_t ticks)
{
    return 0;
}

uint32_t ticks_to_usecs(const uint32_t ticks)
{
    return 0;
}

uint32_t msecs_to_ticks(const uint32_t msecs)
{
    return 0;
}

uint32_t usecs_to_ticks(const uint32_t usecs)
{
    return 0;
}

