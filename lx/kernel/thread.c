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

#include "kernel/thread.h"

#include "lx/types.h"

thread_t  g_init_thread;
thread_t *g_current = &g_init_thread;;

state_t thread_create(thread_t *thread, const char *name, thread_entry_t entry,
                      void *param,uint32_t prio, void *stack, size_t stack_size)
{
    if (name == NULL) {
        return NULL;
    }

    return NULL;
}

state_t thread_delete(thread_t *thread)
{
    return 0;
}

state_t thread_suspend(thread_t *thread)
{
    return 0;
}

state_t thread_resume(thread_t *thread)
{
    return 0;
}

state_t thread_prio_get(thread_t *thread, uint32_t prio)
{
    return 0;
}

state_t thread_prio_set(thread_t *thread, uint32_t prio)
{
    return 0;
}

