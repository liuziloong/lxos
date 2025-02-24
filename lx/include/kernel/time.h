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

#ifndef KERNEL_TIME_H
#define KERNEL_TIME_H

typedef struct {
    uint32_t tv_sec;  /* seconds */
    uint32_t tv_usec; /* microseconds */
} timeval_t;

typedef struct {
    uint32_t tv_sec;  /* seconds */
    uint32_t tv_nsec; /* nanoseconds */
} timespec_t;

extern timespec_t g_xtime; /* wall time */
extern lock_t     g_xtime_lock;

#define time_after(a, b) ((int32_t)(b) - (int32_t)(a) < 0)

#define time_after_eq(a, b) ((int32_t)(a) - (int32_t)(b) >= 0)

#define time_before(a, b) time_after(b, a)

#define time_before_eq(a, b) time_after_eq(b, a)

static inline void rtc_set(void)
{
}

state_t gettimeofday(timeval_t *tv, struct timezone *tz);

state_t settimeofday(timeval_t *tv, struct timezone *tz);

#endif /* KERNEL_TIME_H */

