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

#include "lx/errno.h"
#include "lx/stdarg.h"
#include "lx/stdlib.h"
#include "lx/string.h"
#include "lx/types.h"
#include "lx/vsnprintf.h"

/*
enum fmt_type_e {
    FMT_TYPE_NONE,
    FMT_TYPE_CHAR,
    FMT_TYPE_STRING,
    FMT_TYPE_SHORT,
    FMT_TYPE_USHORT,
    FMT_TYPE_INT,
    FMT_TYPE_UINT,
    FMT_TYPE_LONG,
    FMT_TYPE_ULONG,
};

typedef struct {
    uint32_t align;
    uint32_t width;
    uint32_t precision;
    uint32_t padding;
    uint32_t base;
    uint32_t type;
} fmt_attr_t;
*/

int vsnprintf(char *buf, size_t size, const char *fmt, va_list args)
{
    char *tmp = NULL;
    char *sp  = NULL;

    size_t len   = 0;
    size_t count = 0;

    char    str[16] = {0};
    int32_t val     = 0;

    while ((tmp = strchr(fmt, '%')) != NULL) {
        len    = tmp - fmt;
        count += len;
        if (count > size - 1) {
            return -ENOMEM;
        }

        strncpy(buf, fmt, len);

        buf += len;
        fmt += len;

        switch (*++fmt) {
            case 'c':
                if (++count > size - 1) {
                    return -ENOMEM;
                }
                *buf++ = (char)va_arg(args, int);
                fmt++;
                break;
            case 's':
                sp = va_arg(args, char *);
                len = strlen(sp);
                count += len;
                if (count > size - 1) {
                    return -ENOMEM;
                }
                strncpy(buf, sp, len);
                buf += len;
                fmt++;
                break;
            case 'd':
                val = va_arg(args, int);
                itoa(val, str, 10);
                len = strlen(str);
                count += len;
                if (count > size - 1) {
                    return -ENOMEM;
                }
                strncpy(buf, str, len);
                buf += len;
                fmt++;
                break;
            case 'x':
                val = va_arg(args, int);
                itoa(val, str, 16);
                len = strlen(str);
                count += len;
                if (count > size - 1) {
                    return -ENOMEM;
                }
                strncpy(buf, str, len);
                buf += len;
                fmt++;
                break;
            case 'X':
                val = va_arg(args, int);
                itoa(val, str, 16);
                strupr(str);
                len = strlen(str);
                count += len;
                if (count > size - 1) {
                    return -ENOMEM;
                }
                strncpy(buf, str, len);
                buf += len;
                fmt++;
                break;
            case '%':
                if (++count > size - 1) {
                    return -ENOMEM;
                }
                *buf++ = '%';
                fmt++;
                break;
            default:
                return -EINVAL;
        }
    }

    count += strlen(fmt);
    if (++count > size - 1) {
        return -ENOMEM;
    }

    strcpy(buf, fmt);

    return count;
}

