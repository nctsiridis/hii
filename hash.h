#ifndef HASH_H
#define HASH_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
	int key, val, exists;
} IntPair;

typedef struct {
	int true_size, size, cap;
	IntPair* data;
} HashIntInt;

int hash(int x, int range);
int* hii_get(HashIntInt* hii, int key);
void hii_set(HashIntInt *hii, int key, int val);
void hii_erase(HashIntInt *hii, int key);
void hii_expand(HashIntInt *hii);
HashIntInt *hii_new();

#endif
