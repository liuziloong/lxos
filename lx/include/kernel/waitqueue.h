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

#ifndef KERNEL_WAITQUEUE_H
#define KERNEL_WAITQUEUE_H

#ifdef CONFIG_LX_WAITQUEUE

#include "lx/list.h"

typedef struct {
    unsigned int  flags;
    thread_t       *thread;
    void(*)(void) func;
    list_t        thread_node;
} wait_t;

typedef struct {
    spinlock_t lock;
    list_t     thread_node;
} waitqueue_t;

void waitqueue_init(waitqueue_t *waitqueue);

void wait_init(waitqueue_t *waitqueue, thread_t *thread);

void wait_add(waitqueue_t *waitqueue, wait_t *wait);

void wait_remove(waitqueue_t *waitqueue, wait_t *wait);

void wait_event(wait_t *wait, uint32_t condition, uint32_t timeout);

void wait_wakeup(wait_t *wait);

#endif /* CONFIG_LX_WAITQUEUE */

#endif /* KERNEL_WAITQUEUE_H */

