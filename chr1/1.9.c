/* Copy input to output, replace one or more blank with a single*/
#include <stdio.h>

int main(void) {
char c, last_c;
  
  while((c = getchar()) != EOF) {
    if(c != ' ' || last_c != ' ') {
      putchar(c);
    }

    last_c = c;
  }

  return 0;
}
