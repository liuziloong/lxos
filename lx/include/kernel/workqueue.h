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

#ifndef KERNEL_WORKQUEUE_H
#define KERNEL_WORKQUEUE_H

//#ifdef CONFIG_LX_WORKQUEUE

#include "lx/list.h"
#include "lx/types.h"

#define WORKQUEUE_WORK_MAX 32

typedef void (*work_handle_t)(void *param);

typedef struct {
//    list_t        work_node;
    uint32_t      running;
    work_handle_t handle;
    void         *param;

#ifdef CONFIG_LX_WORKQUEUE_DELAY
    tick_t        delay;
//    timer_t       timer;
#endif
} work_t;

typedef struct {
    list_t        workqueue_node;
    work_t       *work_head;
    const char *name;
//    mutex_t       work_mutex;
//    thread_t      worker;
//    sem_t         sem;
} workqueue_t;

//extern workqueue_t *g_workqueue_head;
//extern mutex_t      g_workqueue_mutex;

workqueue_t *workqueue_create(const char *name);

void workqueue_flush(workqueue_t *workqueue);

void workqueue_delete(workqueue_t *workqueue);

//work_t *work_init(void (*func)(void *), void *args, unsigned long delay);

void work_run(workqueue_t *workqueue, work_t *work);

void sched_work(work_t *work, unsigned long delay);

void work_flush(work_t *work);

void work_cancel(work_t *work);

//#endif /* CONFIG_LX_WORKQUEUE */

#endif /* KERNEL_WORKQUEUE_H */

