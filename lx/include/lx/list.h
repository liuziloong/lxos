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

#ifndef LX_LIST_H
#define LX_LIST_H

typedef struct list_struct {
    struct list_struct *next;
    struct list_struct *prev;
} list_t;

static inline void list_init(list_t *node)
{
    node->next = node;
    node->prev = node;
}

static inline void list_insert(list_t *node, list_t *prev, list_t *next)
{
    next->prev = node;
    node->next = next;
    node->prev = prev;
    prev->next = node;
}

/* insert node before head */
static inline void list_insert_before(list_t *head, list_t *node)
{
    list_insert(node, head->prev, head);
}

/* insert node after head */
static inline void list_insert_after(list_t *head, list_t *node)
{
    list_insert(node, head, head->next);
}

static inline void list_remove(list_t *node)
{
    node->next->prev = node->prev;
    node->prev->next = node->next;

    node->next = node;
    node->prev = node;
}

static inline void list_replace(list_t *node, list_t *old)
{
    node->next       = old->next;
    node->next->prev = node;
    node->prev       = old->prev;
    node->prev->next = node;
}

#endif /* LX_LIST_H */

