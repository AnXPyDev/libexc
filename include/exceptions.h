#include <setjmp.h>

struct _ec_exception;

typedef void *(*_ec_exception_handler_t)(struct _ec_exception*);

typedef struct _ec_exception {
  void *payload;
  int type;
  char *message;
  _ec_exception_handler_t handler;
} _ec_exception_t;

typedef struct _ec_catch_frame {
  jmp_buf *buffer;
  _ec_exception_t *caught;
  struct _ec_catch_frame *previous;
} _ec_catch_frame_t;

typedef struct _ec_catch_stack {
  _ec_catch_frame_t *current;
} _ec_catch_stack_t;

void _ec_push_catch_frame(_ec_catch_stack_t*, jmp_buf*);
_ec_exception_t *_ec_pop_catch_frame(_ec_catch_stack_t*);
void _ec_throw(_ec_catch_stack_t*, _ec_exception_t*);
_ec_exception_t *_ec_catch(_ec_catch_stack_t*, jmp_buf*, int);
_ec_exception_t *_ec_make_exception(int, char*, void*, _ec_exception_handler_t);
void *_ec_handle_exception(_ec_exception_t*);
