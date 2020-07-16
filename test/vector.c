#include <stdio.h>
#include "libec.h"

int main() {
  _ec_vector_t vec = _ec_vector_create(sizeof(int), 5);
  for (int i = 0; i < 20; i++) {
    _ec_vector_push(&vec, &i);
  }
  int n = 192;
  _ec_vector_replace_val(&vec, 5, int, 192);
  for (_ec_vector_size_t i = 0; i < vec.occupied; ++i) {
    printf("%u : %i\n", i, *(int*)_ec_vector_get(&vec, i));
  }
}
