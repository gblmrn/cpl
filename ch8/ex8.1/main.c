/*
 * Exercise 8-1. Rewrite the program cat from Chapter 7 using read, write, open,
 * and close instead of their standard library equivalents. Perform experiments
 * to determine the relative speeds of the two versions.
 */
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void filecopy(int, int);
void error(char *, ...);

/* filecopy: copy file ifd to file ofd */
void filecopy(int ifd, int ofd) {
  char buf[BUFSIZ];
  int n;
  while ((n = read(ifd, buf, BUFSIZ)) > 0) {
    if (write(ofd, buf, n) != n) {
      error("cat: write error");
    }
  }
}

/* error: print an error message and die */
void error(char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  fprintf(stderr, "error: ");
  fprintf(stderr, fmt, args);
  fprintf(stderr, "\n");
  va_end(args);
  exit(1);
}

/* cat: concatenate files, version 1 */
int main(int argc, char *argv[]) {
  int fd;
  void filecopy(int, int);
  if (argc == 1) /* no args; copy standard input */
    filecopy(0, 1);
  else
    while (--argc > 0)
      if ((fd = open(*++argv, O_RDONLY)) == -1) {
        error("cat: can't open %s", *argv);
      } else {
        filecopy(fd, 1);
        close(fd);
      }
  return 0;
}
