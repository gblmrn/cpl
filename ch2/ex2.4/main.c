/*

Write an alternate version of squeeze(s1,s2) that deletes each character
in s1 that matches any character in the string s2.

*/

#include <stdio.h>

void squeeze(char*, const char*);

void squeeze(char s1[], const char s2[])
{
  int i, j, k;

  for (i = j = 0; s1[i] != '\0'; ++i) {
    for (k = 0; s2[k] != '\0'; ++k)
      if (s1[i] == s2[k])
        break;
    if (s2[k] == '\0')
        s1[j++] = s1[i];
  }
  s1[j] = '\0';
}

int main(int argc ,char *argv[])
{
  char s1[] = "abcdf";
  const char s2[] = "df";
  squeeze(s1, s2);
  printf("%s\n", s1);

  return 0;
}
