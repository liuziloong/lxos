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

#ifndef LX_TYPES_H
#define LX_TYPES_H

//#include <stdint.h>

#define NULL 0

//#if 0
typedef signed char   int8_t;
typedef unsigned char uint8_t;

typedef short          int16_t;
typedef unsigned short uint16_t;

typedef int          int32_t;
typedef unsigned int uint32_t;

typedef long long          int64_t;
typedef unsigned long long uint64_t;
//#endif

#ifndef LX_INT
#define LX_INT int
#endif

#ifndef LX_UINT
#define LX_UINT unsigned int
#endif

#ifndef LX_INT32
#define LX_INT32 int32_t
#endif

#ifndef LX_UINT32
#define LX_UINT32 uint32_t
#endif

#ifndef LX_ULONG
#define LX_ULONG unsigned long
#endif

typedef LX_INT   state_t;
typedef LX_INT   ssize_t;
typedef LX_UINT  size_t;
typedef LX_ULONG tick_t;

typedef LX_INT tid_t;

typedef LX_UINT uid_t;
typedef LX_UINT gid_t;

#endif /* LX_TYPES_H */

