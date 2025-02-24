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

NAME := mcu

$(NAME)_TYPE := bsp

$(NAME)_CFLAGS := -DSTM32F429xx -DHAL_UART_MODULE_ENABLED

$(NAME)_CFLAGS += -I./include \
                  -I./init    \
                  -I./driver


$(NAME)_CSRCS := drivers/Src/stm32f4xx_hal_adc.c    \
                 drivers/Src/stm32f4xx_hal_adc_ex.c \
                 drivers/Src/stm32f4xx_hal_uart.c   \
                 drivers/Src/stm32f4xx_hal.c        \
                 drivers/Src/stm32f4xx_hal_usart.c  \
                 drivers/Src/stm32f4xx_hal_gpio.c   \
                 drivers/Src/stm32f4xx_hal_dma.c    \
                 drivers/Src/stm32f4xx_hal_pwr_ex.c \
                 drivers/Src/stm32f4xx_hal_rcc.c    \
                 drivers/Src/stm32f4xx_hal_cortex.c

$(NAME)_CSRCS += lxos/intrpt.c \
                 lxos/mm.c     \
                 startup/startup.c

$(NAME)_ASRCS := startup/startup_stm32f429zi.s

GLOBAL_CFLAGS := -mcpu=cortex-m4 -mthumb -DSTM32F429xx -DHAL_UART_MODULE_ENABLED -fno-tree-scev-cprop

GLOBAL_INCLUDES := ./drivers/Inc                       \
                   ./cmsis/Include                     \
                   ./cmsis/Device/ST/STM32F4xx/Include \
				   ./startup
