/* htoi(s) converts a string of hexadecimal digits to integer
  (including optional 0x or 0X) :D. */

#include <stdio.h>
#include <ctype.h>

#define MAXLEN 1000

/* functions */
int htoi(char []);

int htoi(char s[])
{

  // var
  int i, hexDigit, intValue;

  i = 0;

  /* detect optional 0x or 0X */
  if(s[0] == '0' && tolower(s[1]) == 'x' && s[2] == '\0')
    i = 2;

  hexDigit = intValue = 0;
  for ( ; s[i] != '\0'; ++i)
  {
    if (!isdigit(s[i]) && (tolower(s[i]) < 'a' || tolower(s[i]) > 'f'))
      return -1; 
    if (isdigit(s[i]))
      hexDigit = s[i] - '0'; 
    else
      hexDigit = tolower(s[i]) - 'a' + 10; /* conv letter hexa */
    intValue = 16 * intValue + hexDigit; /* conv hex to dec */
  }

  return intValue;

}

int main(void)
{
  int result;
  char s[MAXLEN];

  printf("Enter a hexadecimal string: ");
  scanf("%s", s);

  if ((result = htoi(s)) < 0)
    return -1;

  printf("%i\n", result);

  return 0;
}
