//
//  ck_array_list.h
//
//  Created by Karim DRIDI on 19/01/2017.
//  Copyright © 2017 Karim DRIDI. All rights reserved.
//

#ifndef ck_array_list_h
#define ck_array_list_h

#include <sys/types.h>

typedef struct s_array_list t_array_list;

#ifdef __cplusplus
extern "C" {
#endif

t_array_list *ck_array_list_create    (size_t capacity, size_t block_size);
void          ck_array_list_delete    (t_array_list *self);

t_array_list *ck_array_list_push_back       (t_array_list *self, void *data);
t_array_list *ck_array_list_push_back_values(t_array_list *self, void *data, size_t n);
void         *ck_array_list_clone_data      (t_array_list *self, size_t *len);

#ifdef __cplusplus
}
#endif

#endif /* ck_array_list_h */
