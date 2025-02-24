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

#ifndef LX_LOG_H
#define LX_LOG_H

#include "lx/printk.h"

#ifndef CONFIG_LX_LOG_LEVEL
#define CONFIG_LX_LOG_LEVEL 2
#endif

#define LOG_LEVEL_ERROR   0
#define LOG_LEVEL_WARNING 1
#define LOG_LEVEL_INFO    2
#define LOG_LEVEL_DEBUG   3

#define LOG_ERROR   "\033[1;31m[ERROR]\033[0m "
#define LOG_WARNING "\033[1;33m[WARNING]\033[0m "
#define LOG_INFO    "\033[1;34m[INFO]\033[0m "
#define LOG_DEBUG   "\033[1;32m[DEBUG]\033[0m "

#define LOG(fmt, ...) printk("\033[1;31m" fmt "\033[0m", ##__VA_ARGS__)

#if (LOG_LEVEL_ERROR <= CONFIG_LX_LOG_LEVEL)
#define LOGE(fmt, ...) printk("\r" LOG_ERROR fmt "\r\n", ##__VA_ARGS__)
#else
#define LOGE(fmt, ...)
#endif

#if (LOG_LEVEL_WARNING <= CONFIG_LX_LOG_LEVEL)
#define LOGW(fmt, ...) printk("\r" LOG_WARNING fmt "\r\n", ##__VA_ARGS__)
#else
#define LOGW(fmt, ...)
#endif

#if (LOG_LEVEL_INFO <= CONFIG_LX_LOG_LEVEL)
#define LOGI(fmt, ...) printk("\r" LOG_INFO fmt "\r\n", ##__VA_ARGS__)
#else
#define LOGI(fmt, ...)
#endif

#if (LOG_LEVEL_DEBUG <= CONFIG_LX_LOG_LEVEL)
#define LOGD(fmt, ...) printk("\r" LOG_DEBUG fmt "\r\n", ##__VA_ARGS__)
#else
#define LOGD(fmt, ...)
#endif

#endif /* LX_LOG_H */

