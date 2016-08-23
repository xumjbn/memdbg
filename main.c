/*
 * main.c
 * Copyright (C) 2016-2017  cloudguard.org: 
 *
 * created time: Mon 22 Aug 2016 03:58:22 PM EDT
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "dbgmem.h"

#define MALLOC(size)		dbg_malloc(size, __FILE__, __LINE__)
#define FREE(ptr)			dbg_free(ptr)

int main(void) 
{
	int *a;
	
	for (int i = 0; i < 1; i++) {
		a = MALLOC(sizeof(int));
		if (a) {
			FREE(a);
		}
	}
	int *b = MALLOC(123);
	FREE(b);

	MALLOC(12345);

	print_meminfo();

	return 0;
}
 
