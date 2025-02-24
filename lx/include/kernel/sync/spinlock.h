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

#ifndef KERNEL_SPINLOCK_H
#define KERNEL_SPINLOCK_H

typedef struct {

} spinlock_t;

void spin_lock_init(spinlock_t *lock);

void spin_lock(spinlock_t *lock);

void spin_unlock(spinlock_t *lock);

void spin_lock_irq(spinlock_t *lock);

void spin_unlock_irq(spinlock_t *lock);

void spin_lock_irqsave(spinlock_t *lock, unsigned long flags);

void spin_unlock_irqrestore(spinlock_t *lock, unsigned long flags);

int spin_trylock(spinlock_t *lock);

int spin_is_locked(spinlock_t *lock);

#endif /* KERNEL_SPINLOCK_H */

