#include <stdlib.h>
#include <stdio.h>
#include "include/randarr.h"

void merge(uint32_t a[], uint32_t aux[], int lo, int mid, int hi) {
	int i = lo, j = mid+1;
	for (int k = lo; k <= hi; ++k) {
		if (i > mid) {
			aux[k] = a[j++];
		}
		else if (j > hi) {
			aux[k] = a[i++];
		}
		else if (a[j] < a[i]) {
			aux[k] = a[j++];
		} else {
			aux[k] = a[i++];
		}
	}
}

void sort(uint32_t a[], uint32_t aux[], int lo, int hi) {
	if (hi <= lo) {
		return;
	}
	int mid = (lo+hi) / 2;
	//swap aux and a
	sort (aux, a, lo, mid);
	sort (aux, a, mid+1, hi);
	merge(aux, a, lo, mid, hi);
}

int main() {
	sort(random_array, scrap_array, 0, size-1);

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
}
