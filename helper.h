#ifndef HELPER_H
#define HELPER_H
#include <stdio.h>
#include <assert.h>
inline void my_assert(const int &con, const char * msg) {
  printf("%s\n", msg);
  assert(con);
}
#endif
