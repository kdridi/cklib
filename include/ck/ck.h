//
//  ck.h
//
//  Created by Karim DRIDI on 19/01/2017.
//  Copyright © 2017 Karim DRIDI. All rights reserved.
//

#ifndef ck_h
#define ck_h

#include <sys/types.h>
#include <stdarg.h>

#include <ck/ck_array_list.h>
#include <ck/ck_capture.h>

#ifdef __cplusplus
extern "C" {
#endif

void *  ck_malloc  (size_t size);
void    ck_free    (void *ptr);
void *  ck_memcpy  (void *restrict dst, const void *restrict src, size_t n);
void *  ck_memmove (void *dst, const void *src, size_t len);
size_t  ck_strlen  (const char *s);
char *  ck_strdup  (const char *s1);
ssize_t ck_read    (int fildes, void *buf, size_t nbyte);
int     ck_printf  (const char * restrict format, ...);
int     ck_vprintf (const char * restrict format, va_list ap);

#ifdef __cplusplus
}
#endif

#endif /* ck_h */
