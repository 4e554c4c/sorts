#include <stdio.h>
#include "include/randarr.h"

/**
 * Macros to help heap index logic
 */
#define P(i) (i/2)
#define C(i) (2*i)

static inline void exch(uint32_t h[], uint32_t a, uint32_t b) {
	uint32_t temp = h[a];
	h[a] = h[b];
	h[b] = temp;
}

static void sink(uint32_t h[], uint32_t i, uint32_t n) {
	// As long as the current item has a child, continue.
	while (C(i) <= n) {
		// check the largest child
		uint32_t c = C(i);
		if (c < n && h[c] < h[c+1]) {
			++c;
		}
		if (h[i] > h[c]) {
			break;
		}
		exch(h,c,i);
		i = c;
	}
}

/**
 * Will sort the array in `randarr.h` and exit.
 * Naïve textbook method.
 */
int main() {
	// HACK: now the first index is at heap[1] instead of random_array[0].
	// Thanks C :)
	uint32_t *heap = random_array-1;
	uint32_t N = size;

	// Build the heap
	for (int k = N/2; k >= 1; --k) {
		sink(heap, k, N);
	}

	// Now sort it
	while (N > 1) {
		exch(heap,1,N);
		sink(heap,1,--N);
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
	return 0;
#endif
}
