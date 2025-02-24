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

#include "lx/types.h"

#include "mm/mm.h"
#include "port/mm.h"

#define MM_REGION_NUM 5

int g_mm_region_num = MM_REGION_NUM;

mm_region_t g_mm_region[MM_REGION_NUM];

void hw_mm_init(void)
{
    g_mm_region[0].addr = (void *)0x20001000;
	g_mm_region[0].size = (size_t)0x00003070;

    g_mm_region[1].addr = (void *)0x20006000;
    g_mm_region[1].size = (size_t)0x00003050;

    g_mm_region[2].addr = (void *)0x20016000;
    g_mm_region[2].size = (size_t)0x00003080;

    g_mm_region[3].addr = (void *)0x20019080;
    g_mm_region[3].size = (size_t)0x00003060;

	g_mm_region[4].addr = (void *)0x2002c0e0;
    g_mm_region[4].size = (size_t)0x00003100;
}

