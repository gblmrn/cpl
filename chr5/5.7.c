/*

Rewrite readlines to store lines in an array supplied by main, rather
than calling alloc to maintain storage. How much faster is the program?

 */

#include <stdio.h>
#include <string.h>

#define MAXLINES 5000 // max lines to be stored
#define MAXLEN 1000 // line max length

char *lineptr[MAXLINES]; // pointers to text lines
char lines[MAXLINES][MAXLEN]; // array for readlines2

int readlines(char *lineptr[], int nlines);
int readlines2(char lines[][MAXLEN], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

int main(int argc, char** argv)
{
  int nlines; // numbers of lines

  //if ((nlines = readlines2(lines, MAXLINES)) >0 ) { // v2
  if ((nlines = readlines(lineptr, MAXLINES)) >= 0) { // v1
    qsort(lineptr, 0, nlines - 1);
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("error: input too big to sort\n");
    return 1;
  }
}

int getLine(char*, int);
char *alloc(int);

// readlines: read input lines
int readlines(char* lineptr[], int maxlines)
{
  int len, nlines;
  char *p, line[MAXLEN];

  nlines = 0;
  while ((len = getLine(line, MAXLEN)) > 0)
    if (nlines >= maxlines || (p = alloc(len)) == NULL) // we can use
      return -1; // malloc from stdlib instead of alloc implementation
    else {
      line[len-1] = '\0'; // delete new line ('\n')
      strcpy(p, line);
      lineptr[nlines++] = p;
    }
  return nlines;
}

// readlines2: "-" without alloc function with arr supplied by main
int readlines2(char lines[][MAXLEN], int maxlines)
{
  int len, nlines;
  
  nlines = 0;
  while((len = getLine(lines[nlines], MAXLEN)) > 0)
    if (nlines >= maxlines)
      return -1;
    else
      lines[nlines++][len-1] ='\0'; // delete new line
    return nlines;
}

// writelines: write output lines
void writelines(char *lineptr[], int nlines)
{
  int i;

  for (i = 0; i < nlines; ++i)
    printf("%s\n", lineptr[i]);
}

// getline: get a new line from input and return it's length
int getLine(char line[], int maxlen)
{
  int i, c;

  for (i = 0; i < maxlen && (c = getchar()) != '\n' && c != EOF; ++i)
    line[i] = c;
  if (c == '\n')
    line[i++] = c;
  line[i] = '\0';

  return i;
}

#define ALLOCSIZE 100000 // size of available space

static char allocbuf[ALLOCSIZE]; // storage for alloc
static char *allocp = allocbuf; // next free poisition

// *alloc: return pointer to n characters
char *alloc(int n)
{
  if (allocbuf + ALLOCSIZE - allocp >= n) { // if it fits
      allocp += n;
      return allocp - n; // old p
    } else // not enough room
        return 0;
}

// qsort: sort v[left]...v[right] into increasing order
void qsort(char *v[], int left, int right)
{
  int i, last;
  void swap(char *v[], int i, int j);

  if (left >= right) // do nothing if array contains
    return; // fewer than two elements.
  swap(v, left, (left + right) / 2);
  last = left;
  for (i = left+1; i <= right; ++i)
    if (strcmp(v[i], v[left]) < 0)
      swap(v, ++last, i);
  swap(v, left, last);
  qsort(v, left, last-1);
  qsort(v, last+1, right);
}

// swap: interchange v[i] and v[j]
void swap(char *v[], int i, int j)
{
  char *temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}
