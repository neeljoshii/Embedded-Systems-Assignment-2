# Use the C compiler
CC = arm-none-eabi-gcc

# Added floating point hardware flags for the STM32F4
CFLAGS = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -g -O0
CFLAGS += -Iinclude -Iconfig -Ifreertos -Ifreertos/include -Ifreertos/portable -Isrc

# Point back to main.c
SRCS = src/main.c src/key_task.c src/ntp_task.c src/speech_task.c
SRCS += freertos/tasks.c freertos/queue.c freertos/list.c 
SRCS += freertos/port.c freertos/heap_4.c

ASMS = startup/startup_stm32.s

# Linker Script and specs for baremetal printf
LDFLAGS = -T linker/stm32.ld -nostartfiles --specs=nosys.specs

all: build/firmware.elf

build/firmware.elf:
	mkdir -p build
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRCS) $(ASMS) -o build/firmware.elf

clean:
	rm -rf build