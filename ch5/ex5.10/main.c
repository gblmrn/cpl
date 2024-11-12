/*

Write a program expr, which evaluates a reverse Polish expression
from command line, where each operator or operand is a separate 
argument. For example,
expr 2 3 4 + * evaluates 2 * (3 + 4)

 */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#define MAXVALUE 100

int main(int argc, char **argv)
{
  double buf[MAXVALUE];
  double *pbuf = buf;

  while (--argc) {
    if (isdigit(**++argv))
      *pbuf++ = atof(*argv);
    else if (**argv == '-') { // without ++ (doesn't need
      pbuf -= 2; // to iterate to the next value)
      *pbuf = *pbuf - *(pbuf + 1);
      ++pbuf; // iterate to next free space in the buffer.
    }
    else if (**argv == '/') {
      pbuf -= 2;
      *pbuf = *pbuf / *(pbuf - 1);
      ++pbuf;
    }
    else if (**argv == '*') {
      pbuf -= 2;
      *pbuf = *pbuf * *(pbuf - 1);
      ++pbuf;
    }
    else if (**argv == '+') {
      pbuf -= 2;
      *pbuf = * pbuf + *(pbuf + 1);
      ++pbuf;
    }
    else
      argc = 1;
  }
  printf("%.3f\n", *--pbuf); // -- last space where value is stored 
  return 0;
}
