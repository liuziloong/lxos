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

#ifndef KERNEL_SEM_H
#define KERNEL_SEM_H

typedef struct {
    const char *name;
    uint32_t    count;
    list_t     *wait_head;
    lock_t      lock;
} sem_t;

state_t sem_create(sem_t *sem, const char *name, int count, int init);

state_t sem_delete(sem_t *sem);

state_t sem_clear(sem_t *sem);

state_t sem_take(sem_t *sem);

state_t sem_give(sem_t *sem);

#endif /* KERNEL_SEM_H */

