/*
 * dgbmem.c
 * Copyright (C) 2016-2017  cloudguard.org: 
 *
 * created time: Mon 22 Aug 2016 03:25:12 PM EDT
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


struct mem_prefix {
	size_t size;
	const char *file;
	const char *reason;
	size_t line;
};

struct memlist {
	struct mem_prefix mp;
	struct memlist *prev;
	struct memlist *next;
};


static struct memlist *memlist_head = NULL;

#define cut_mem_prefix(p)		((struct mem_prefix *)(p) + 1)
#define add_mem_prefix(p)		((struct mem_prefix *)(p) - 1)


static int add_to_memlist(struct mem_prefix *p)
{
	struct memlist *h = memlist_head;
	struct memlist *prev = memlist_head;

	for (; h; h = h->next) {
		if (strcmp(h->mp.file, p->file) == 0 && h->mp.line == p->line) {
			h->mp.size += p->size;
			return 0;
		}
		prev = h;
	}

	struct memlist *n = malloc(sizeof(struct memlist));
	assert(n != NULL);
	memset(n, 0, sizeof(*n));

	memcpy(&n->mp, p, sizeof(struct mem_prefix));
	if (prev == memlist_head) {
		if (prev) {
			prev->next = n;
			n->prev = memlist_head;
		} else {
			memlist_head = n;
		}
	} else {
		prev->next = n;
		n->prev = prev;
	}

	return 0;
}

static int del_from_memlist(struct mem_prefix *p)
{
	struct memlist *h = memlist_head;

	for (; h; h = h->next) {
		if (strcmp(h->mp.file, p->file) == 0 && h->mp.line == p->line) {
			h->mp.size -= p->size;
			break;
		}
	}
	return 0;
}

void *dbg_malloc(size_t size, const char *file, size_t line)
{
	struct mem_prefix *p = malloc(sizeof(struct mem_prefix) + size);
	if (p != NULL) {
		p->size = size;
		p->file = file;
		p->line = line;
		p->reason = "malloc";
		add_to_memlist(p);
		return p + 1;
	} else {
		return NULL;
	}
}

void dbg_free(void *p)
{
	del_from_memlist(add_mem_prefix(p));
	free(add_mem_prefix(p));
}

void print_meminfo(void) 
{
	struct memlist *h = memlist_head;

	printf("FILENAME            LINE        SIZE        REASON\n"); 
	printf("-----------------------------------------------------\n");
	for (; h; h = h->next) {
		printf("%-20s%-12u%-12u%-10s\n", 
				h->mp.file, (unsigned int)h->mp.line, (unsigned int)h->mp.size, h->mp.reason); 
	}
	printf("-----------------------------------------------------\n");
}
