/* Exercise 5-13. Write the program tail, which prints the last n lines of its
 * input. By default, n is set to 10, let us say, but it can be changed by an
 * optional argument so that tail -n prints the last n lines. The program should
 * behave rationally no matter how unreasonable the input or the value of n.
 * Write the program so it makes the best use of available storage; lines should
 * be stored as in the sorting program of Section 5.6, not in a two-dimensional
 * array of fixed size.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1000      /* max line len */
#define MAXLINES 5000    /* max lines */
#define ALLOCSIZE 100000 // size of available space

int getLine(char line[], int maxlen);
char *alloc(int n);
int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);

static char allocbuf[ALLOCSIZE]; // storage for alloc
static char *allocp = allocbuf;  // next free poisition
char *lineptr[MAXLINES];         // pointers to text lines
char lines[MAXLINES][MAXLEN];    // array for readlines2

// getline: get a new line from input and return it's length
int getLine(char line[], int maxlen) {
  int i, c;

  for (i = 0; i < maxlen && (c = getchar()) != '\n' && c != EOF; ++i)
    line[i] = c;
  if (c == '\n')
    line[i++] = c;
  line[i] = '\0';

  return i;
}

// *alloc: return pointer to n characters
char *alloc(int n) {
  if (allocbuf + ALLOCSIZE - allocp >= n) { // if it fits
    allocp += n;
    return allocp - n; // old p
  } else               // not enough room
    return 0;
}

// readlines: read input lines
int readlines(char *lineptr[], int maxlines) {
  int len, nlines;
  char *p, line[MAXLEN];

  nlines = 0;
  while ((len = getLine(line, MAXLEN)) > 0)
    if (nlines >= maxlines || (p = alloc(len)) == NULL) // we can use
      return -1; // malloc from stdlib instead of alloc implementation
    else {
      line[len - 1] = '\0'; // delete new line ('\n')
      strcpy(p, line);
      lineptr[nlines++] = p;
    }
  return nlines;
}

// writelines: write output lines
void writelines(char *lineptr[], int nlines) {
  int i;

  for (i = 0; i < nlines; ++i)
    printf("%s\n", lineptr[i]);
}

int main(int argc, char **argv) {
  int n = 10;
  if (argc > 1) {
    if (strcmp(argv[1], "-n") == 0) {
      n = atoi(argv[2]);
    }
  }

  if (readlines(lineptr, MAXLINES) >= 0) {
    writelines(lineptr, n);
    return 0;
  } else {
    printf("error: input too big to sort\n");
    return 1;
  }
}
