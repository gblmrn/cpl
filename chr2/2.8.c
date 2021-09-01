/*

Write a function rightrot(x,n) that returns the value of the integer x
rotated to the right by n bit positions.

*/

#include <stdio.h>

int rightrot(unsigned, int);

int rightrot(unsigned x, int n)
{
  return ((~(~0 << n) & x) << (sizeof(x) - n)) | (x >> n);
}

int main(int argc, char *argv[])
{
  printf("%d", rightrot(9, 2));

  return 0;
}
