#include <stdio.h>
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

void _ec_vector_set(_ec_vector_t *vector, _ec_vector_size_t index, void *new_element) {
  if (index + 1 > vector->reserved) {
    _ec_vector_reserve(vector, index + 1);
  }
  if (index + 1 > vector->occupied) {
    vector->occupied = index + 1;
  }
  memcpy(vector->data + index * vector->element_size, new_element, vector->element_size);
}

void _ec_vector_insert(_ec_vector_t *vector, _ec_vector_size_t index, void *new_element) {
  if (index + 1 > vector->occupied) {
    if (index + 1 > vector->reserved) {
      _ec_vector_reserve(vector, index + 1);
    }
    _ec_vector_set(vector, index, new_element);
  } else if (vector->occupied + 1 > vector->reserved) {
    char *new_data = malloc((vector->occupied + 1) * vector->element_size);
    memcpy(new_data, vector->data, vector->element_size * index);
    memcpy(new_data + vector->element_size * index, new_element, vector->element_size);
    memcpy(new_data + vector->element_size * (index + 1), vector->data + index * vector->element_size, (vector->occupied - index) * vector->element_size);
    free(vector->data);
    vector->data = new_data;
    vector->occupied += 1;
    vector->reserved = vector->occupied;
  } else {
    char *storage = malloc(vector->element_size);
    char *storage2 = malloc(vector->element_size);
    char *tomove = vector->data + index * vector->element_size;
    memcpy(storage2, new_element, vector->element_size);
    
    for (int i = 0; i < vector->occupied - index + 1; ++i) {
      memcpy(storage, tomove, vector->element_size);
      memcpy(tomove, storage2, vector->element_size);
      memcpy(storage2, storage, vector->element_size);
      tomove += vector->element_size;
    }
    memcpy(tomove, storage2, vector->element_size);
    vector->occupied += 1;
    free(storage);
    free(storage2);
  }
}

void _ec_vector_remove(_ec_vector_t *vector, _ec_vector_size_t index) {
  if (index + 1 > vector->occupied) {
    return;
  } else {
    if (vector->occupied > index + 1) {
      memcpy(vector->data + index * vector->element_size, vector->data + (index + 1) * vector->element_size, vector->occupied - (index + 1));
    }
    vector->occupied -= 1;
  }
}
