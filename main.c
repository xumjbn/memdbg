/*
 * main.c
 * Copyright (C) 2016-2017  cloudguard.org: 
 *
 * created time: Mon 22 Aug 2016 03:58:22 PM EDT
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "memdbg.h"

#define MALLOC(size)		dbg_malloc(size, __FILE__, __LINE__)
#define FREE(ptr)		dbg_free(ptr)

#define malloc	MALLOC
#define free	FREE

int main(void) 
{
	int *a;
	
	for (int i = 0; i < 1; i++) {
		a = malloc(sizeof(int));
		if (a) {
			free(a);
		}
	}
	int *b = malloc(123);
	free(b);

	malloc(12345);

	print_meminfo();

	return 0;
}
 
