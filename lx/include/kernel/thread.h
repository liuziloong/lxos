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

#ifndef KERNEL_THREAD_H
#define KERNEL_THREAD_H

#include "lx/list.h"
#include "lx/types.h"

#define THREAD_NAME_LEN_MAX 32

/* thread priority */
#define THREAD_PRIO_MID 32

#define THREAD_PRIO_DEFAULT THREAD_PRIO_MID

static inline int32_t thread_prio_check(uint32_t prio)
{
    return 0;
}

#define THREAD_STATE_INVALID     0 /* the thread is uninitialized */
#define THREAD_STATE_INACTIVE    1 /* the thread is initialized but not yet activated */
#define THREAD_STATE_RUNNING     1 /* the thread is running */
#define THREAD_STATE_PENDING     2 /* the thread is pending for preemption unlock */
#define THREAD_STATE_READYTORUN  3 /* the thread is ready but not running */
#define THREAD_STATE_WAITING_SEM 4 /* the thread is waiting for a semaphore */
#define THREAD_STATE_WAITING_SIG 5 /* the thread is waiting for a signal*/
#define THREAD_STATE_STOPPED     6 /* the thread is stopped by a signal */
#define THREAD_STATE_DEAD        7 /* the thread is dead: exit or killed */

#define THREAD_IS_RUNNING(thread) ((thread->state & THREAD_STAT_RUNNING) != 0)
#define THREAD_IS_TRACED(thread)  ((thread->state & THREAD_STAT_TRACED)  != 0)

typedef void (*thread_entry_t)(void *param);

typedef struct {
    uint32_t  state;

#ifdef CONFIG_LX_THREAD_NAME
    char      name[THREAD_NAME_LEN_MAX];
#endif

	void     *entry;
	void     *param;
    void     *stack;
    size_t    stack_size;

//	sched_type_e type;
	uint32_t prio;
	tid_t tid;
	uid_t uid;
	gid_t gid;

    list_t threads;

#ifdef CONFIG_SMP
    uint32_t cpu_id;
#endif
} thread_t;

#define INIT_THREAD(thread) \
{                       \
}

state_t thread_create(thread_t *thread, const char *name, thread_entry_t entry,
                      void *param,uint32_t prio, void *stack, size_t stack_size);

state_t thread_delete(thread_t *thread);

state_t thread_suspend(thread_t *thread);

state_t thread_resume(thread_t *thread);

state_t thread_prio_get(thread_t *thread, uint32_t prio);

state_t thread_prio_set(thread_t *thread, uint32_t prio);

state_t thread_delay(thread_t *thread, uint32_t ticks);

state_t thread_yield(void);

#endif /* KERNEL_THREAD_H */

