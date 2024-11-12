/*
 * Exercise 5-11. Modify the program entab and detab (written as exercises in
 * Chapter 1) to accept a list of tab stops as arguments. Use the default tab
 * settings if there are no arguments.
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
void detab(char in[], char out[], int argc, char *argv[]) {
  int i, j, k = 1;
  unsigned int snr;

  for (i = j = 0; in[i] != '\0'; ++i) {
    if (in[i] == '\t') {
      if (argc > 1 && k < argc) {
        snr = atoi(argv[k]) - j % atoi(argv[k]);
        k++;
      } else {
        snr = TABLEN - j % TABLEN;
      }
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

// replace strings of blanks by the min number of tabs and blanks
void entab(char in[], char out[], int argc, char *argv[]) {
  int i, j, k = 1;
  int nblanks, ntabs;

  for (i = j = 0; in[i] != '\0'; ++i) {
    if (in[i] == ' ') {
      for (nblanks = ntabs = 0; in[i] == ' '; ++i) {
        if (argc > 1 && k < argc) {
          if ((nblanks + 1) % atoi(argv[k]) == 0) {
            ++ntabs;
            nblanks = 0;
            ++k;
          }
        } else if ((nblanks + 1) % TABLEN == 0) {
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
    entab(in, out, argc, argv);
    printf("%s", out);
    detab(in, out, argc, argv);
    printf("%s", out);
  }

  return 0;
}
