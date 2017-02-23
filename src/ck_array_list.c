//
//  ck_array_list.c
//
//  Created by Karim DRIDI on 19/01/2017.
//  Copyright © 2017 Karim DRIDI. All rights reserved.
//

#include <ck/ck_array_list.h>
#include <ck/ck.h>

#include <stddef.h>

typedef struct s_array_list
{
    size_t capacity;
    size_t block_size;
    size_t length;
    char data[1];
} t_array_list;

static t_array_list *ck_array_list_realloc(t_array_list *self, size_t capacity);

/// ////////////////////////////////////////////////////////////////////////////
// ck_array_list_create
/// ////////////////////////////////////////////////////////////////////////////
t_array_list *
ck_array_list_create(size_t capacity, size_t block_size)
{
    t_array_list *self;
    size_t size;

    size = sizeof(t_array_list) + capacity * block_size - 1;
    if ((self = (t_array_list*) ck_malloc(size)) == NULL)
        return NULL;

    self->capacity = capacity;
    self->block_size = block_size;
    self->length = 0;

    return self;
}

/// ////////////////////////////////////////////////////////////////////////////
// ck_array_list_delete
/// ////////////////////////////////////////////////////////////////////////////
void
ck_array_list_delete(t_array_list *self)
{
    if (self == NULL)
        return;

    ck_free(self);
}

/// ////////////////////////////////////////////////////////////////////////////
// ck_array_list_push_back
/// ////////////////////////////////////////////////////////////////////////////
t_array_list *
ck_array_list_push_back(t_array_list *self, void *data)
{
    if (self->capacity == self->length)
        self = ck_array_list_realloc(self, self->capacity * 2);

    ck_memcpy(self->data + self->length * self->block_size
      , data, self->block_size);
    self->length += 1;

    return self;
}

/// ////////////////////////////////////////////////////////////////////////////
// ck_array_list_push_back
/// ////////////////////////////////////////////////////////////////////////////
t_array_list *
ck_array_list_push_back_values(t_array_list *self, void *data, size_t n)
{
  size_t index;

  index = 0;
  while (index < n)
  {
    self = ck_array_list_push_back(self, data);
    index += 1;
  }

  return self;
}

/// ////////////////////////////////////////////////////////////////////////////
// ck_array_list_clone_data
/// ////////////////////////////////////////////////////////////////////////////
void *
ck_array_list_clone_data(t_array_list *self, size_t *len_ptr)
{
  char *data;
  size_t len;

  data = NULL;
  if (self != NULL)
  {
    len = self->length * self->block_size;
    data = (char *) ck_malloc(len + 1);
    if (data != NULL)
    {
      ck_memcpy(data, self->data, len);
      data[len] = '\0';
      if (len_ptr != NULL)
      {
        *len_ptr = len;
      }
    }
  }

  return data;
}


/// ////////////////////////////////////////////////////////////////////////////
// ck_array_list_realloc
/// ////////////////////////////////////////////////////////////////////////////
static t_array_list *
ck_array_list_realloc(t_array_list *self, size_t capacity)
{
    t_array_list *next;

    if ((next = ck_array_list_create(capacity, self->block_size)) == NULL)
    {
        ck_array_list_delete(self);
        return NULL;
    }

    next->length = self->length > capacity ? capacity : self->length;
    ck_memcpy(next->data, self->data, next->length * next->block_size);
    ck_array_list_delete(self);

    return next;
}
