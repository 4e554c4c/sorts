#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/randarr.h"
#ifndef CUTOFF
#  define CUTOFF 7
#endif

static inline void insertion_sort(uint32_t s[], uint32_t lo, uint32_t hi) {
	for (int i = lo+1; i <= hi; ++i) {
		uint32_t tmp = s[i];
		int j;
		for (j = i; j > lo && s[j] < s[j-1]; --j) {
			s[j-1]=s[j];
		}
		s[j]=tmp;
	}
}

void merge(uint32_t src[], uint32_t dst[], int lo, int mid, int hi) {
	int i = lo, j = mid+1;
	for (int k = lo; k <= hi; ++k) {
		if (i > mid) {
			dst[k] = src[j++];
		} else if (j > hi) {
			dst[k] = src[i++];
		} else if(src[j] < src[i]) {
			dst[k] = src[j++];
		} else {
			dst[k] = src[i++];
		}
	}
}

void sort(uint32_t src[], uint32_t dst[], int lo, int hi) {
	if (hi <= lo + CUTOFF) {
		insertion_sort(dst,lo,hi);
		return;
	}
	int mid = (lo+hi) / 2;
	sort (dst, src, lo, mid);
	sort (dst, src, mid+1, hi);
	merge(src, dst, lo, mid, hi);
}

int main() {
	uint32_t *scrap_array = malloc(sizeof(uint32_t) * size);
	memcpy(scrap_array, random_array, sizeof(uint32_t) * size);
	sort(scrap_array, random_array, 0, size-1);
	free(scrap_array);

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
