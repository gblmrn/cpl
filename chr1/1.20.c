/*
 * Exercise 1-20. Write a program detab that replaces tabs in the input with the
 * proper number of blanks to space to the next tab stop. Assume a fixed set of
 * tab stops, say every n columns. Should n be a variable or a symbolic
 * parameter?
 */

#include <stdio.h>

#define MAXLEN 1000
#define TAB_LENGTH 8

// replace tabs with spaces
void detab(char in[], char out[]) {
  int i, j;
  unsigned int snr;

  for (i = j = 0; in[i] != '\0'; ++i) {
    if (in[i] == '\t') {
      snr = TAB_LENGTH - j % TAB_LENGTH;
      while (snr) {
        out[j++] = ' ';
        --snr;
      }
    } else {
      out[j++] = in[i];
    }
  }
  out[j] = '\0';
}

// read line in 'line' from 'stdin' with 'maxlen' and return line length
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

int main() {
  int c;
  unsigned int nr_of_spaces;
  char in[MAXLEN];
  char out[MAXLEN];

  while ((getLine(in, MAXLEN)) > 0) {
    detab(in, out);
    printf("%s", out);
  }

  return 0;
}
