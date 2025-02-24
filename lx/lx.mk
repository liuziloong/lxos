##
#  Copyright 2023 Andy andrew.lxos@gmail.com
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
##

NAME := lx

$(NAME)_TYPE := kernel

$(NAME)_CFLAGS := -Wall
#$(NAME)_CFLAGS += -Wextra
$(NAME)_CFLAGS += -Werror

$(NAME)_INCLUDES := ./mm

$(NAME)_DEPENDS := board mcu

$(NAME)_CSRCS := init/lx_main.c

$(NAME)_CSRCS += kernel/thread.c    \
                 kernel/tick.c      \
                 kernel/timer.c     \
                 kernel/workqueue.c

$(NAME)_CSRCS += libs/string.c \
                 libs/stdlib.c \
                 libs/printk.c \
                 libs/vsnprintf.c

$(NAME)_CSRCS += mm/mm.c \
                 mm/tlsf.c

GLOBAL_INCLUDES := ./include
