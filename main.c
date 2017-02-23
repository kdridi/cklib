#include <ck/ck.h>

#include <unistd.h>
#include <stdio.h>

void my_putchar(char c);

void my_putchar(char c)
{
  write(STDOUT_FILENO, &c, 1);
}

void func(void* data)
{
  printf("%s", data);
  my_putchar('\n');
}

// void ck_capture_streams(t_capture **capout, t_capture **caperr, void (*func)(void*), void* data);

int main()
{
  t_capture *capout;
  t_capture *caperr;

  ck_capture_streams(&capout, &caperr, &func, "Hello, World!");

  printf("capout.data = \"%s\"\n", ck_capture_get_data(capout));
  printf("capout.size = %zu\n", ck_capture_get_size(capout));

  printf("caperr.data = \"%s\"\n", ck_capture_get_data(caperr));
  printf("caperr.size = %zu\n", ck_capture_get_size(caperr));

  ck_capture_delete(caperr);
  ck_capture_delete(capout);

  return 0;
}
