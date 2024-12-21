/*
 * Exercise 5-17. Add a field-searching capability, so sorting may bee done on
 * fields within lines, each field sorted according to an independent set of
 * options. (The index for this book was sorted with -df for the index category
 * and -n for the page numbers.)
 */
#include <ctype.h>
#include <stdarg.h>
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
int strcmp4(char *, char *);
void readargs(int, char **);
void error(char *, ...);

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf;  /* next free poisition */
char *lineptr[MAXLINES];         /* pointers to text lines */
static int rev = 1;              /* reverse order flag, default ascending */
static int fold = 0;             /* fold flag */
static int dir = 0;              /* directory flag */
static int num = 0;              /* numeric flag */
int pos1 = 0;                    /* field beginning with pos1 */
int pos2 = 0;                    /* ending just before pos2  */

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

/* strcmp4: compare s1 and s2 */
int strcmp4(char *s1, char *s2) {
  int res;
  while (*s1 != '\0' && *s2 != '\0') {
    if (dir) {
      while (*s1 != '\0' && !isalnum(*s1) && !isalpha(*s1)) {
        ++s1;
      }
      while (*s2 != '\0' && !isalnum(*s2) && !isalpha(*s2)) {
        ++s2;
      }
    }
    res = fold ? tolower(*s1) - tolower(*s2) : *s1 - *s2;
    if (res == 0) {
      ++s1;
      ++s2;
    } else {
      return rev * res;
    }
  }
  return 0;
}

/* readargs: read program arguments */
void readargs(int argc, char *argv[]) {
  int c;
  while (--argc > 0 && (c = (*++argv)[0]) == '-' || c == '+') {
    if (c == '-' && !isdigit(*(argv[0] + 1))) {
      while ((c = *++argv[0])) {
        switch (c) {
        case 'd':
          dir = 1;
          break;
        case 'f':
          fold = 1;
          break;
        case 'n':
          num = 1;
          break;
        case 'r':
          rev = -1;
          break;
        default:
          printf("sort: illegal option %c\n", c);
          error("Usage: sort -dfnr [+pos1] [-pos2]\n");
          break;
        }
      }
    } else if (c == '-') {
      pos2 = atoi(argv[0] + 1);
    } else if ((pos1 = atoi(argv[0] + 1)) < 0) {
      error("Usage: sort -dfnr [+pos1] [-pos2]\n");
    }
  }
  if (argc || pos1 > pos2) {
    error("Usage: sort -dfnr [+pos1] [-pos2]\n");
  }
}

/* error: print an error message and die */
void error(char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  fprintf(stderr, "error: ");
  fprintf(stderr, fmt, args);
  fprintf(stderr, "\n");
  va_end(args);
  exit(1);
}

/* sort input lines */
int main(int argc, char *argv[]) {
  int nlines;
  int i, j, numeric = 0;

  readargs(argc, argv);
  if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    qsort2((void **)lineptr, 0, nlines - 1,
           (int (*)(void *, void *))(num ? numcmp : strcmp4));
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("input too big to sort\n");
    return 1;
  }
}
