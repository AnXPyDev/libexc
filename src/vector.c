#include <malloc.h>
#include <string.h>
#include "vector.h"

_ec_vector_t _ec_vector_create(_ec_vector_size_t element_size, _ec_vector_size_t reserve) {
  char *data = malloc(element_size * reserve);
  _ec_vector_t result = {
    element_size, 0, reserve, data
  };
  return result;
}

void _ec_vector_destroy(_ec_vector_t *vector) {
  free(vector->data);
}

void _ec_vector_reserve(_ec_vector_t *vector, _ec_vector_size_t new_capacity) {
  vector->data = realloc(vector->data, vector->element_size * new_capacity);
  vector->reserved = new_capacity;
  if (vector->occupied > vector->reserved) {
    vector->occupied = vector->reserved;
  }
}

void _ec_vector_push(_ec_vector_t *vector, void *new_element) {
  if (vector->occupied == vector->reserved) {
    _ec_vector_reserve(vector, vector->occupied + 1);
  }
  memcpy(vector->data + vector->occupied * vector->element_size, new_element, vector->element_size);
  vector->occupied++;
}

void _ec_vector_pop(_ec_vector_t *vector) {
  if (vector->occupied > 0) {
    vector->occupied--;
  }
}

void *_ec_vector_get(_ec_vector_t *vector, _ec_vector_size_t index) {
  if (index + 1 > vector->occupied) {
    return NULL;
  }
  return vector->data + index * vector->element_size;
}

void _ec_vector_replace(_ec_vector_t *vector, _ec_vector_size_t index, void *new_element) {
  if (index + 1 > vector->occupied) {
    return;
  }
  memcpy(vector->data + index * vector->element_size, new_element, vector->element_size);
}

