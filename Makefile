CFLAGS := -Wall -Werror -O0 -ggdb
LFLAGS :=

.PHONY: all run clean

all: heapsort mergesort quicksort

heapsort: heapsort.c | bin/randarr.o bin
	@gcc -o bin/heapsort $(CFLAGS) $(LFLAGS) heapsort.c bin/randarr.o

mergesort: mergesort.c | bin/randarr.o bin
	@gcc -o bin/mergesort $(CFLAGS) $(LFLAGS) mergesort.c bin/randarr.o

quicksort: quicksort.c | bin/randarr.o bin
	@gcc -o bin/quicksort $(CFLAGS) $(LFLAGS) quicksort.c bin/randarr.o

bin/randarr.o: gen_arr | bin
	@rm -f ./bin/randarr.asm
	@./bin/gen_arr 1000000 > bin/randarr.asm
	@nasm -felf64 bin/randarr.asm -o bin/randarr.o

gen_arr: gen_arr.c | bin
	@mkdir -p bin
	@gcc -o bin/gen_arr $(CFLAGS) $(LFLAGS) gen_arr.c

bin:
	@mkdir bin

clean:
	@rm -rf bin
