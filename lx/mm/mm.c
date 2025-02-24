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

#include "mm/mm.h"

#include "lx/log.h"
#include "port/mm.h"

#ifdef CONFIG_LX_MM_TLSF
#include "tlsf.h"
#endif

#ifdef CONFIG_LX_MM_HALFFIT
#include "halffit.h"
#endif

void mm_init(void)
{
    int num = 0;
    int tmp = 0;

    hw_mm_init();

    LOGI("MM: MM-INIT NOW! There are %d regions.\n", g_mm_region_num);

    if ((g_mm_region_num < MM_REGION_NUM_MIN) || (g_mm_region_num > MM_REGION_NUM_MAX)) {
        LOGE("MM: region number error!\n");

        return;
    }

    for (num = 0; num < g_mm_region_num; num++) {
        if ((g_mm_region[num].size < MM_REGION_SIZE_MIN) ||
            (g_mm_region[num].size > MM_REGION_SIZE_MAX)) {
            LOGE("MM: region size(%d) error! 0x%x < REGION-SIZE < 0x%x.\n",
                 g_mm_region[num].size, MM_REGION_SIZE_MIN, MM_REGION_SIZE_MAX);
        }

        if ((int)g_mm_region[num].addr % MM_ALIGN_SIZE != 0) {
            LOGW("MM: memory address must be aligned to %d bytes.\n", MM_ALIGN_SIZE);
        }

        /* get the aligned address */
        tmp = MM_ALIGN_UP((int)g_mm_region[num].addr);

        g_mm_region[num].size = MM_ALIGN_DOWN(g_mm_region[num].size - (tmp - (int)g_mm_region[num].addr));
        g_mm_region[num].addr = (void *)tmp;

        LOGI("MM: memory start address is 0x%x, size is %d ~ 0x%x.\n",
             g_mm_region[num].addr, g_mm_region[num].size, g_mm_region[num].size);
    }

#ifdef CONFIG_LX_MM_TLSF
    tlsf_init();
#endif

#ifdef CONFIG_LX_MM_HALFFIT
    halffit_init();
#endif
}

void *mm_malloc(size_t size)
{
#ifdef CONFIG_LX_MM_TLSF
    return tlsf_malloc(size);
#endif

#ifdef CONFIG_LX_MM_HALFFIT
    return halffit_malloc(size);
#endif
}

void *mm_zalloc(size_t size)
{
#ifdef CONFIG_LX_MM_TLSF
    return tlsf_zalloc(size);
#endif

#ifdef CONFIG_LX_MM_HALFFIT
    return halffit_zalloc(size);
#endif
}

void *mm_realloc(void *oldmem, size_t size)
{
#ifdef CONFIG_LX_MM_TLSF
    return tlsf_realloc(oldmem, size);
#endif

#ifdef CONFIG_LX_MM_HALFFIT
    return halffit_realloc(oldmem, size);
#endif
}

void mm_free(void *mem)
{
#ifdef CONFIG_LX_MM_TLSF
    tlsf_free(mem);
#endif

#ifdef CONFIG_LX_MM_HALFFIT
    halffit_free(mem);
#endif
}

void mm_check(void)
{
#ifdef CONFIG_LX_MM_TLSF
    tlsf_check();
#endif

#ifdef CONFIG_LX_MM_HALFFIT
    halffit_check();
#endif
}

