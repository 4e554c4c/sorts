#include <stdio.h>
#include "include/randarr.h"

int main() {
	for (int i = 1; i < size; ++i) {
		uint32_t tmp = random_array[i];
		int j;
		for (j = i; j > 0 && random_array[j-1] > random_array[j]; --j) {
			random_array[j]=random_array[j-1];
		}
		random_array[j]=tmp;
	}

#ifdef DEBUG
	// Now print the array for testing :)
	puts("arr:\t{");
	for (int i = 0; i < size; ++i) {
		if (i % 10 == 0 && i != 0) {
			putchar('\n');
		}
		printf("%u,", random_array[i]);
	}
	puts("};\n");
#endif
	return 0;
}
