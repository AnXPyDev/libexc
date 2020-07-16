#include <stdio.h>
#include <setjmp.h>
#include <malloc.h>
#include "libec.h"

// Initialize a catch stack in the global scope
_ec_catch_stack_t CStack;

// Exception 12 handler
void *handle_exception_12(_ec_exception_t *e) {
  printf("Exception 12 caught\npayload: %i\nmessage: %s\n", *(int*)e->payload, e->message);
  free(e->payload);
  free(e->message);
  return NULL;
}

void test_recursive(int n, int depth) {
  printf("test_recursive: %i %i\n", n, depth);
  if (n >= depth) {
    char *message = malloc(255);
    sprintf(message, "test_recursive: Throwing after %i recursive calls", n);
    int *payload = malloc(sizeof(int)); *payload = n;
    _ec_exception_t *e = _ec_make_exception(1, message, (void*)payload, handle_exception_12);
    _ec_throw(&CStack, e);
  }
  test_recursive(n + 1, depth);
}

void test_rethrow() {
  jmp_buf buffer;
  int jmp_ret = setjmp(buffer);
  _ec_exception_t *caught = _ec_catch(&CStack, &buffer, jmp_ret);
  if (caught != NULL) {
    printf("test_rethrow: Rethrowing exception\n");
    _ec_throw(&CStack, caught);
  } else {
    test_recursive(1, 20);
  }
}

int main() {
  jmp_buf buffer;
  int jmp_ret = setjmp(buffer);
  _ec_exception_t *caught = _ec_catch(&CStack, &buffer, jmp_ret);
  if (caught != NULL) {
    _ec_handle_exception(caught);
    free(caught);
  } else {
    test_rethrow();
  }
  return 0;
}
