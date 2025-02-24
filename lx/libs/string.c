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
#include "lx/string.h"

void *memchr(const void *src, char c, size_t size)
{
    const char *tmp = (const char *)src;

    while (size-- != 0) {
        if (c == *tmp) {
            return (void *)tmp;
        }

		tmp++;
    }

    return NULL;
}

/* TODO: word length and alined */
void *memcpy(void *dst, const void *src, size_t count)
{
    uint8_t       *to = (uint8_t *)dst;
    const uint8_t *from = (const uint8_t *)src;

    while (count--) {
        *to++ = *from++;
    }

    return dst;
}

int32_t memcmp(const void *mem1, const void *mem2, size_t count)
{
    const uint8_t *tmp1 = (const uint8_t *)mem1;
    const uint8_t *tmp2 = (const uint8_t *)mem2;

    for (; count > 0; count--) {
        if (*tmp1 != *tmp2) {
            return ((*tmp1 > *tmp2) ? 1 : -1);
        }

        tmp1++;
        tmp2++;
    }

    return 0;
}

void *memset(void *mem, uint8_t c, size_t count)
{
    uint8_t *tmp = (uint8_t *)mem;

    while (count--) {
        *tmp++ = c;
    }

    return mem;
}

void *memmove(void *dst, const void *src, size_t count)
{
    uint8_t       *to = (uint8_t *)dst;
    const uint8_t *from = (const uint8_t *)src;

    if (dst <= src) {
        while (count--) {
            *to++ = *from++;
        }
    } else {
        to   += count;
        from += count;
        while (count--) {
            *--to = *--from;
        }
    }

    return dst;
}

char *strcpy(char *dst, const char *src)
{
    char *tmp = dst;

    while ((*tmp++ = *src++) != '\0') {
        ;
    }

    return dst;
}

char *strncpy(char *dst, const char *src, size_t count)
{
    char *tmp = dst;

    for (; (count > 0) && (*src != '\0'); --count) {
        *tmp++ = *src++;
    }

    *tmp = '\0';

    for (; count > 0; --count) {
        *tmp++ = '\0';
    }

    return dst;
}

char *strcat(char *dst, const char *src)
{
    char *tmp = dst;

    while (*tmp != '\0') {
        tmp++;
    }

    while ((*tmp++ = *src++) != '\0') {
        ;
    }

    return dst;
}

char *strncat(char *dst, const char *src, size_t count)
{
    char *tmp = dst;

    while (*tmp != '\0') {
        tmp++;
    }

    for (; (count > 0) && (*src != '\0'); --count) {
        *tmp++ = *src++;
    }

    *tmp = '\0';

    return dst;
}

int32_t strcmp(const char *str1, const char *str2)
{
    while (1) {
        if (*str1 != *str2) {
            return *str1 > *str2 ? 1 : -1;
        }

        if (*str1 == '\0') {
            break;
        }

        str1++;
        str2++;
    }

    return 0;
}

int32_t strncmp(const char *str1, const char *str2, size_t count)
{
    while (count--) {
        if (*str1 != *str2) {
            return *str1 > *str2 ? 1 : -1;
        }

        if (*str1 == '\0') {
            break;
        }

        str1++;
        str2++;
    }

    return 0;
}

char *strchr(const char *str, char c)
{
    for (; *str != c; str++) {
        if (*str == '\0') {
            return NULL;
        }
    }

    return (char *)str;
}

char *strrchr(const char *str, char c)
{
    const char *last = NULL;

    do {
        if (*str == c) {
            last = str;
        }
    } while (*str++ != '\0');

    return (char *)last;
}

char *strnchr(const char *str, char c, size_t count)
{
    for (; (count > 0) && (*str != '\0'); str++, count--) {
        if (*str == c) {
            return (char *)str;
        }
    }

    return NULL;
}

size_t strlen(const char *str)
{
    const char *tmp;

    for (tmp = str; *tmp != '\0'; tmp++) {
        ;
    }

    return (size_t)(tmp - str);
}

size_t strnlen(const char *str, size_t count)
{
    const char *tmp;

    for (tmp = str; (count > 0) && (*tmp != '\0'); tmp++, count--) {
        ;
    }

    return (size_t)(tmp - str);
}

char *strstr(const char *str1, const char *str2)
{
    size_t len1;
    size_t len2;

    len2 = strlen(str2);
    if (!len2) {
        return (char *)str1;
    }

    len1 = strlen(str1);
    while (len1 >= len2) {
        if (memcmp(str1, str2, len2) == 0) {
            return (char *)str1;
        }

        len1--;
        str1++;
    }

    return NULL;
}

char *strnstr(const char *str1, const char *str2, size_t len)
{
    size_t tmp;

    tmp = strlen(str2);
    if (!tmp) {
        return (char *)str1;
    }

    while (len >= tmp) {
        if (memcmp(str1, str2, tmp) == 0) {
            return (char *)str1;
        }

        len--;
        str1++;
    }

    return NULL;
}

char *strupr(char *str)
{
    char *tmp = str;

    for (; *tmp != '\0'; tmp++) {
        if ((*tmp >= 'a') && (*tmp <= 'z')) {
            *tmp -= ('a' - 'A');
        }
    }

    return str;
}

