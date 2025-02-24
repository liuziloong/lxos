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

#include "kernel/thread.h"

#include "lx/log.h"

#include "mm/mm.h"

static inline void systick_init(void)
{

}

static inline void sched_init(void)
{

}

static inline void time_init(void)
{
}

static inline void timer_init(void)
{

}

static inline void workqueue_init(void)
{
}

static inline void console_init(void)
{
}

static inline void idle_init(void)
{
}

static inline void app_init(void)
{
}


extern int main(void);

static inline void lx_startup(void)
{
    main();
}

void lx_start(void)
{
    LOG("\r\n----------lx start now!!!----------\n\n");

    mm_init();

    systick_init();

    sched_init();

    time_init();

    timer_init();

    workqueue_init();

    console_init();

    idle_init();

    app_init();

    lx_startup();
}
