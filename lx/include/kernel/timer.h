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

#ifndef KERNEL_TIMER_H
#define KERNEL_TIMER_H

#include "lx/types.h"

typedef struct {
    const char    *name;
    //list_t        node;
    //tick_t        expires;
    //timer_cb_t *func;
    void       *param;
    //tick_t        period;
    unsigned int      repeat;
} timer_t;

typedef void (*timer_cb_t)(void *param);

typedef struct {
    //spinlock_t lock;
    struct timer_list *running_timer;
    uint32_t timer_jiffies;
    uint32_t next_timer;
    //struct tvec_root tv1;
    //struct tvec tv2;
    //struct tvec tv3;
    //struct tvec tv4;
    //struct tvec tv5;
} timer_vec_t;

#define INIT_CPU_TIMERS(cpu_timers)    \
{                                      \
    LIST_HEAD_INIT(cpu_timers[0]), \
    LIST_HEAD_INIT(cpu_timers[1]), \
    LIST_HEAD_INIT(cpu_timers[2]), \
}

timer_t *timer_create(const char *name, tick_t period, uint32_t repeat,
                      timer_cb_t cb, void *param);

state_t timer_delete(timer_t *timer);

state_t timer_delete_sync(timer_t *timer);

state_t timer_modify(timer_t *timer, tick_t period, uint32_t repeat);

state_t timer_start(timer_t *timer);

state_t timer_stop(timer_t *timer);

#endif /* KERNEL_TIMER_H */

