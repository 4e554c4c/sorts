#define _XOPEN_SOURCE 700
#define _POSIX_C_SOURCE 200809L
#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * Write an assembly file containing a random array.
 */
int main(int argc, char **argv) {
	if (argc != 2|| strcmp(argv[1], "-h") == 0) {
		fprintf(stderr, "FORMAT: gen_arr [-h] `num_lines`\n");
		exit(EXIT_FAILURE);
	}
	int num_items = atoi(argv[1]);
	int fd = open("/dev/urandom", O_RDONLY);

	assert(num_items > 0 && fd > 0);
	uint32_t buff_size = (10000 < num_items+1) ? 10000 : num_items;
	uint32_t *rand_arr = calloc(sizeof(uint32_t), buff_size);
	assert(rand_arr);

	printf("section .data\n"          \
		"align 4\n"               \
		"global size\n"           \
		"size:\n"                 \
		"\tdd %d\n"               \
		"global _random_array\n"  \
		"_random_array:", num_items);
	for (int i = 0; i < num_items; ++i) {
		if ((i%buff_size) == 0) {
			assert(read(fd, rand_arr, sizeof(uint32_t) * buff_size) > 0);
		}
		if (i % 10 == 0) {
			putchar('\n');
			printf("\tdd ");
		}
		printf("%u, ", rand_arr[i%buff_size]);
	}

	return 0;
}
