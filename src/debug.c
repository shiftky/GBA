#include "debug.h"

void vba_print(char *s) {
  #if defined(__arm__) || defined(__thumb__)
  asm volatile(
    "mov r2, %0\n"
    "ldr r0, =0xc0ded00d\n"
    "mov r1, #0\n"
    "and r0, r0, r0\n"
    :
    /* No output */ :
    "r" (s) :
    "r0", "r1", "r2"
  );
  #endif
}

void vba_int_print(int n) {
  int i;
  char str[30];

  n = n & 0xFFFF;
  for (i = 0; i < 16; i++, n = n << 1) {
    if ( (n & 0x8000) >> 15 ) {
      str[i] = '1';
    } else {
      str[i] = '0';
    }
  }
  str[i] = '\n';
  str[i+1] = '\0';

  vba_print(str);
}
