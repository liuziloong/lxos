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

#ifndef KERNEL_SCHED_H
#define KERNEL_SCHED_H

#include "lx/bitmap.h"

/*
 * 0: highest, 63: lowest
 *
 * 0~7:   used by kernel
 * 8~55:  used by user
 * 56~63: used by kernel
 */
#define SCHED_PRIO_MAX     64
#define SCHED_PRIO_DEFAULT 32

#define SCHED_FIFO 1
#define SCHED_RR   2

typedef struct {
    BITMAP_DECLARE(bitmap, SCHED_PRIO_MAX);
	list_t queue[SCHED_PRIO_MAX];
} run_queue_t;

typedef struct {


} wait_queue_t;


void update_thread_ticks(void);

#endif /* KERNEL_SCHED_H */

