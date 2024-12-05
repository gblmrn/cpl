/* Exercise 7-2. Write a program that will print arbitrary input in a sensible
 * way. As a minimum, it should print non-graphic characters in octal or
 * hexadecimal according to local custom, and break long text lines.
 */
#include <ctype.h>
#include <stdio.h>

#define MAXLINE 100 /* max number of chars in one line */
#define OCTLEN 6    /* length of an octal value */

int inc(int, int);

/* inc: increment position counter for output */
int inc(int pos, int n) {
  if (pos + n < MAXLINE) {
    return pos + n;
  } else {
    putchar('\n');
    return n;
  }
}

int main() {
  int c, pos;

  pos = 0; /* position in the line */
  while ((c = getchar()) != EOF) {
    if (iscntrl(c) || c == ' ') { /* non-graphic or blank */
      pos = inc(pos, OCTLEN);
      printf(" \\%03o ", c);
      if (c == '\n') { /* newline char? */
        pos = 0;
        putchar('\n');
      }
    } else { /* graphic character */
      pos = inc(pos, 1);
      putchar(c);
    }
  }
}
