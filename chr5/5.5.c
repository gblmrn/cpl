/*

Write versions of the library functions strncpy, strncat, and strncmp,
which operate on at most the first n characters of their argument strings.
For example, strncpy(s,t,n) copies at most n characters of t to s.
Pseudocode:
strncpy(s,t,n)
for i = 0 to n
  *(s+i) = *(t+i) ? *(t+i) : '\0' 

*/

#include <stdio.h>

#define MAX 10

int strLen(char*);
char* strNcpy(char*, const char*, int);
char* strNcat(char*, const char*, int);
int strNcmp(const char*, const char*, int);

int main(int argc, char** argv)
{
  char s[MAX] = "";
  char* t = "xyz";
  printf("strNcpy = %s\n", strNcpy(s, t, 3));
  printf("strNcat = %s\n", strNcat(s, t, 2));
  printf("strNcmp = %d\n", strNcmp(s, t, 2));

  return 0;
}

// find string length
int strLen(char* s)
{
  int count = 0;
  while (*s++)
    count++;
  return count;
}

// copy first n chars from t to s.
char* strNcpy(char* s, const char* t, int n) 
{
  int i;
  for (i = 0; i < n; ++i)
    *(s+i) = *(t+i) ? *(t+i) : '\0';
  return s;
}

// concatenate first n chars from t to the end of s.
char* strNcat(char* s, const char* t, int n)
{
  int i;
  int len = strLen(s);
  for (i = 0; i < n && *(t + i); ++i)
    *(s + i + len) = *(t + i);
  *(s + len + i) = '\0';
  return s;
}

// compare first n characters from string t with string s
int strNcmp(const char* s, const char* t, int n)
{
  int i;
  for (i = 0; i < n && *(s + i) == *(t + i) && *(s + i); ++i)
    ;
  return (unsigned char)*(s + i) - (unsigned char)*(t + i);
}
