#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/randarr.h"

void merge(uint32_t a[], uint32_t aux[], int lo, int mid, int hi) {
	// Copy from a to aux
	memcpy(&aux[lo],&a[lo], (1+hi-lo)*sizeof(uint32_t));

	int i = lo, j = mid+1;
	for (int k = lo; k <= hi; ++k) {
		if (i > mid) {
			a[k] = aux[j++];
		}
		else if (j > hi) {
			a[k] = aux[i++];
		}
		else if (aux[j] < aux[i]) {
			a[k] = aux[j++];
		} else {
			a[k] = aux[i++];
		}
	}

}

void sort(uint32_t a[], uint32_t aux[], int lo, int hi) {
	if (hi <= lo) {
		return;
	}
	int mid = (lo+hi) / 2;
	//swap aux and a
	sort (a, aux, lo, mid);
	sort (a, aux, mid+1, hi);
	merge(a, aux, lo, mid, hi);
}

int main() {
	uint32_t *scrap_array = malloc(sizeof(uint32_t) * size);
	sort(random_array, scrap_array, 0, size-1);

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
