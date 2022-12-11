#ifndef VECTOR_H
#define VECTOR_H
#include <stdio.h>
#include <stdlib.h>
typedef struct
{
	int* array;
	size_t used;
	size_t size;
}Array;

void initArray(Array* a, size_t initsize)
{
	//a->array = malloc(initsize * sizeof(initsize));
}
#endif // !VECTOR_H
