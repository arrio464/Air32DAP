#
# Copyright (c) 2014-2015 0xc0170
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# This project was exported via the project generator.  More information https://github.com/project-generator/project_generator

CPU = cortex-m3

# toolchain specific
TOOLCHAIN = 
TOOLCHAIN_BINPATH = 'D:\Program Files\Keil_v5\ARM\ARMCLANG\bin\'
CC = $(TOOLCHAIN_BINPATH)$(TOOLCHAIN)armclang
CXX = $(TOOLCHAIN_BINPATH)$(TOOLCHAIN)armclang
AS = $(TOOLCHAIN_BINPATH)$(TOOLCHAIN)armclang
LD = $(TOOLCHAIN_BINPATH)$(TOOLCHAIN)armlink
AR = $(TOOLCHAIN_BINPATH)$(TOOLCHAIN)armar
CPP = $(TOOLCHAIN_BINPATH)$(TOOLCHAIN)armclang

OBJCOPY = $(TOOLCHAIN_BINPATH)$(TOOLCHAIN)fromelf
OBJDUMP = $(TOOLCHAIN_BINPATH)$(TOOLCHAIN)fromelf
SIZE = $(TOOLCHAIN_BINPATH)$(TOOLCHAIN)fromelf
NM = $(TOOLCHAIN_BINPATH)$(TOOLCHAIN)fromelf

# application specific
INSTRUCTION_MODE = thumb
TARGET = stm32f103xb_bl

TARGET_EXT = .axf
# Executables also produce hex and binary outputs.
ALL_TARGET_OUT_FILES = $(TARGET_OUT) $(TARGET_HEX) $(TARGET_BIN)


TARGET_OUT = $(OBJ_FOLDER)$(TARGET)$(TARGET_EXT)
TARGET_HEX = $(OBJ_FOLDER)$(TARGET).hex
TARGET_BIN = $(OBJ_FOLDER)$(TARGET).bin

LINKER_EXT = .sct

LD_SCRIPT_IN = ..\..\..\source\daplink\daplink.ac6.sct
LD_SCRIPT = $(OUT_DIR)/$(TARGET).generated$(LINKER_EXT)


CC_SYMBOLS =  -DDAPLINK_VERSION=259  -DMSC_ENDPOINT  -DDAPLINK_BL  -DDAPLINK_BUILD_KEY=0x9B939D93  -DDRAG_N_DROP_SUPPORT  -DOS_TICK=10000  -DINTERFACE_STM32F103XB  -DUSE_HAL_DRIVER  -DSTM32F103xB  -DDAPLINK_HIC_ID=0x97969908  -D__packed=__packed  -DDAPLINK_NO_ASSERT_FILENAMES  -DOS_CLOCK=72000000  -D__PROGRAM_START 
ASM_SYMBOLS = ${CC_SYMBOLS}


LIBS = 




LIB_PATHS = 


# directories
INC_DIRS =  ..\..\..\source\usb  ..\..\..\source\daplink  ..\..\..\source\daplink\bootloader  ..\..\..\source\cmsis-core  ..\..\..\source\hic_hal  ..\..\..\source\hic_hal\cmsis-driver  ..\..\..\source\daplink\drag-n-drop  ..\..\..\source\daplink\settings  ..\..\..\source\target  ..\..\..\source\rtos_none  ..\..\..\source\hic_hal\stm32\stm32f103xb  ..\..\..\source\hic_hal\stm32\stm32f103xb\cmsis  ..\..\..\source\hic_hal\stm32\stm32f103xb\STM32F1xx_HAL_Driver  ..\..\..\source\hic_hal\stm32\stm32f103xb\STM32F1xx_HAL_Driver\Inc 

OUT_DIR = build

INC_DIRS_F = -I. $(patsubst %, -I%, $(INC_DIRS))

SRC_DIRS =  ..\..\..\source\usb  ..\..\..\source\usb\msc  ..\..\..\source\daplink  ..\..\..\source\daplink\bootloader  ..\..\..\source\daplink\drag-n-drop  ..\..\..\source\daplink\settings  ..\..\..\source\target  ..\..\..\source\rtos_none  ..\..\..\source\hic_hal\stm32\stm32f103xb  ..\..\..\source\hic_hal\stm32\stm32f103xb\cmsis  ..\..\..\source\hic_hal\stm32\stm32f103xb\STM32F1xx_HAL_Driver\Src  ..\..\..\source\board  ..\..\..\source\hic_hal\stm32\stm32f103xb\armcc 

ifeq ($(strip $(OUT_DIR)), )
	OBJ_FOLDER =
else
	OBJ_FOLDER = $(strip $(OUT_DIR))/
endif

# Flags
COMMON_FLAGS = 
COMMON_FLAGS += --target=arm-arm-none-eabi -mcpu=$(CPU) -m$(INSTRUCTION_MODE)

C_FLAGS  =  --target=arm-arm-none-eabi  -Os  -flto  -g  --std=c99  -fdata-sections  -ffunction-sections  -fno-builtin  -fshort-enums  -fshort-wchar  -funsigned-char  -masm=auto  -nostdlib  -Wall  -Wno-error=cpp  -Warmcc-pragma-thumb  -Wno-ignored-optimization-argument  -Wno-unused-command-line-argument  -mno-unaligned-access 
CXX_FLAGS  = 
ASM_FLAGS  =  -g  -x assembler-with-cpp  -masm=auto  -Wa,armasm,--no_unaligned_access 

CFLAGS = $(COMMON_FLAGS) $(C_FLAGS) $(INC_DIRS_F) $(CC_SYMBOLS) -c -MMD
CXXFLAGS = $(COMMON_FLAGS) $(CXX_FLAGS) $(INC_DIRS_F) $(CC_SYMBOLS) -c -MMD
ASFLAGS = $(COMMON_FLAGS) $(ASM_FLAGS) $(INC_DIRS_F) $(ASM_SYMBOLS) -c
GENASMFLAGS = -S -W
OBJDUMPFLAGS = --text -acdyrz --interleave=source
SIZEFLAGS = --text -z
NMFLAGS = --text -arz

# Linker options
LD_OPTIONS +=  --bestdebug  --summary_stderr  --info=summarysizes,sizes,totals,unused,veneers  --load_addr_map_info  --xref  --callgraph  --symbols  --lto
LD_OPTIONS += --strict --scatter=$(LD_SCRIPT) --map --list $(OBJ_FOLDER)$(TARGET).map

# Flags to run only preprocessor
CPP_FLAGS = -E -xc --target=arm-arm-none-eabi -mcpu=$(CPU) -MMD


# Flags to preprocess the linker script
LD_CPP_FLAGS = 


ARFLAGS = cr

ifeq ($(OS),Windows_NT)
	RM = cmd /c rd /s /q
else
	RM = rm -rf
endif

C_SRCS :=  ..\..\..\source\board\stm32f103xb_bl.c  ..\..\..\source\daplink\HardFault_Handler.c  ..\..\..\source\daplink\bootloader\daplink.c  ..\..\..\source\daplink\bootloader\main_bootloader.c  ..\..\..\source\daplink\circ_buf.c  ..\..\..\source\daplink\cortex_m.c  ..\..\..\source\daplink\crc32.c  ..\..\..\source\daplink\daplink_debug.c  ..\..\..\source\daplink\drag-n-drop\file_stream.c  ..\..\..\source\daplink\drag-n-drop\flash_decoder.c  ..\..\..\source\daplink\drag-n-drop\flash_intf.c  ..\..\..\source\daplink\drag-n-drop\flash_manager.c  ..\..\..\source\daplink\drag-n-drop\iap_flash_intf.c  ..\..\..\source\daplink\drag-n-drop\intelhex.c  ..\..\..\source\daplink\drag-n-drop\vfs_manager.c  ..\..\..\source\daplink\drag-n-drop\vfs_user.c  ..\..\..\source\daplink\drag-n-drop\virtual_fs.c  ..\..\..\source\daplink\error.c  ..\..\..\source\daplink\flash_hal.c  ..\..\..\source\daplink\info.c  ..\..\..\source\daplink\sdk_stub.c  ..\..\..\source\daplink\settings\settings.c  ..\..\..\source\daplink\settings\settings_rom_stub.c  ..\..\..\source\daplink\util.c  ..\..\..\source\daplink\validation.c  ..\..\..\source\hic_hal\stm32\stm32f103xb\STM32F1xx_HAL_Driver\Src\air32f10x_rcc_ex.c  ..\..\..\source\hic_hal\stm32\stm32f103xb\STM32F1xx_HAL_Driver\Src\stm32f1xx_hal.c  ..\..\..\source\hic_hal\stm32\stm32f103xb\STM32F1xx_HAL_Driver\Src\stm32f1xx_hal_cortex.c  ..\..\..\source\hic_hal\stm32\stm32f103xb\STM32F1xx_HAL_Driver\Src\stm32f1xx_hal_dma.c  ..\..\..\source\hic_hal\stm32\stm32f103xb\STM32F1xx_HAL_Driver\Src\stm32f1xx_hal_flash.c  ..\..\..\source\hic_hal\stm32\stm32f103xb\STM32F1xx_HAL_Driver\Src\stm32f1xx_hal_flash_ex.c  ..\..\..\source\hic_hal\stm32\stm32f103xb\STM32F1xx_HAL_Driver\Src\stm32f1xx_hal_gpio.c  ..\..\..\source\hic_hal\stm32\stm32f103xb\STM32F1xx_HAL_Driver\Src\stm32f1xx_hal_gpio_ex.c  ..\..\..\source\hic_hal\stm32\stm32f103xb\STM32F1xx_HAL_Driver\Src\stm32f1xx_hal_rcc.c  ..\..\..\source\hic_hal\stm32\stm32f103xb\STM32F1xx_HAL_Driver\Src\stm32f1xx_hal_rcc_ex.c  ..\..\..\source\hic_hal\stm32\stm32f103xb\STM32F1xx_HAL_Driver\Src\stm32f1xx_hal_tim.c  ..\..\..\source\hic_hal\stm32\stm32f103xb\STM32F1xx_HAL_Driver\Src\stm32f1xx_hal_tim_ex.c  ..\..\..\source\hic_hal\stm32\stm32f103xb\STM32F1xx_HAL_Driver\Src\stm32f1xx_hal_uart.c  ..\..\..\source\hic_hal\stm32\stm32f103xb\STM32F1xx_HAL_Driver\Src\stm32f1xx_hal_usart.c  ..\..\..\source\hic_hal\stm32\stm32f103xb\cmsis\system_stm32f1xx.c  ..\..\..\source\hic_hal\stm32\stm32f103xb\flash.c  ..\..\..\source\hic_hal\stm32\stm32f103xb\gpio.c  ..\..\..\source\hic_hal\stm32\stm32f103xb\read_uid.c  ..\..\..\source\hic_hal\stm32\stm32f103xb\sdk.c  ..\..\..\source\hic_hal\stm32\stm32f103xb\uart.c  ..\..\..\source\hic_hal\stm32\stm32f103xb\usb_config.c  ..\..\..\source\hic_hal\stm32\stm32f103xb\usbd_STM32F103.c  ..\..\..\source\rtos_none\SysTick_Handler.c  ..\..\..\source\rtos_none\cmsis_os2_port.c  ..\..\..\source\target\target_board.c  ..\..\..\source\target\target_default.c  ..\..\..\source\usb\msc\usbd_core_msc.c  ..\..\..\source\usb\msc\usbd_msc.c  ..\..\..\source\usb\usbd_core.c 
C_OBJS := $(patsubst %.c,$(OBJ_FOLDER)%.o,$(notdir $(C_SRCS)))

CPP_SRCS := 
CPP_OBJS := $(patsubst %.cpp,$(OBJ_FOLDER)%.o,$(notdir $(CPP_SRCS)))

S_SRCS :=  ..\..\..\source\hic_hal\stm32\stm32f103xb\armcc\startup_stm32f103xb.S 
S_OBJS = $(patsubst %.s,$(OBJ_FOLDER)%.o,$(filter %.s,$(notdir $(S_SRCS))))
S_OBJS += $(patsubst %.S,$(OBJ_FOLDER)%.o,$(filter %.S,$(notdir $(S_SRCS))))

O_OBJS := 

ALL_OBJS := $(C_OBJS) \
	$(CPP_OBJS) \
	$(S_OBJS) \
	$(O_OBJS)

VPATH := $(SRC_DIRS)

#-------------------------------------------------------------------------------
# Logging options
#-------------------------------------------------------------------------------

# Enable color output by default.
USE_COLOR ?= 1

# Normally, commands in recipes are prefixed with '@' so the command itself
# is not echoed by make. But if VERBOSE is defined (set to anything non-empty),
# then the '@' is removed from recipes. The 'at' variable is used to control
# this.
ifeq "$(VERBOSE)" "1"
at :=
else
at := @
endif

# These colors must be printed with the printf command. echo won't handle the
# escape sequences.
color_default = \033[00m
color_bold = \033[01m
color_red = \033[31m
color_green = \033[32m
color_yellow = \033[33m
color_blue = \033[34m
color_magenta = \033[35m
color_cyan = \033[36m
color_orange = \033[38;5;172m
color_light_blue = \033[38;5;039m
color_gray = \033[38;5;008m
color_purple = \033[38;5;097m

ifeq "$(USE_COLOR)" "1"
color_build := $(color_light_blue)
color_c := $(color_green)
color_cxx := $(color_green)
color_cpp := $(color_orange)
color_asm := $(color_magenta)
color_ar := $(color_yellow)
color_link := $(color_cyan)
color_convert := $(color_gray)
endif

# Used in printmessage if the color args are not present.
color_ :=

# Use in recipes to print color messages if printing to a terminal. If
# USE_COLOR is not set to 1, this reverts to a simple uncolorized printf.
# A newline is added to the end of the printed message.
#
# Arguments:
#  1 - name of the color variable (see above), minus the "color_" prefix
#  2 - first colorized part of the message
#  3 - first uncolorized part of the message
#  4 - color name for second colorized message
#  5 - second colorized message
#  6 - second uncolorized part of the message
#  7 - uncolorized prefix on the whole line; this is last because it is expected to be used rarely
#
# All arguments are optional.
#
# Use like:
#  $(call printmessage,cyan,Building, remainder of the message...)
ifeq ($(OS),Windows_NT)
define printmessage
echo $(7)$(2)$(3)$(5)$(6)
endef
else
ifeq "$(USE_COLOR)" "1"
define printmessage
if [ -t 1 ]; then printf "$(7)$(color_$(1))$(2)$(color_default)$(3)$(color_$(4))$(5)$(color_default)$(6)\n" ; \
else printf "$(7)$(2)$(3)$(5)$(6)\n" ; fi
endef
else
define printmessage
printf "$(7)$(2)$(3)$(5)$(6)\n"
endef
endif
endif

#-------------------------------------------------------------------------------
# Recipes
#-------------------------------------------------------------------------------

# Compile C sources.
$(OBJ_FOLDER)%.o : %.c
	@$(call printmessage,c,Compiling, $<)
ifeq ($(GENERATE_ASSEMBLY),1)
	$(at)$(CC) $(CFLAGS) $(GENASMFLAGS) $<
endif
	$(at)$(CC) $(CFLAGS) $< -o $@
ifeq ($(DISASSEMBLE_OBJECTS),1)
	$(at)$(OBJDUMP) $(OBJDUMPFLAGS) $@ --output $(@:%.o=%.lst)
endif

# Compile C++ sources.
$(OBJ_FOLDER)%.o : %.cpp
	@$(call printmessage,cxx,Compiling, $<)
ifeq ($(GENERATE_ASSEMBLY),1)
	$(at)$(CXX) $(CFLAGS) $(GENASMFLAGS) $<
endif
	$(at)$(CXX) $(CXXFLAGS) $< -o $@
ifeq ($(DISASSEMBLE_OBJECTS),1)
	$(at)$(OBJDUMP) $(OBJDUMPFLAGS) $@ --output $(@:%.o=%.lst)
endif

# Preprocess and assemble .S sources.
$(OBJ_FOLDER)%.o : %.S
	@$(call printmessage,asm,Assembling, $<)
	$(at)$(AS) $(ASFLAGS) $< -o $@

# Assemble .s sources.
$(OBJ_FOLDER)%.o : %.s
	@$(call printmessage,asm,Assembling, $<)
	$(at)$(AS) $(ASFLAGS) $< -o $@

#-------------------------------------------------------------------------------
# Rules
#-------------------------------------------------------------------------------

PRE_BUILD_SCRIPT := \
	$(shell ..\..\..\tools/pre_build_script.py)

all: $(ALL_TARGET_OUT_FILES)
	$(at)-..\..\..\tools/post_build_script_armclang.py

# Make the build directory an order-only prerequisite for everything that goes in it.
$(ALL_TARGET_OUT_FILES) $(ALL_OBJS) $(LD_SCRIPT): | $(OUT_DIR)

$(OUT_DIR):
ifeq ($(OS),Windows_NT)
	$(at)-mkdir $(OUT_DIR)
else
	$(at)$(shell mkdir $(OBJ_FOLDER) 2>/dev/null)
endif



# Tool invocations

$(LD_SCRIPT): $(LD_SCRIPT_IN)
	@$(call printmessage,cpp,Preprocessing, $<)
	$(at)$(CPP) $(CPP_FLAGS) $(LD_CPP_FLAGS) $(INC_DIRS_F) $(CC_SYMBOLS) $< -o $@


$(TARGET_OUT): $(LD_SCRIPT) $(C_OBJS) $(CPP_OBJS) $(S_OBJS)
	@$(call printmessage,link,Linking, $@)
	$(at)$(LD) $(LIB_PATHS) -o $@ $(CPP_OBJS) $(C_OBJS) $(S_OBJS) $(O_OBJS) $(LIBS) $(LD_OPTIONS)
	$(at)$(SIZE) $(SIZEFLAGS) $(TARGET_OUT)
	$(at)-$(NM) $(NMFLAGS) $(TARGET_OUT) --output $(OBJ_FOLDER)$(TARGET)-symbol-table.txt

$(TARGET_HEX): $(TARGET_OUT)
	@$(call printmessage,convert,Converting, $@)
	$(at)@$(OBJCOPY) --i32combined $(TARGET_OUT) --output $(TARGET_HEX)

$(TARGET_BIN): $(TARGET_OUT)
	@$(call printmessage,convert,Converting, $@)
	$(at)@$(OBJCOPY) --bincombined $(TARGET_OUT) --output $(TARGET_BIN)



# Other Targets
clean:
	@echo 'Removing entire out directory'
ifeq ($(OS),Windows_NT)
	$(at)-$(RM) $(subst /,\\,$(OBJ_FOLDER))
else
	$(at)$(RM) $(OBJ_FOLDER)* $(OBJ_FOLDER)
endif
	@echo ' '

help:
	@echo "Useful targets:"
	@echo " - all (default)"
	@echo " - clean"
	@echo " - help"
	@echo
	@echo "Options:"
	@echo " - VERBOSE={0|1} to show full command lines."
	@echo " - USE_COLOR={0|1} to override color output."

.PHONY: all clean help

# Include dependencies
-include $(ALL_OBJS:.o=.d)


# Include the linker script dependencies
-include $(LD_SCRIPT:.sct=.d)
