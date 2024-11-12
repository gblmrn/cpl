/*

Write a pointer version of the function strcat that we showed in 
Chapter 2: strcat(s,t) copies the string t to the end of s;

 */

#include <stdio.h>

void strCat(char*, char*);

int main(int argc, char** argv)
{
  char s[] = "abc";
  char t[] = "def";
  strCat(s, t);
  printf("%s ", s);

  return 0;
}

void strCat(char* s, char* t) // copies t to the end of s
{
  for ( ; *s != '\0'; ++s)
    ;
  for ( ; *t != '\0'; ++t, ++s)
    *s = *t;
  *s = '\0';
}
