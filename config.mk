# See LICENSE file for copyright and license details.

LIB_NAME = libfe310

OBJ_DIR = obj
OUT_DIR = out
SRC_DIR = src

CROSS_COMPILE ?= riscv32-unknown-elf-
AR := $(CROSS_COMPILE)ar
CC := $(CROSS_COMPILE)gcc

CFLAGS  += -pipe -std=c99 -Wpedantic -Wall -Wextra
CFLAGS  += -mabi=ilp32 -march=rv32imac_zicsr_zifencei
CFLAGS  += -mcpu=sifive-e31 -mtune=sifive-e31 -mcmodel=medlow
CFLAGS  += -Iinc/
ifeq ($(DEBUG), 1)
	CFLAGS += -g -Og
else
	CFLAGS += -Os
endif
LDFLAGS += -nostdlib
