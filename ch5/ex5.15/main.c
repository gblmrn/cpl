/*
 * Exercise 5-15. Add the option -f to fold upper and lower case together, so
 * that case distinctions are not made during sorting; for example, a and A
 * compare equal.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1000      /* max line len */
#define MAXLINES 5000    /* max #lines to be sorted */
#define ALLOCSIZE 100000 /* size of available space */

int getLine(char line[], int maxlen);
char *alloc(int n);
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void swap(void *v[], int i, int j);
void qsort2(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int numcmp(char *, char *);
int strcmp3(char *, char *);

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf;  /* next free poisition */
char *lineptr[MAXLINES];         /* pointers to text lines */
static int rev = 1;              /* reverse order flag, default ascending */
static int fold = 0;             /* fold flag */

/* getline: get a new line from input and return it's length */
int getLine(char line[], int maxlen) {
  int i, c;

  for (i = 0; i < maxlen && (c = getchar()) != '\n' && c != EOF; ++i)
    line[i] = c;
  if (c == '\n')
    line[i++] = c;
  line[i] = '\0';

  return i;
}

/* *alloc: return pointer to n characters */
char *alloc(int n) {
  if (allocbuf + ALLOCSIZE - allocp >= n) { // if it fits
    allocp += n;
    return allocp - n; // old p
  } else               // not enough room
    return 0;
}

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines) {
  int len, nlines;
  char *p, line[MAXLEN];

  nlines = 0;
  while ((len = getLine(line, MAXLEN)) > 0)
    if (nlines >= maxlines || (p = alloc(len)) == NULL)
      return -1;
    else {
      line[len - 1] = '\0';
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

void swap(void *v[], int i, int j) {
  void *temp;
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

/* qsort2: sort v[left]...v[right] into increasing order */
void qsort2(void *v[], int left, int right, int (*comp)(void *, void *)) {
  int i, last;
  void swap(void *v[], int, int);
  if (left >= right)
    /* do nothing if array contains */
    return;
  /* fewer than two elements */
  swap(v, left, (left + right) / 2);
  last = left;
  for (i = left + 1; i <= right; i++)
    if ((*comp)(v[i], v[left]) < 0)
      swap(v, ++last, i);
  swap(v, left, last);
  qsort2(v, left, last - 1, comp);
  qsort2(v, last + 1, right, comp);
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2) {
  double v1, v2;
  v1 = atof(s1);
  v2 = atof(s2);
  if (v1 < v2)
    return -1 * rev;
  else if (v1 > v2)
    return 1 * rev;
  else
    return 0;
}

/* strcmp3: compare s1 and s2 */
int strcmp3(char *s1, char *s2) {
  return rev * fold ? strcasecmp(s1, s2) : strcmp(s1, s2);
}

/* sort input lines */
int main(int argc, char *argv[]) {
  int nlines;
  int i, numeric = 0;

  if (argc > 1) {
    for (i = 1; i < argc; i++) {
      if (strcmp(argv[i], "-n") == 0) {
        numeric = 1;
      } else if (strcmp(argv[i], "-r") == 0) {
        rev = -1;
      } else if (strcmp(argv[i], "-f") == 0) {
        fold = 1;
      }
    }
  }

  if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    qsort2((void **)lineptr, 0, nlines - 1,
           (int (*)(void *, void *))(numeric ? numcmp : strcmp3));
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("input too big to sort\n");
    return 1;
  }
}
