# Dirs
CMSIS_STM32F7 = /home/dolaprolorap/STM32CubeF7/Drivers/CMSIS
CMSIS_TEMPLATES = $(CMSIS_STM32F7)/Device/ST/STM32F7xx/Source/Templates
SRCDIR = ./src
BINDIR = ./bin
INCDIR = ./include

# Files
SRCS = ./src/main.c ./src/usart.c ./src/timers.c ./src/buttons.c ./src/gpio.c ./src/leds.c
CMSIS_SRCS = $(CMSIS_TEMPLATES)/system_stm32f7xx.c
CMSIS_ASMS = $(CMSIS_TEMPLATES)/gcc/startup_stm32f767xx.s
OBJS = $(SRCS:./src/%.c=$(BINDIR)/%.o) \
       $(CMSIS_SRCS:$(CMSIS_TEMPLATES)/%.c=$(BINDIR)/%.o) \
       $(CMSIS_ASMS:$(CMSIS_TEMPLATES)/gcc/%.s=$(BINDIR)/%.o)

# Utils
AS := arm-none-eabi-as
CC := arm-none-eabi-gcc
LD := arm-none-eabi-ld
OBJCOPY := arm-none-eabi-objcopy

# Compiler settings
CPPFLAGS := -I$(CMSIS_STM32F7)/Device/ST/STM32F7xx/Include
CPPFLAGS += -I$(CMSIS_STM32F7)/Include
CPPFLAGS += -I$(INCDIR)
CPPFLAGS += -DSTM32F767xx
CFLAGS := -mcpu=cortex-m3 -g -std=c17 -Wall -Wextra -Wpedantic
CFLAGS += -Os
LDSCRIPT := ./stm32f767.ld

flash: $(BINDIR)/main.bin
	$(info === Flashing MC ===)
	st-flash --connect-under-reset write $< 0x08000000

$(BINDIR)/main.bin: $(BINDIR)/main.elf
	$(info === Making binary main.bin ===)
	$(OBJCOPY) -O binary $< $@

$(BINDIR)/main.elf: $(LDSCRIPT) $(OBJS)
	$(info === Linking ===)
	$(LD) -o $@ -T $^

$(BINDIR)/%.o: ./src/%.c | $(BINDIR)
	$(info === Compiling $@ ===)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

$(BINDIR)/%.o: $(CMSIS_TEMPLATES)/%.c | $(BINDIR)
	$(info === Compiling $@ ===)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

$(BINDIR)/%.o: $(CMSIS_TEMPLATES)/gcc/%.s | $(BINDIR)
	$(info === Compiling $@ ===)
	$(AS) $(ASFLAGS) -o $@ $<

clean:
	$(info === Cleaning ===)
	rm -f $(BINDIR)/*.o $(BINDIR)/*.elf $(BINDIR)/*.bin
    