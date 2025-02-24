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

#ifndef KERNEL_RWLOCK_H
#define KERNEL_RWLOCK_H

typedef struct rwlock {

} rwlock_t;

typedef struct rwlock_attr {

} rwlock_attr_t;

void rwlock_init(rwlock_t *rwlock, const rwlock_attr_t *attr);

void rwlock_destroy(rwlock_t *rwlock);

void rwlock_attr_init(rwlock_attr_t *attr);

int rwlock_attr_destroy(rwlock_attr_t *attr);

int rwlock_attr_get(rwlock_attr_t *attr);

int rwlock_attr_set(rwlock_attr_t *attr);

int rwlock_rdlock(rwlock_t *rwlock);

int rwlock_tryrdlock(rwlock_t *rwlock);

int rwlock_wrlock(rwlock_t *rwlock);

int rwlock_trywrlock(rwlock_t *rwlock);

int rwlock_unlock(rwlock_t *rwlock);

#endif /* KERNEL_RWLOCK_H */

