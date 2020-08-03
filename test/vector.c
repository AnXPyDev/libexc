#include <stdio.h>
#include "libec.h"

int main() {
  _ec_vector_t vec = _ec_vector_create(sizeof(int), 5);
  for (int i = 0; i < 20; i++) {
    _ec_vector_push(&vec, &i);
  }
  _ec_vector_set_val(&vec, 5, int, 192);
  _ec_vector_insert_val(&vec, 1, int, 69);
  _ec_vector_reserve(&vec, vec.reserved + 100);
  _ec_vector_insert_val(&vec, 5, int, 321);
  _ec_vector_remove(&vec, 15);
  for (_ec_vector_size_t i = 0; i < vec.occupied; ++i) {
    printf("%u : %i\n", i, *(int*)_ec_vector_get(&vec, i));
  }
  
}
