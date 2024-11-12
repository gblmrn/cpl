/*

Write a program to determine the ranges of char, short, int and long
variables, both signed and unsigned, by printing appropiate values from
standard headers and by direct computation. Harder if you compute them:
determine the ranges of the various floating-point types.

*/

#include <stdio.h>
#include <limits.h>

int main(int argc, char *argv[])
{
  // First print is by using standard headers from limits.h
  // Second print is by using direct computation.

  printf("Signed char[%d to %d]\n", SCHAR_MIN, SCHAR_MAX);
  printf("Signed char[%d to %d]\n", ~((unsigned char)~0 >> 1), ((unsigned char)~0 >>1));
  
  printf("Unsigned char[0 to %u]\n", UCHAR_MAX);
  printf("Unsigned char[0 to %u]\n", ((unsigned char)~0));

  printf("Signed short[%d to %d]\n",SHRT_MIN, SHRT_MAX);
  printf("Signed short[%d to %d]\n",~((unsigned short)~0 >> 1), ((unsigned short)~0 >> 1));

  printf("Unsigned short[0 to %u]\n", USHRT_MAX);
  printf("Unsigned short[0 to %u]\n", (unsigned short)~0);

  printf("Signed int[%d to %d]\n",INT_MIN, INT_MAX);
  printf("Signed int[%d to %d]\n",~(~0U >> 1), (~0U >> 1));

  printf("Unsigned int[0 to %u]\n", UINT_MAX);
  printf("Unsigned int[0 to %u]\n", ~0U);

  printf("Signed long[%ld to %ld]\n", LONG_MIN, LONG_MAX);
  printf("Signed long[%ld to %ld]\n", ~(~0UL >> 1), (~0UL >> 1));

  printf("Unsigned long[0 to %lu]\n", ULONG_MAX);
  printf("Unsigned long[0 to %lu]\n", ~0UL);

  printf("Signed long long[%llu to %llu]\n",LLONG_MIN, LLONG_MAX);
  printf("Signed long long[%llu to %llu]\n", ~(~0ULL >> 1), (~0ULL >> 1));

  printf("Unsigned long long[0 to %llu]\n", ULLONG_MAX);
  printf("Unsigned long long[0 to %llu]\n", ~0ULL);

  return 0;
}
