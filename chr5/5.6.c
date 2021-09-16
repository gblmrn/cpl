/*

Rewrite appropriate programs from earlier chapters and exercises with 
pointers instead of array indexing. Good possibilities include getline,
atoi, itoa, and their variants, reverse, and strindex and getop.

*/

#include <stdio.h>
#include <ctype.h>

#define MAXLINE 100

int getlinep(char*, int);
int atoip(char*);
char* itoap(int, char*);
char* reversep(char*);
int strindexp(char*, char*); 
int getopp(char* str);

int main(int argc, char** argv)
{
  char s[MAXLINE];
  int n = 1245;
  while(getlinep(s, MAXLINE))
    printf("%s", reversep(s)); // just replace the function here to test it

  return 0;
}

int getlinep(char* s, int len)
{
  int i;
  char c;
  for (i = 0; i < len && ((c = getchar()) != '\n') && c != '\0'; ++i)
    *(s + i) = c;
  if (c == '\n')
    *(s + i++) = c;
  *(s + i) = '\0';
  return i;
}

int strlenp(char*);
void swap(char*, char*);

char* reversep(char* s)
{
  int start = 0;
  int end = strlenp(s) - 1; // skip /n and /0
  while (start <= end)
    swap((s + start++), (s + end--));
  return s;
}

int strlenp(char* s)
{
  int count = 0;
  while(*s++ != '\0')
    count++;
  return count;
}

void swap(char* x, char* y)
{
  char temp;
  temp = *x;
  *x = *y;
  *y = temp;
}

// retuns index where t occurs in s else -1
int strindexp(char* s, char* t)
{
  int i, j, k;
  for (i = 0; *(s + i) != '\0'; ++i) {
    for (j = i, k = 0; *(t + k) != '\0' && *(s + j) == *(t + k) ; ++k, ++j)
      ;
      if (k > 0 && *(t + k) == '\0')
        return i;
  }
  return -1;
}

// string->integer
int atoip (char* s)
{
  int n, sign;
  for ( ; isspace(*s) || *s == '\t'; ++s); // skip white space
  sign = (*s == '-') ? -1 : 1;
  if (*s == '-' || *s == '+')
    s++;
  for (n = 0; isdigit(*s); ++s)
    n = n * 10 + (*s - '0');
  return sign * n;
}

// integer->string
char* itoap(int n, char* s)
{
  char* s2 = s;
  do {
    *s2++ = n % 10 + '0';
  } while ((n /= 10) > 0);
  reversep(s);
  return s;
}
