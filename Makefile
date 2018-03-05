CC ?= gcc
LFLAGS ?=
CFLAGS ?= -Wall -Werror $(LFLAGS)

sorts := heapsort quicksort mergesort
sort_executables := $(sorts:%=bin/%)

.PHONY: all debug

all: CFLAGS += -O3
all: $(sort_executables)

debug: CFLAGS += -O0 -DDEBUG -ggdb
debug: $(sort_executables)

bin/gen_arr: gen_arr.c | bin
	$(CC) -o bin/gen_arr $(CFLAGS) $(LFLAGS) gen_arr.c

bin/randarr.o: | bin/gen_arr bin
	rm -f ./bin/randarr.asm
	./bin/gen_arr 10000000 > bin/randarr.asm
	nasm -felf64 bin/randarr.asm -o bin/randarr.o

bin/%: %.c | bin/randarr.o bin
	$(CC) -o $@ $< $(CFLAGS) bin/randarr.o

bin:
	@mkdir bin

mostlyclean:
	@rm -f $(sort_executables)

clean:
	@rm -rf bin
