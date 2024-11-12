/*

In a two's complement number system, x &= (x-1) deletes the rightmost
1-bit in x. Explain why. Use this observation to write a faster version
of bitcount.
Answer: 
If x is odd the (x-1) has the same representation as x but the 
  rightmost bit is changed from 1 to 0. (x & (x-1)) == (x-1)
If x is even then (x-1) has the rightmost bit changed from 0 to 1 and
  the rightmost 1 becomes 0;
So we can use the expression x &= (x-1) to count bits that are 1.

*/

#include <stdio.h>

int bitcount(unsigned);

int bitcount(unsigned x)
{
  int b;
  for(b = 0; x != 0; x &= (x - 1))
      b++;

  return b;
}

int main(int argc, char *argv[])
{
  printf("%d\n", bitcount(5)); // 5 in binary is 0101 --> bitcount(5) == 2

  return 0;
}
