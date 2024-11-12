/*

Write a program entab to replace string of blanks by the minimum number
of tabs and blanks to achive the same spacing.

Pseudocode:
entab(char in[], char out[])

  for (i = 0; i != '\0'; ++i) {
    if (in[i] == ' ')
      for (nblanks = ntabs = 0; in[i] == ' '; ++i)
        if (n

  }

*/

#include <stdio.h>

#define MAXLEN 1000
#define TABLEN 4

int getLine(char line[], int maxlen) {
  int i, c;

  for (i = 0; i < maxlen - 1 && ((c = getchar()) != EOF) && c != '\n'; ++i)
    line[i] = c;
  if (c == '\n') {
    line[i] = c;
    ++i;
  }
  line[i] = '\0';

  return i;
}

// replace strings of blanks by the min number of tabs and blanks
void entab(char in[], char out[]) {
  int i, j, nblanks, ntabs;

  for (i = j = 0; in[i] != '\0'; ++i) {
    if (in[i] == ' ') {
      for (nblanks = ntabs = 0; in[i] == ' '; ++i) {
        if ((nblanks + 1) % TABLEN == 0) {
          ++ntabs;
          nblanks = 0;
        } else
          ++nblanks;
      }
      --i;
      while (ntabs-- > 0)
        out[j++] = '\t';
      while (nblanks-- > 0)
        out[j++] = ' ';
    } else
      out[j++] = in[i];
  }
  out[j] = '\0';
}

int main(int argc, char *argv[]) {
  char in[MAXLEN];
  char out[MAXLEN];

  while ((getLine(in, MAXLEN)) > 0) {
    entab(in, out);
    printf("%s", out);
  }

  return 0;
}
