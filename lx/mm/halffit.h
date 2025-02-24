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

#ifndef MM_HALFFIT_H
#define MM_HALFFIT_H

void halffit_init(void);

void *halffit_malloc(size_t size);

void *halffit_zalloc(size_t size);

void *halffit_realloc(void *oldmem, size_t size);

void halffit_free(void *mem);

void halffit_check(void);

#endif /* MM_HALFFIT_H */

