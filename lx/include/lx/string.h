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

#ifndef LX_STRING_H
#define LX_STRING_H

#include "lx/types.h"

/**
 * memchr - Find a character in an area of memory.
 * @param[in] src   The memory area
 * @param[in] c     The character to search for
 * @param[in] size  The size of the area
 * @return  if find, return the address of the first occurrence;
 *          else return NULL.
 */
void *memchr(const void *src, char c, size_t size);

/**
 * memcpy - Copy one area of memory to another.
 * @param[in] dst    Where to copy to
 * @param[in] src    Where to copy from
 * @param[in] count  The size of the area
 * @return  return the address of the dst area.
 *
 * *DON'T* use this function to access IO space.
 */
void *memcpy(void *dst, const void *src, size_t count);

/**
 * memcmp - Compare two areas of memory.
 * @param[in] mem1   One area of memory
 * @param[in] mem2   Another area of memory
 * @param[in] count  The size of the area
 * @return  if *mem1 > *mem2, return 1;
 *          else if *mem1 == *mem2, return 0;
 *          else *mem1 < *mem2, return -1.
 */
int32_t memcmp(const void *mem1, const void *mem2, size_t count);

/**
 * memset - Fill a region of memory with the given value.
 * @param[in] mem    Pointer to the start of the area
 * @param[in] c      The byte to fill the area with
 * @param[in] count  The size of the area
 * @return  return the address of the area.
 */
void *memset(void *mem, uint8_t c, size_t count);

/**
 * memmove - Copy one area of memory to another.
 * @param[in] dst    Where to copy to
 * @param[in] src    Where to copy from
 * @param[in] count  The size of the area
 * @return  return the address of the dst area.
 *
 * *UNLIKE* memcpy(), memmove() copes with overlapping areas.
 */
void *memmove(void *dst, const void *src, size_t count);

/**
 * strcpy - Copy a NUL terminated string to another.
 * @param[in] dst  Where to copy the string to
 * @param[in] src  Where to copy the string from
 * @return  return the address of the dst area.
 */
char *strcpy(char *dst, const char *src);

/**
 * strncpy - Copy a length-limited string to another.
 * @param[in] dst    Where to copy the string to
 * @param[in] src    Where to copy the string from
 * @param[in] count  The maximum number of bytes to copy
 * @return  return the address of the dst area.
 */
char *strncpy(char *dst, const char *src, size_t count);

/**
 * strcat - Append one NUL-terminated string to another.
 * @param[in] dst  The string to be appended to
 * @param[in] src  The string to append to it
 * @return  return the address of the dst area.
 */
char *strcat(char *dst, const char *src);

/**
 * strncat - Append a length-limited string to another.
 * @param[in] dst    The string to be appended to
 * @param[in] src    The string to append to it
 * @param[in] count  The maximum numbers of bytes to copy
 * @return  return the address of the dst area.
 */
char *strncat(char *dst, const char *src, size_t count);

/**
 * strcmp - Compare two strings.
 * @param[in] str1  One string
 * @param[in] str2  Another string
 * @return  if *str1 > *str2, return 1;
 *          else if *str1 == *str2, return 0;
 *          else *str1 < *str2, return -1.
 */
int32_t strcmp(const char *str1, const char *str2);

/**
 * strncmp - Compare two length-limited strings.
 * @param[in] str1   One string
 * @param[in] str2   Another string
 * @param[in] count  The maximum number of bytes to compare
 * @return  if *str1 > *str2, return 1;
 *          else if *str1 == *str2, return 0;
 *          else *str1 < *str2, return -1.
 */
int32_t strncmp(const char *str1, const char *str2, size_t count);

/**
 * strchr - Find the first occurrence of a character in a string.
 * @param[in] str  The string to be searched
 * @param[in] c    The character to search for
 * @return  if find, return the address of the first occurrence;
 *          else return NULL.
 */
char *strchr(const char *str, char c);

/**
 * strrchr - Find the last occurrence of a character in a string.
 * @param[in] str  The string to be searched
 * @param[in] c    The character to search for
 * @return  if find, return the address of the first occurrence;
 *          else return NULL.
 */
char *strrchr(const char *str, char c);

/**
 * strnchr - Find the first occurrence of a character in a length-limited string.
 * @param[in] str    The string to be searched
 * @param[in] c      The character to search for
 * @param[in] count  The maximum number of bytes to be searched
 * @return  if find, return the address of the first occurrence;
 *          else return NULL.
 */
char *strnchr(const char *str, char c, size_t count);

/**
 * strlen - Compute the length of a string.
 * @param[in] str  The string to be computed
 * @return  return the size of the string.
 */
size_t strlen(const char *str);

/**
 * strnlen - Compute the length of a length-limited string.
 * @param[in] str    The string to be computed
 * @param[in] count  The maximum number of bytes to search
 * @return  return the size of the string or the count.
 */
size_t strnlen(const char *str, size_t count);

/**
 * strstr - Find the first substring in a NUL terminated string.
 * @param[in] str1  The string to be searched
 * @param[in] str2  The string to search for
 * @return  if find, return the address of the first occurrence;
 *          else return NULL.
 */
char *strstr(const char *str1, const char *str2);

/**
 * strnstr - Find the first substring in a length-limited string
 * @param[in] str1  The string to be searched
 * @param[in] str2  The string to search for
 * @param[in] len   The maximum number of characters to search
 * @return  if find, return the address of the first occurrence;
 *          else return NULL.
 */
char *strnstr(const char *str1, const char *str2, size_t len);

/**
 * strupr - Converted the string to uppercase
 * @param[in] str  The string to be converted
 * @return  return the address of the input string.
 */
char *strupr(char *str);

#endif /* LX_STRING_H */

