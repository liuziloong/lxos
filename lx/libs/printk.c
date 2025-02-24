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

#include "lx/printk.h"

#include "lx/stdarg.h"
#include "lx/string.h"
#include "lx/vsnprintf.h"

#define BUF_MAX 1024

#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo_144.h"

extern UART_HandleTypeDef UartHandle;

void printk(const char *fmt, ...)
{
    char    buf[BUF_MAX];
    size_t  len;
    va_list args;

    memset(buf, 0, BUF_MAX);

    va_start(args, fmt);
    len = vsnprintf(buf, BUF_MAX, fmt, args);
    HAL_UART_Transmit(&UartHandle, (uint8_t *)buf, len, 0xFFFF);
    va_end(args);
}

