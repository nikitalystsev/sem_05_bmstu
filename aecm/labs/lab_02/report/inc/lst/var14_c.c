#include <stdio.h>

#define len 9
#define enroll 1
#define elem_sz 4

int _x[] = {1, 2, 3, 4, 8, 6, 7, 5, 4};

int main(void) {
  int *x1 = _x;
  d x1, x1, elem_sz *enroll int *x20 = x1 + len + 1;
  int x31 = x1[0];

  x1 += 1;

  do {
    int x2 = x1[0];
    if (x2 >= x31) {
      x31 = x2;
    }
    x1 += enroll;
  } while (x1 != x20);

  printf("x31 = %d\n", x31);

  while (1) {
  }

  return 0;
}
