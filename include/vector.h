typedef unsigned int _ec_vector_size_t;

typedef struct _ec_vector {
  _ec_vector_size_t element_size;
  _ec_vector_size_t occupied, reserved;
  char *data;
} _ec_vector_t;

_ec_vector_t _ec_vector_create(_ec_vector_size_t element_size, _ec_vector_size_t reserve);
void _ec_vector_destroy(_ec_vector_t *vector);
void _ec_vector_reserve(_ec_vector_t *vector, _ec_vector_size_t new_capacity);
void _ec_vector_push(_ec_vector_t *vector, void *new_element);
void _ec_vector_pop(_ec_vector_t *vector);
void *_ec_vector_get(_ec_vector_t *vector, _ec_vector_size_t index);
void _ec_vector_replace(_ec_vector_t *vector, _ec_vector_size_t index, void *new_element);
//void _ec_vector_insert(_ec_vector_t *vector, _ec_vector_size_t index, void *new_element);

#define _ec_vector_push_val(vector, T, val) {T __new_elt = val; _ec_vector_push(vector, &__new_elt);}
#define _ec_vector_replace_val(vector, index, T, val) {T __new_elt = val; _ec_vector_replace(vector, index, &__new_elt);}
