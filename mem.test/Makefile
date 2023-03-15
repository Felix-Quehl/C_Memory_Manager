name = test.out
HEADERS = -I./header -I../mem/header
LIBRARIES = -L../mem -lmem

trash = $(shell find ./ -name '*.o') $(name) *.profraw *.profdata
sources = $(shell find ./code -name '*.c')
objects = $(sources:.c=.o)

SHELL := /bin/bash
CC = clang
CFLAGS = -Weverything -Wall -Wextra -Werror -Wpedantic -Wno-poison-system-directories $(HEADERS)
LDFLAGS = $(LIBRARIES)

all: release

release: $(name)

debug: CFLAGS += -g
debug: CFLAGS += -fprofile-instr-generate -fcoverage-mapping
debug: LDFLAGS += -fprofile-instr-generate -fcoverage-mapping
debug: $(name)

$(name): $(objects) 
	$(CC) $(LDFLAGS) $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) $(headers) -o $@ -c $< 

clean:
	rm -rf $(trash)

.ONESHELL:
