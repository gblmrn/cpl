/*
 * Exercise 7-8. Write a program to print a set of files, starting each new one
 * on a new page, with a title and a running page count for each file.
 */
#include <stdio.h>

#define MAXLINE 100 /* maximum size of one line */
#define MAXBOT 3    /* maximum lines at bottom of page */
#define MAXHDR 5    /* maximum lines at head of page */
#define MAXPAGE 66  /* maxium lines on one page */

void fileprint(FILE *, char *);
int heading(char *, int pageno);

/* fileprint: print file fname */
void fileprint(FILE *fp, char *fname) {
  int lineno, pageno = 1;
  char line[MAXLINE];

  lineno = heading(fname, pageno++);
  while (fgets(line, MAXLINE, fp) != NULL) {
    if (lineno == 1) {
      fprintf(stdout, "\f");
      lineno = heading(fname, pageno++);
    }
    fputs(line, stdout);
    if (++lineno > MAXPAGE - MAXBOT) {
      lineno = 1;
    }
  }
  fprintf(stdout, "\f"); /* page eject after the file */
}

/* pageno: put heading and enough blank lines */
int heading(char *fname, int pageno) {
  int ln = 3;

  fprintf(stdout, "\n\n");
  fprintf(stdout, "%s page %d\n", fname, pageno);
  while (ln++ < MAXHDR) {
    fprintf(stdout, "\n");
  }
  return ln;
}

/* print: print files - each new one a new page */
int main(int argc, char *argv[]) {
  FILE *fp;

  if (argc == 1) {
    fileprint(stdout, " "); /* no args; print standard output */
  } else {                  /* print file(s) */
    while (--argc) {
      if ((fp = fopen(*++argv, "r")) == NULL) {
        fprintf(stderr, "print: can't open file %s\n", *argv);
      } else {
        fileprint(fp, *argv);
        fclose(fp);
      }
    }
  }
  return 0;
}
