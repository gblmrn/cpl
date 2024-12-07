/*
 * Exercise 7-4. Write a private version of scanf analogous to minprintf from
 * the previous section.
 */

#include <stdarg.h>
#include <stdio.h>

#define LOCALFMT 100

/* minscanf: minimal scanf with variable argument list */
void minscanf(char *fmt, ...) {
  va_list ap; /* points to each unnamed arg in turn */
  char *p, *sval;
  char localfmt[LOCALFMT];
  int i, ival;
  unsigned uval;
  double dval;

  va_start(ap, fmt); /* make ap point to 1st unnamed arg */
  for (p = fmt; *p; p++) {
    if (*p != '%') {
      putchar(*p);
      continue;
    }
    i = 0;
    localfmt[i++] = '%';
    while (*(p + 1))
      localfmt[i++] = *++p;
    localfmt[i++] = *(p + 1);
    localfmt[i++] = '\0';
    switch (*++p) {
    case 'd':
    case 'i':
      ival = va_arg(ap, int);
      scanf(localfmt, ival);
      break;
    case 'x':
    case 'X':
    case 'u':
    case 'o':
      uval = va_arg(ap, unsigned);
      scanf(localfmt, uval);
      break;
    case 'f':
      dval = va_arg(ap, double);
      scanf(localfmt, dval);
      break;
    case 's':
      sval = va_arg(ap, char *);
      scanf(localfmt, sval);
      break;
    default:
      scanf("%s", localfmt);
      break;
    }
  }
  va_end(ap); /* clean up when done */
}

int main() {}
