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

#ifndef KERNEL_MUTEX_H
#define KERNEL_MUTEX_H

typedef struct {
    const char *name;
    atomic_t    count;
    spinlock_t  lock;
    list_t     *wait_head;
} mutex_t;

void mutex_lock(mutex_t *mutex);

void mutex_trylock(mutex_t *mutex);

void mutex_unlock(mutex_t *mutex);


#endif /* KERNEL_MUTEX_H */

