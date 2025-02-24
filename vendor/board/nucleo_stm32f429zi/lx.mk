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

NAME := board

$(NAME)_TYPE := bsp

$(NAME)_CFLAGS :=

$(NAME)_CSRCS := ./src/stm32f4xx_hal_msp.c    \
                 ./src/stm32f4xx_nucleo_144.c \
                 ./src/system_stm32f4xx.c

$(NAME)_ASRCS :=

GLOBAL_CFLAGS := -mcpu=cortex-m4 -mthumb -DSTM32F429xx -DHAL_UART_MODULE_ENABLED

GLOBAL_INCLUDES := ./include
