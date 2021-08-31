/*

Write a function setbits(x,p,n,y) that returns x with the n bits that
begin at position p set to the rightmost n bits of y, leaving other
bits unchanged

*/

#include <stdio.h>

int setbits(unsigned, int, int, unsigned);
void decToBin(unsigned);

int setbits(unsigned x, int p, int n, unsigned y)
{
  int posP = p + 1 - n;
  return (x & ~(~(~0 << n) << posP)) | ((~(~0 << n) & y) << posP);
}

int main(int argc, char* argv[])
{
  printf("0x%X\n", setbits(0x0FFF, 7, 4, 0xA));

  return 0;
}
