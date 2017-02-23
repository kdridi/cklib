//
//  ck_capture.h
//
//  Created by Karim DRIDI on 19/01/2017.
//  Copyright © 2017 Karim DRIDI. All rights reserved.
//

#ifndef ck_capture_h
#define ck_capture_h

#include <sys/types.h>
#include <stdio.h>

typedef struct s_capture t_capture;

#ifdef __cplusplus
extern "C" {
#endif

t_capture *ck_capture_create(FILE* file, void (*func)(void*), void* data);
void ck_capture_delete(t_capture *self);

void *ck_capture_get_data(t_capture *self);
size_t ck_capture_get_size(t_capture *self);

void ck_capture_streams(t_capture **capout, t_capture **caperr, void (*func)(void*), void* data);

#ifdef __cplusplus
}
#endif

#endif /* ck_capture_h */
