#include "hash.h"

void hii_print(HashIntInt *hii) {
	for (int i = 0; i < hii->cap; i++) {
		if (hii->data[i].exists == 1) printf("%d: <%d, %d>\n", i, hii->data[i].key, hii->data[i].val);
		else if (hii->data[i].exists == 2) printf("%d: <DEAD>\n", i);
		else if (hii->data[i].exists == 0) printf("%d: <DNE>\n", i);
	}
}

int hash(int x, int range) {
	uint32_t ux = (uint32_t) x;
	ux ^= ux >> 16;
	ux *= 0x85ebca6b;
	ux ^= ux >> 13;
	ux *= 0xc2b2ae35;
	ux ^= ux >> 16;
	int res = (int) ux;
	return res >= 0 ? res % range : -res % range;
}

int* hii_get(HashIntInt* hii, int key) {
	int h = hash(key, hii->cap);
	for (int i = 0; i < hii->cap && (hii->data[h].key != key || hii->data[h].exists != 1); i++) h = (h + 1) % hii->cap;
	if (hii->data[h].exists != 1 || hii->data[h].key != key) return NULL;
	return &(hii->data[h].val);
}

void hii_set(HashIntInt* hii, int key, int val) {
	if (hii->true_size == hii->cap) hii_expand(hii);
	int h = hash(key, hii->cap);
	for (int i = 0; i < hii->cap && hii->data[h].exists && (hii->data[h].key != key || hii->data[h].exists == 2); i++) 
		h = (h + 1) % hii->cap;
	hii->data[h].key = key;
	hii->data[h].val = val;
	if (!hii->data[h].exists) {
		hii->true_size++;
		hii->size++;
		hii->data[h].exists = 1;
	}
}

void hii_erase(HashIntInt *hii, int key) {
	int h = hash(key, hii->cap);
	for (int i = 0; i < hii->cap && (hii->data[h].key != key || hii->data[h].exists != 1); i++) h = (h + 1) % hii->cap;
	if (hii->data[h].exists != 1 || hii->data[h].key != key) return;
	hii->data[h].exists = 2;
	hii->size--;
}

void hii_expand(HashIntInt* hii) {
	IntPair* data_copy = malloc(hii->size * sizeof(IntPair));
	for (int k = 0, i = 0; i < hii->cap; i++) {
		if (hii->data[i].exists) {
			data_copy[k] = hii->data[i];
			k++;
		}
	}
	free(hii->data);
	hii->cap *= 2;
	hii->data = malloc(hii->cap * sizeof(IntPair));
	int n = hii->size;
	for (int i = 0; i < hii->cap; i++) hii->data[i].exists = 0;
	for (int i = 0; i < n; i++) hii_set(hii, data_copy[i].key, data_copy[i].val);
	hii->size = n;
	hii->true_size = n;
}

HashIntInt* hii_new() {
	HashIntInt* res = malloc(sizeof(HashIntInt));
	res->true_size = 0;
	res->size = 0;
	res->cap = 1;
	res->data = malloc(sizeof(IntPair));
	res->data[0].exists = 0;
	return res;
}


