//
//  ck.c
//
//  Created by Karim DRIDI on 19/01/2017.
//  Copyright © 2017 Karim DRIDI. All rights reserved.
//

#include <ck/ck.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdarg.h>

void *ck_malloc(size_t size)
{
    void *ptr;

    ptr = malloc(size);
    if (ptr == NULL)
    {
        // TODO Logging
    }

    return ptr;
}

void ck_free(void *ptr)
{
    if (ptr == NULL)
    {
        // TODO Logging
    }
    free(ptr);
}

int ck_printf(const char * restrict format, ...)
{
    int res;
    va_list ap;

    va_start(ap, format);
    res = ck_vprintf(format, ap);
    va_end(ap);

    return res;
}

ssize_t ck_read(int fildes, void *buf, size_t nbyte)
{
    ssize_t res;

    res = read(fildes, buf, nbyte);
    if (res < 0)
    {
        // TODO Logging
    }
    if (res == 0)
    {
        // TODO Logging
    }

    return res;
}

void *ck_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
    // TODO Implementation is missing.
    return memcpy(dst, src, n);
}

void *ck_memmove(void *dst, const void *src, size_t len)
{
    // TODO Implementation is missing.
    return memmove(dst, src, len);
}

size_t ck_strlen(const char *s)
{
    // TODO Implementation is missing.
    return strlen(s);
}

char *ck_strdup(const char *s1)
{
    // TODO Implementation is missing.
    return strdup(s1);
}

int ck_vprintf(const char * restrict format, va_list ap)
{
    // TODO Implementation is missing.
    return vprintf(format, ap);
}
