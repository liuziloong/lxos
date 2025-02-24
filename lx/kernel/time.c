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

#include "kernel/time.h"

timespec_t g_xtime; /* wall time */
lock_t     g_xtime_lock;

state_t gettimeofday(timeval_t *tv, struct timezone *tz)
{
    return 0;
}

state_t settimeofday(timeval_t *tv, struct timezone *tz)
{
    return 0;
}

