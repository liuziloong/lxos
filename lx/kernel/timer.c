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

#include "kernel/timer.h"

#include "lx/types.h"

timer_t *timer_create(const char *name, tick_t period, uint32_t repeat,
                      timer_cb_t cb, void *param)
{
    return 0;
}

state_t timer_delete(timer_t *timer)
{
    return 0;
}

state_t timer_reset(timer_t *timer, tick_t period, uint32_t repeat)
{
    return 0;
}

state_t timer_start(timer_t *timer)
{
    return 0;
}

state_t timer_stop(timer_t *timer)
{
    return 0;
}

