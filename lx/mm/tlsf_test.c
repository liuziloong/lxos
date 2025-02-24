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

#include "tlsf_test.h"

#include "tlsf.h"

void tlsf_test(void)
{
    void *mem1 = NULL;
    void *mem2 = NULL;
    //void *mem3 = NULL;
    //void *mem4 = NULL;
    void *mem5 = NULL;
    //void *mem6 = NULL;

    mem1 = tlsf_malloc(64);
    memset(mem1, 0, 16);
    tlsf_check();

    mem2 = tlsf_malloc(120);
    memset(mem2, 0, 12);
    tlsf_check();

    mem5 = tlsf_malloc(256);
    tlsf_check();

    tlsf_free(mem1);
    tlsf_check();

    tlsf_free(mem2);
    tlsf_check();

    tlsf_free(mem5);
    tlsf_check();

#ifdef CONFIG_LX_MM_DEBUG_BITMAP_SHOW
    _tlsf_debug_bitmap_show();
#endif
}

