#include <setjmp.h>
#include <stdio.h>
#include <malloc.h>
#include "exceptions.h"

// Adds a new frame to the catch stack
void _ec_push_catch_frame(_ec_catch_stack_t *stk, jmp_buf *buffer) {
  // A catch frame must be allocated on the heap
  _ec_catch_frame_t *frame = malloc(sizeof(_ec_catch_frame_t));
  frame->previous = stk->current;
  frame->buffer = buffer;
  stk->current = frame;
}

// Removes a frame from the top of the catch stack
// and returns a ptr to a caught exception or NULL
// if nothing was caught
_ec_exception_t *_ec_pop_catch_frame(_ec_catch_stack_t *stk) {
  // Returns null if a catch frame doesn't exist
  if (stk->current == NULL) {
    return NULL;
  }
  _ec_catch_frame_t *current = stk->current;
  _ec_exception_t *caught = current->caught;
  stk->current = stk->current->previous;
  free(current);
  return caught;
}

// Uses longjmp to return to last catch frame
void _ec_throw(_ec_catch_stack_t *stk, _ec_exception_t *exception) {
  if (stk->current == NULL) {
    return;
  }
  stk->current->caught = exception;
  longjmp(*(stk->current->buffer), 1);
}

// Returns caught exception if returning from a longjmp
// or initializes a new catch frame
_ec_exception_t *_ec_catch(_ec_catch_stack_t *stk, jmp_buf *buffer, int jmp_ret) {
  if (jmp_ret == 0) {
    _ec_push_catch_frame(stk, buffer);
    return NULL;
  }
  return _ec_pop_catch_frame(stk);
}

// Allocates an exception on the heap
_ec_exception_t *_ec_make_exception(int type, char* message, void* payload, _ec_exception_handler_t handler) {
  _ec_exception_t *e = (_ec_exception_t*)malloc(sizeof(_ec_exception_t));
  e->type = type;
  e->message = message;
  e->payload = payload;
  e->handler = handler;
  return e;
}

// Calls exception's handler if it has one
// or prints a message
void *_ec_handle_exception(_ec_exception_t *exception) {
  if (exception->handler != NULL) {
    return exception->handler(exception);
  }
  printf("Caught exception of type %i\n", exception->type);
  return NULL;
}
