#include <stdio.h>
#include "include/randarr.h"

static inline void exch(uint32_t s[], uint32_t a, uint32_t b) {
	uint32_t temp = s[a];
	s[a] = s[b];
	s[b] = temp;
}

int partition(uint32_t s[], int l, int h) {
	int p = h;           /* pivot element index */
	int first_high = l;  /* divider positioner for pivot element */

	for (int i = l; i < h; ++i) {
		if (s[i] < s[p]) {
			exch(s, i, first_high);
			++first_high;
		}
	}
	exch(s, p, first_high);

	return first_high;
}

void quicksort(uint32_t s[], int l, int h) {
	int p;

	if ((h-l)>0) {
		p = partition(s,l,h);
		quicksort(s,l,p-1);
		quicksort(s,p+1,h);
	}
}

int main() {
	quicksort(random_array, 0, size-1);

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
