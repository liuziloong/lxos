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

#ifndef PORT_MM_H
#define PORT_MM_H

#include "mm/mm.h"

extern int g_mm_region_num;

extern mm_region_t g_mm_region[]; /* memory regions, provided by vendor. */

void hw_mm_init(void);

#endif /* PORT_MM_H */

