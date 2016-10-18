#include <stdio.h>

void swap(int *px, int *py);
void alt_swap(int *px, int *py);

void swap(int *px, int *py)
{
  int temp;

  temp = *px;
  *px = *py;
  *py = temp;
}

// Ehh why doesn't this work?
void alt_swap(int *px, int *py)
{
  int *temp = px;  /* store original address at px */

  px = py;  /* px points to py */
  py = temp;
  printf("x: %d, y: %d\n", *px, *py);
}

int main()
{
  int x = 5;
  int y = 10;

  alt_swap(&x, &y);
  printf("x: %d, y: %d\n", x, y);
  return 0;
}
