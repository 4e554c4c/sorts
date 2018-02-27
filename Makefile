CFLAGS := -Wall -Werror -O0
LFLAGS :=

.PHONY: all run clean

all: mergesort

mergesort: randarr.h mergesort.c
	@gcc -o bin/mergesort $(CFLAGS) $(LFLAGS) mergesort.c

randarr.h: gen_arr
	@mkdir -p include
	@rm -f ./include/randarr.h
	@./bin/gen_arr 100 > ./include/randarr.h

gen_arr: gen_arr.c
	@mkdir -p bin
	@gcc -o bin/gen_arr $(CFLAGS) $(LFLAGS) gen_arr.c

clean:
	@rm -rf include bin
