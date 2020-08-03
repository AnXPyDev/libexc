typedef unsigned int _ec_shared_ptr_counter_t;

struct _ec_unique_ptr {
  void *ptr;
};

struct _ec_shared_ptr {
  _ec_shared_ptr_counter_t *count;
  void *ptr;
};

struct _ec_weak_ptr {
  void *ptr;
}

enum _ec_ptr_type {
  _ec_ptr_type_unique, _ec_ptr_type_shared, _ec_ptr_type_weak
};

union _ec_ptr_container {
  struct _ec_shared_ptr shared;
  struct _ec_unique_ptr unique;
  struct _ec_weak_ptr weak;
};

typedef struct _ec_ptr {
  enum _ec_ptr_type type;
  union _ec_ptr_container container;
} _ec_ptr_t;

