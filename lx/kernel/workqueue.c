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

#include "kernel/workqueue.h"

#include "lx/types.h"

//workqueue_t *g_workqueue_head;
//mutex_t      g_workqueue_mutex;

workqueue_t *workqueue_create(const char *name)
{
    return NULL;
}

void workqueue_flush(workqueue_t *workqueue)
{

}

void workqueue_delete(workqueue_t *workqueue)
{

}

void work_init(work_t *work, work_handle_t handle, void *param, uint32_t delay)
{
	return;
}

void work_run(workqueue_t *workqueue, work_t *work)
{

}

void work_flush(work_t *work)
{

}

