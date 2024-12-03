/*
 * Exercise 7-1. Write a program that converts upper case to lower or lower
 * case to upper, depending on the name it is invoked with, as found in
 * argv[0].
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>

/* lower: convert input to lower case */
/* upper: convert input to upper case */
int main(int argc, char *argv[]) {
  int c;

  if (strcmp(argv[0], "lower") == 0)
    while ((c = getchar()) != EOF)
      putchar(tolower(c));
  else
    while ((c = getchar()) != EOF)
      putchar(toupper(c));
}
