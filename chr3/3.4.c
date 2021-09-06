/*

In a two's complement number representation, our version of
itoa does not handle the largest negative number, that is,
the value of n equal to -(2^(wordsize-1). Explain why not.
Modify it to print that value correctly, regardless of the
machine on which it runs.

 */

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

#define MAXLINE 20

void swap(char*, char*);
void reverse(char*);
void itoa(int, char*);

void swap(char* x, char* y)
{
  char temp;

  temp = *x;
  *x = *y;
  *y = temp;
}

void reverse(char s[])
{
  int start, end;
  start = 0;
  end = strlen(s) - 1;

  while(start <= end){
    swap(&s[start], &s[end]);
    start++;
    end--;
  }
}

// Takes a number and convers it to string
void itoa(int n, char s[])
{
  int i, sign;
  sign = n;

  i = 0;
  do {
    s[i++] = abs(n % 10) + '0';
  } while (n /= 10);
  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';
  reverse(s);
}

int main(int argc, char** argv)
{
  char buffer[MAXLINE];

  itoa(INT_MIN, buffer);
  printf("%s\n", buffer);

  return 0;
}
