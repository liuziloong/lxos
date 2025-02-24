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

#ifndef ARCH_PORT_CPU_H
#define ARCH_PORT_CPU_H

void hw_cpu_ctx_switch(void);

void hw_cpu_start_first(void);

void hw_cpu_systick_handle(void);

void hw_cpu_pendsv_handle(void);

void hw_cpu_stack_init(void *task, void *arg, uint32_t stk_base, size_t stk_size);

#endif /* ARCH_PORT_CPU_H */

