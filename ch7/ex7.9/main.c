/*
 * Exercise 7-9. Functions like isupper can be implemented to save space or to
 * save time. Explore both possibilities.
 */
#include <ctype.h>
#include <stdio.h>

int isupper2(int);

/* isupper2: return 1 if c is upper case letter */
int isupper2(int c) {
  if (c >= 'A' && c <= 'Z')
    return 1;
  else
    return 0;
}

int main() {
  int c;

  while ((c = getc(stdin)) != EOF) {
    if (c != '\n') {
      printf("isupper2(%c) = %d\n", c, isupper2(c));
    }
  }

  return 0;
}
