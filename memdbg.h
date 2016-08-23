/*
 * dbgmem.h
 * Copyright (C) 2016-2017  cloudguard.org: 
 *
 * created time: Mon 22 Aug 2016 03:25:05 PM EDT
 *
 */

#ifndef _MEMDBG_H

void *dbg_malloc(size_t size, const char *file, size_t line);
void dbg_free(void *p);
void print_meminfo(void);

#endif /* _MEMDBG_H */
