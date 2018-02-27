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
 * Ok, so We're going to write a valid C header to stdout that contains a random
 * array of size bytes.
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

	printf("#include<stdint.h>\n" \
		"uint32_t size = %d;\n" \
		"uint32_t random_array[%d]={", num_items, num_items);
	for (int i = 0; i < num_items; ++i) {
		if ((i%buff_size) == 0) {
			assert(read(fd, rand_arr, sizeof(uint32_t) * buff_size) > 0);
		}
		if (i % 10 == 0) {
			putchar('\n');
		}
		printf("%u,", rand_arr[i%buff_size]);
	}
	puts("};\n");

	return 0;
}
