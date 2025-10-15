#include <stdio.h>
#include "hii.h"

int main() {
	HashIntInt *hii = hii_new();
	int n = 10;

	for (int i = 0; i < n; i++) {
		hii_set(hii, i, i);
	}

	for (int i = 0; i < n; i++) {
		int *y = hii_get(hii, i);
		if (y) printf("%d\n", *y);
		else printf("could not find %d\n", i);
	}

	printf("Removing evens\n");

	for (int i = 0; i < n; i += 2) {
		hii_erase(hii, i);
	}

	for (int i = 0; i < n; i++) {
		int *y = hii_get(hii, i);
		if (y) printf("%d\n", *y);
		else printf("could not find %d\n", i);
	}

	printf("Reinserting evens\n");

	for (int i = 0; i < n; i += 2) {
		hii_set(hii, i, i);
	}

	for (int i = 0; i < n; i++) {
		int *y = hii_get(hii, i);
		if (y) printf("%d\n", *y);
		else printf("could not find %d\n", i);
	}

	printf("Setting all odds to 0\n");

	for (int i = 1; i < n; i += 2) {
		hii_set(hii, i, 0);
	}

	for (int i = 0; i < n; i++) {
		int *y = hii_get(hii, i);
		if (y) printf("%d\n", *y);
		else printf("could not find %d\n", i);
	}

	return 0;
}
