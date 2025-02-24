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

#ifndef KERNEL_ATOMIC_H
#define KERNEL_ATOMIC_H

void atomic_(int count);

int atomic_read(atomic_t *v);

void atomic_set(atomic_t *v, int count);

void atomic_add(atomic_t *v, int count);

void atomic_sub(atomic_t *v, int count);

void atomic_inc(atomic_t *v);

void atomic_dec(atomic_t *v);

int atomic_sub_and_test(atomic_t *v, int count);

int atomic_add_negative(atomic_t *v, int count);

int atomic_dec_and_test(atomic_t *v);

int atomic_inc_and_test(atomic_t *v);

#endif /* KERNEL_ATOMIC_H */

