/*

Write a program to print a histogram of the frequencies of different
characters in its input.

*/
#include <stdio.h>

#define A 'A'
#define z 'z'

int main(int argc, char *argv[])
{
  char c, i, j, letters[z - A];

  for (i = A; i < z + 1; ++i)
    letters[i - A] = 0;

  // count letter frequency
  while ((c = getchar()) != EOF) {
    if (c >= A && c <= z)
      ++letters[c - A];
  }

  // print histogram
  for (i = A; i < z + 1; ++i) {
    if (letters[i - A] != 0) {
      printf("\n%c (%02d): ", i, letters[i - A]);
      for (j = 0; j < letters[i - A]; ++j)
        putchar('*');
    }
  }
  putchar('\n');
    
  return 0;
}
