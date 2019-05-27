#include "mrubyc_src/mrubyc.h"

#include <stdio.h>
#include <stdlib.h>

#include "src/models/operations.c"
#include "src/loops/main_loop.c"

#define MEMORY_SIZE (1024*40)
static uint8_t my_memory_pool[MEMORY_SIZE];

/*
  Strongly recommended seeing src/value.h to know
  how to pass variables
*/

/* sample function of passing Fixnum */
static void c_FixnumAdd(struct VM *vm, mrbc_value v[], int argc){
  int fixnum = GET_INT_ARG(1) + 1;
  /* C int can be returned as it is */
  SET_INT_RETURN(fixnum);
}

/* sample function of passing String */
static void c_StringShift(struct VM *vm, mrbc_value v[], int argc){
  char *string = GET_STRING_ARG(1);
  if (string[0] < 0x7f) {
    string[0] = string[0] + 1;
  } else {
    string[0] = 0x20;
  }
  /* C char* should be converted into mruby String */
  mrbc_value mrbc_string = mrbc_string_new_cstr(vm, string);
  SET_RETURN(mrbc_string);
}

/* sample function of Array */
static void c_ArrayAsItIs(struct VM *vm, mrbc_value v[], int argc){
  /* convert mruby Array into C array */
  mrbc_value mrbc_array = GET_ARY_ARG(1);
  int length = GET_INT_ARG(2);
  int array[length];
  for( int i = 0; i < length; i++ ) {
    mrbc_value value = mrbc_array_get(&mrbc_array, i);
    array[i] = value.i;
  }
  /* convert vice versa */
  mrbc_value mrbc_new_array = mrbc_array_new(vm, length);
  for( int i = 0; i < length; i++ ) {
    mrbc_value value = mrbc_fixnum_value(array[i]);
    mrbc_array_set( &mrbc_new_array, i, &value );
  }
  SET_RETURN(mrbc_new_array);
}

//================================================================
/*! DEBUG PRINT
*/
static void c_debugprint(struct VM *vm, mrbc_value v[], int argc){
  for( int i = 0; i < 79; i++ ) { console_putchar('='); }
  console_putchar('\n');
  int total, used, free, fragment;
  mrbc_alloc_statistics( &total, &used, &free, &fragment );
  console_printf("Memory total:%d, used:%d, free:%d, fragment:%d\n", total, used, free, fragment );
  unsigned char *key = GET_STRING_ARG(1);
  unsigned char *value = GET_STRING_ARG(2);
  console_printf("%s:%s\n", key, value );
  for( int i = 0; i < 79; i++ ) { console_putchar('='); }
  console_putchar('\n');
}

int main(void) {
  mrbc_init(my_memory_pool, MEMORY_SIZE);

  mrbc_define_method(0, mrbc_class_object, "debugprint", c_debugprint);

  mrbc_define_method(0, mrbc_class_object, "w_FixnumAdd", c_FixnumAdd);
  mrbc_define_method(0, mrbc_class_object, "w_StringShift", c_StringShift);
  mrbc_define_method(0, mrbc_class_object, "w_ArrayAsItIs", c_ArrayAsItIs);

  mrbc_create_task( operations, 0 );
  mrbc_create_task( main_loop, 0 );
  mrbc_run();

  return 0;
}

