//
//  ck_capture.c
//
//  Created by Karim DRIDI on 19/01/2017.
//  Copyright © 2017 Karim DRIDI. All rights reserved.
//

#include <ck/ck_capture.h>
#include <ck/ck_array_list.h>
#include <ck/ck.h>

#include <stdio.h>
#include <unistd.h>

struct s_capture
{
  void* data;
  size_t size;
};

static void*
static_ck_capture(FILE* file, size_t* len_ptr, void (*func)(void*), void* data);

/// ////////////////////////////////////////////////////////////////////////////
// ck_capture_create
/// ////////////////////////////////////////////////////////////////////////////
t_capture *
ck_capture_create(FILE* file, void (*func)(void*), void* data)
{
  t_capture *self;

  if ((self = (t_capture*) ck_malloc(sizeof(t_capture))) != NULL)
    self->data = static_ck_capture(file, &(self->size), func, data);

  return self;
}

/// ////////////////////////////////////////////////////////////////////////////
// ck_capture_delete
/// ////////////////////////////////////////////////////////////////////////////
void
ck_capture_delete(t_capture *self)
{
  if (self != NULL)
  {
    ck_free(self->data);
    ck_free(self);
  }
}

/// ////////////////////////////////////////////////////////////////////////////
// ck_capture_get_data
/// ////////////////////////////////////////////////////////////////////////////
void *
ck_capture_get_data(t_capture *self)
{
  return self->data;
}

/// ////////////////////////////////////////////////////////////////////////////
// ck_capture_get_size
/// ////////////////////////////////////////////////////////////////////////////
size_t
ck_capture_get_size(t_capture *self)
{
  return self->size;
}




/// ////////////////////////////////////////////////////////////////////////////
// ck_capture_streams
/// ////////////////////////////////////////////////////////////////////////////
typedef struct s_nested
{
  t_capture *cap;
  void (*func)(void*);
  void* data;
} t_nested;

static void
static_ck_capture_nested(void *data)
{
  t_nested *nested;

  nested = (t_nested*) data;
  nested->cap = ck_capture_create(stderr, nested->func, nested->data);
}

void
ck_capture_streams
(t_capture **capout, t_capture **caperr, void (*func)(void*), void* data)
{
  t_capture *cap;
  t_nested nested;

  nested.cap = NULL;
  nested.func = func;
  nested.data = data;

  cap = ck_capture_create(stdout, &static_ck_capture_nested, &nested);

  if (capout != NULL)
    *capout = cap;

  if (caperr != NULL)
    *caperr = nested.cap;
}

/// ////////////////////////////////////////////////////////////////////////////
// static_ck_capture
/// ////////////////////////////////////////////////////////////////////////////
static void*
static_ck_capture(FILE* file, size_t* len_ptr, void (*func)(void*), void* data)
{
  static int RD = 0;
  static int WR = 1;
  static const ssize_t BS = 1;

  int p[2];
  int prevFD;
  void *result;

  result = NULL;
  if (pipe(p) != -1)
  {
      if ((prevFD = dup(fileno(file))) != -1)
      {

          if ((fflush(file)) == 0)
          {
              if ((dup2(p[WR], fileno(file))) != -1)
              {
                  func(data);

                  if ((fflush(file)) == 0)
                  {
                      if ((dup2(prevFD, fileno(file))) != -1)
                      {
                          close(p[WR]);

                          t_array_list* buffer;

                          if ((buffer = ck_array_list_create(1024, sizeof(char))) != NULL)
                          {
                              char buf[BS];
                              ssize_t bytesRead;

                              do {
                                  bytesRead = read(p[RD], buf, BS);
                                  if (bytesRead > 0)
                                      buffer = ck_array_list_push_back_values(buffer, buf, bytesRead);
                              } while (bytesRead > 0);

                              result = ck_array_list_clone_data(buffer, len_ptr);
                          }
                      }
                  }
              }
          }

          close(prevFD);
      }

      if (result == NULL)
      {
          close(p[WR]);
      }
      close(p[RD]);
  }

  return result;
}
