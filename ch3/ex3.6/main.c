/*

Write a version of itoa that accepts three arguments instead of
two. The third argument is a minimum field width; the converted
number must be padded with blanks on the left if necessary to
make it wide enough.
 
 */

#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

void swap(char*, char*);
void reverse(char*);
void itoa(int, char*, int);

void swap(char* x, char* y) {
  char temp;

  temp = *x;
  *x = *y;
  *y = temp;
}

void reverse(char* s) {
  int start, end;
  
  start = 0;
  end = strlen(s) - 1;
  while(start <= end) {
    swap(&s[start], &s[end]);
    start++;
    end--;
  }
}

void itoa(int n, char s[], int w) { // w->min s width.
  int i, sign;

  if((sign = n) < 0)
    n = -n;

  i = 0;
  do {
    s[i++] = n % 10 + '0';
  } while(n /= 10);
  if(sign < 0)
    s[i++] = '-';
  while(i < w)
    s[i++] = ' '; // add blanks to achive min width.
  s[i] = '\0';
  reverse(s);
}

int main(int argc, char** argv)
{
  char buffer[MAXLINE];

  itoa(500, buffer, 5);
  printf("%s\n", buffer);

  return 0;
}
