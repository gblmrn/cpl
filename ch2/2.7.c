/*

Write a function invert(x,p,n) that returns x with the n bits that begin
at position p inverted, leaving other bits unchanged.

*/

#include <stdio.h>

int inverted(unsigned, int, int);

int inverted(unsigned x, int p, int n)
{
  return x ^ ~(~0 << n) << p;
}

int main(int argc, char *argv[])
{

  printf("0x%X", inverted(0xFFFF, 0, 0));

  return 0;
}
