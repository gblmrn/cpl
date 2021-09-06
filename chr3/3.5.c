/*

Write a function itob(n,s,b) that convers the integer n into a
base b character representation in the string s. In particular,
itob(n,s,16) ofrmats n as a hexadecimal integer in s.

 */

#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

void swap(char*, char*);
void reverse(char*);
void itob(int,char*,int);

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
  while(start <= end) {
    swap(&s[start], &s[end]);
    start++;
    end--;
  }
}

void itob(int n, char s[], int b)
{
  int i, j, sign;

  if((sign = n) < 0)
    n = -n;
  else
    n = n;
  i = 0;
  do {
    j = n % b;
    s[i++] = (j < 9) ? (j + '0') : ((j - 10) + 'A');
  } while(n /= b);
  if(sign < 0)
    s[i++] = '-';
  s[i] = '\0';
  reverse(s);
}

int main(int argc, char** argv)
{
  char buffer[MAXLINE];

  itob(255, buffer, 16);
  printf("%s\n", buffer);

  return 0;
}
