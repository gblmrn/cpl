/*

Write the function strend(s,t), which returns 1 if the string t
occurs at the end of the string s, and zero otherwise.
Pseudocode:
if(len(t) <= len(s))
  s += len(s) - len(t)
  if(strcmp(s,t) == 0)
    ...
*/

#include <stdio.h>

int strLen(char*);
int strCmp(char*, char*);
int strend(char*, char*);

int main(int argc, char** argv)
{
  char s[] = "abcd";
  char t[] = "cd";
  printf("%d ", strend(s, t)); // should be 1

  return 0;
}

int strLen(char* s) // return string length
{
  int i;
  for(i = 0; s[i] != '\0'; ++i)
    ;
  return i;
}

int strCmp(char* s, char* t) // compare two strings
{
  for( ; *s == *t; ++s, ++t)
    if (*s == '\0')
      return 0;
  return *s - *t;
}

int strend(char* s, char* t)
{
  int s_len, t_len, result;
  s_len = strLen(s);
  t_len = strLen(t);
  result = 0;

  if(t_len <= s_len) {
    s += s_len - t_len;
    if (strCmp(s,t) == 0)
      result = 1;
  }
  return result;
}
