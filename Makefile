include .config

include VERSION

unexport GREP_OPTIONS
unexport LC_ALL
LC_COLLATE = C
LC_NUMERIC = C
export LC_COLLATE
export LC_NUMERIC

############################################################

ARCH     := $(patsubst "%",%,$(strip $(CONFIG_ARCH)))
ARCH_DIR := ./lx/arch/$(ARCH)

MCU     := $(patsubst "%",%,$(strip $(CONFIG_MCU)))
MCU_DIR := ./vendor/mcu/$(MCU)

BOARD     := $(patsubst "%",%,$(strip $(CONFIG_BOARD)))
BOARD_DIR := ./vendor/board/$(BOARD)

APPS      := $(patsubst "%",%,$(strip $(CONFIG_APPS)))
APPS_DIR  := ./apps/$(APPS)

OUT := ./out

TARGET := $(OUT)/lx

############################################################

HOSTCC       := gcc
HOSTCXX      := g++
HOSTCFLAGS   := -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer -std=gnu89
HOSTCXXFLAGS := -O2

############################################################

CROSS_COMPILE := arm-none-eabi-

AS      := $(CROSS_COMPILE)as
CC      := $(CROSS_COMPILE)gcc
LD      := $(CROSS_COMPILE)ld
AR      := $(CROSS_COMPILE)ar
NM      := $(CROSS_COMPILE)nm
STRIP   := $(CROSS_COMPILE)strip
OBJCOPY := $(CROSS_COMPILE)objcopy
OBJDUMP := $(CROSS_COMPILE)objdump

ARFLAGS :=

ASFLAGS :=

CFLAGS := -g -c

CFLAGS += -fno-builtin   \
          -nodefaultlibs \
          -nostartfiles

CFLAGS += -nostdinc -nostdlib

CFLAGS += -s -O0          \
          -fdata-sections \
          -ffunction-sections

CFLAGS += -Wall
#CFLAGS += -Wextra
#CFLAGS += -Werror=implicit-function-declaration \
          -Werror=implicit-int                  \
          -Werror=incompatible-pointer-types    \
          -Werror=return-type                   \
          -Werror=shadow                        \
          -Werror=return-local-addr             \
          -Werror=uninitialized                 \
          -Werror=format                        \
          -Werror=sign-compare                  \
          -Werror=int-conversion
CFLAGS += -Werror

CFLAGS += $(shell sed -e '/\#/d' .config | sed -e '/^$$/d' | sed -e 's/CONFIG/-DCONFIG/g')

LDFLAGS :=

LDS := -T$(if $(wildcard $(BOARD_DIR)/$(BOARD).ld),$(BOARD_DIR)/$(BOARD).ld,$(MCU_DIR)/$(MCU).ld)

############################################################
UNITS :=
UNITS_NAME :=

LX_MKS := $(wildcard $(MCU_DIR)/lx.mk)
LX_MKS += $(wildcard $(BOARD_DIR)/lx.mk)
LX_MKS += ./lx/lx.mk
LX_MKS += $(wildcard $(APPS_DIR)/lx.mk)

define lxmk_check_func
	$(eval NAME := )
	$(eval include $(1))
	$(if $(NAME),,$(error "INVALID LX MAKEFILE: NAME is NULL!!!  $(1)"))
	$(if $(findstring $(NAME),$(UNITS_NAME)),                                \
         $(error "INVALID LX MAKEFILE: NAME ***$(NAME)*** EXISTS!!!  $(1)"), \
         $(eval UNITS_NAME += $(NAME)))
endef

define get_global_settings_func
	$(eval include $(1))
	$(eval CFLAGS += $(GLOBAL_CFLAGS))
	$(eval CFLAGS += $(subst /./,/,$(patsubst %,-I$(dir $(1))%,$(GLOBAL_INCLUDES))))
	$(eval GLOBAL_CFLAGS := )
	$(eval GLOBAL_INCLUDES := )
endef

define build_cobj_func
	$(shell mkdir -p $(OUT)/$(dir $(1)))
	$(shell $(CC) $(CFLAGS) $(2) -o $(OUT)/$(patsubst %c,%o,$(1)) $(1))
endef

define build_aobj_func
	$(shell mkdir -p $(OUT)/$(dir $(1)))
	$(shell $(AS) $(ASFLAGS) $(2) -o $(OUT)/$(patsubst %s,%o,$(1)) $(1))
endef

define build_unit_func
	$(eval NAME := )
	$(eval include $(1))
	$(eval UNIT := $(subst .,$(OUT),$(dir $(1)))$(NAME).a)
	$(eval UNITS += $(UNIT))
	$(eval UNIT_CFLAGS := $(subst /./,/,$(patsubst -I%,-I$(dir $(1))%,$($(NAME)_CFLAGS))))
	$(eval UNIT_CFLAGS += $(subst /./,/,$(patsubst %,-I$(dir $(1))%,$($(NAME)_INCLUDES))))
	$(eval UNIT_ASFLAGS := $($(NAME)_ASFLAGS))
	$(eval CSRCS := $(subst /./,/,$(patsubst %,$(dir $(1))%,$($(NAME)_CSRCS))))
	$(eval ASRCS := $(subst /./,/,$(patsubst %,$(dir $(1))%,$($(NAME)_ASRCS))))
	$(eval COBJS := $(CSRCS:%.c=$(OUT)/%.o))
	$(eval AOBJS := $(ASRCS:%.s=$(OUT)/%.o))
	$(eval $(foreach csrc,$(CSRCS),$(call build_cobj_func,$(csrc),$(UNIT_CFLAGS))))
	$(eval $(foreach asrc,$(ASRCS),$(call build_aobj_func,$(asrc),$(UNIT_ASFLAGS))))
	$(shell $(AR) -r $(UNIT) $(AOBJS) $(COBJS))
	@echo "\033[36mUNIT:\t$(UNIT)\033[0m\n"
	@echo "\033[31mCFLAGS:\033[0m $(UNIT_CFLAGS)\n" | sed 's/ /\n\t/g'
	@echo "\033[31mASFLAGS:\033[0m $(UNIT_ASFLAGS)\n" | sed 's/ /\n\t/g'
	@echo "\033[31mCSRCS:\033[0m $(CSRCS)\n" | sed 's/ /\n\t/g'
	@echo "\033[31mASRCS:\033[0m $(ASRCS)\n" | sed 's/ /\n\t/g'
endef

define build_target_func
	$(shell $(CC) $(LDS) -nostdlib -nostartfiles -Wl,-Map=$(TARGET).map -Wl,--gc-sections -o $(TARGET).elf -Wl,--whole-archive $(1))
	$(shell $(OBJCOPY) -O binary $(TARGET).elf $(TARGET).bin)
endef

############################################################

RESULT_SUCCESS := "==================== BUILD SUCCESS ===================="
RESULT_FAILURE := "==================== BUILD FAILURE ===================="

all: step3

step1:
	@echo "\033[33m\n--------------------    STEP  1    --------------------\n\033[0m"
	$(if $(wildcard $(TARGET).elf),$(shell mv $(TARGET).elf $(TARGET).elf.oldo))
	$(if $(wildcard $(TARGET).bin),$(shell mv $(TARGET).bin $(TARGET).bin.oldo))
	$(foreach lxmk,$(LX_MKS),$(call lxmk_check_func,$(lxmk)))
	$(foreach lxmk,$(LX_MKS),$(call get_global_settings_func,$(lxmk)))
	@echo "\033[31mBOARD:\033[0m $(BOARD)  \033[31mMCU:\033[0m $(MCU)\n"
	@echo "\033[31mLXMKS:\033[0m $(LX_MKS)" | sed 's/ /\n\t/g'
	@echo "\033[31mCFLAGS:\033[0m\n$(CFLAGS)\n"
	@echo "\033[31mASFLAGS:\033[0m\n$(ASFLAGS)\n"
	@echo "\033[31mLDSCRIPT:\033[0m $(LDS)\n"

step2: step1
	@echo "\033[33m\n--------------------    STEP  2    --------------------\n\033[0m"
	$(foreach lxmk,$(LX_MKS),$(call build_unit_func,$(lxmk)))

step3: step2
	@echo "\033[33m\n--------------------    STEP  3    --------------------\n\033[0m"
	$(call build_target_func,$(UNITS))
	@echo "\033[31mTARGET:\033[0m $(TARGET).elf $(TARGET).bin\n"
	@echo "\033[31mUNITS:\033[0m$(UNITS)" | sed 's/ /\n\t/g'
	@if [ -f $(TARGET).bin ];                          \
	 then echo "\033[31m\n$(RESULT_SUCCESS)\n\033[0m"; \
	 else echo "\033[35m\n$(RESULT_FAILURE)\n\033[0m"; \
	 fi

#	$(if $(wildcard $(TARGET).bin),                    \
         @echo "\033[33m\n$(RESULT_SUCCESS)\n\033[0m", \
         @echo "\033[33m\n$(RESULT_FAILURE)\n\033[0m")

############################################################

clean:
	@rm -rf $(OUT)/*

include scripts/Makefile.menuconfig
