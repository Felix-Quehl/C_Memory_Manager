name = libmem.so
HEADERS = -I./header

trash = $(shell find ./ -name '*.o') $(name)
sources = $(shell find ./code -name '*.c')
objects = $(sources:.c=.o)

SHELL := /bin/bash
CC = clang
CFLAGS = -Weverything -Wall -Wextra -Werror -Wpedantic -fno-inline -Wno-poison-system-directories $(HEADERS)
LDFLAGS = --shared

all: release

release: $(name)

debug: CFLAGS += -g
debug: $(name)

$(name): $(objects)
	$(CC) $(LDFLAGS) $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) $(headers) -o $@ -c $< 

clean:
	rm -rf $(trash)

.ONESHELL: