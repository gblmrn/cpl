/*
 *Exercise 5-12. Extend entab and detab to accept the shorthand
 */
#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 1000
#define TABLEN 8

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

// replace tabs with spaces
void detab(char in[], char out[], int m, int n) {
  int i, j;
  unsigned int snr;

  for (i = j = 0; in[i] != '\0'; ++i) {
    if (in[i] == '\t' && i >= m) {
      snr = n - j % n;
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

// replace spaces with tabs
void entab(char in[], char out[], int m, int n) {
  int i, j, nblanks, ntabs;

  for (i = j = 0; in[i] != '\0'; ++i) {
    if (in[i] == ' ' && i >= m) {
      for (nblanks = ntabs = 0; in[i] == ' '; ++i) {
        if ((nblanks + 1) % n == 0) {
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
  int i;
  int m = 0; /* default starting position for tabstops */
  int n = 8; /* default tabstops length */

  for (i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      m = atoi(argv[i] + 1);
    } else if (argv[i][0] == '+') {
      n = atoi(argv[i] + 1);
    }
  }

  while ((getLine(in, MAXLEN)) > 0) {
    entab(in, out, m, n);
    printf("%s", out);
    detab(in, out, m, n);
    printf("%s", out);
  }

  return 0;
}
