CFLAGS := -Wall -Werror -O0 -ggdb
LFLAGS :=

.PHONY: all run clean

all: heapsort quicksort

heapsort: heapsort.c | randarr.h bin
	@gcc -o bin/heapsort $(CFLAGS) $(LFLAGS) heapsort.c

quicksort: quicksort.c | randarr.h bin
	@gcc -o bin/quicksort $(CFLAGS) $(LFLAGS) quicksort.c

randarr.h: gen_arr | include
	@rm -f ./include/randarr.h
	@./bin/gen_arr 10000000 > ./include/randarr.h

gen_arr: gen_arr.c | bin
	@mkdir -p bin
	@gcc -o bin/gen_arr $(CFLAGS) $(LFLAGS) gen_arr.c

include:
	@mkdir include

bin:
	@mkdir bin

clean:
	@rm -rf include bin
