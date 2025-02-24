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

#ifndef KERNEL_IRQ_H
#define KERNEL_IRQ_H

#include "arch/irq.h"

#define LOCAL_IRQ_ENABLE()  do { hw_local_irq_enable(); } while (0)
#define LOCAL_IRQ_DISABLE() do { hw_local_irq_disable(); } while (0)

#define LOCAL_IRQ_SAVE(flags)    do { (flags) = hw_local_irq_save(); } while (0)
#define LOCAL_IRQ_RESTORE(flags) do { hw_local_irq_restore(flags); } while (0)

#endif /* KERNEL_IRQ_H */

