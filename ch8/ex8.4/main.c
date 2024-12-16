/*
 * Exercise 8-4. The standard library function
 * int fseek(FILE *fp, long offset, int origin)
 * is identical to lseek except that fp is a file pointer instead of a file
 * descriptor and return value is an int status, not a position. Write fseek.
 * Make sure that your fseek coordinates properly with the buffering done for
 * the other functions of the library.
 */

#include <unistd.h>
#define PERMS 0666
#define EOF (-1)
#define BUFSIZ2 1024
#define OPEN_MAX 20 /* max #files open at once */

typedef struct _iobuf {
  int cnt;    /* characters left */
  char *ptr;  /* next character position */
  char *base; /* location of buffer */
  int flag;   /* mode of file access */
  int fd;     /* file descriptor */
} FILE2;

extern FILE2 _iob[OPEN_MAX];

enum _flags {
  _READ = 01,  /* file open for reading */
  _WRITE = 02, /* file open for writing */
  _UNBUF = 04, /* file is unbuffered */
  _EOF = 010,  /* EOF has occurred on this file */
  _ERR = 020   /* error occurred on this file */
};

FILE2 _iob[OPEN_MAX] = {/* stdin, stdout, stderr */
                        {0, (char *)0, (char *)0, _READ, 0},
                        {0, (char *)0, (char *)0, _WRITE, 1},
                        {0, (char *)0, (char *)0, _WRITE | _UNBUF, 2}};

int fseek(FILE2 *, long, int);

/* fseek2: seek with a file pointer */
int fseek(FILE2 *fp, long offset, int whence) {
  unsigned nc; /* number of characters to flush */
  long rc = 0; /* return code */

  if (fp->flag & _READ) {
    if (whence == 1) {   /* from current position ? */
      offset -= fp->cnt; /* remember chars in buffer */
    }
    lseek(fp->fd, offset, whence);
    fp->cnt = 0; /* no characters buffered */
  } else if (fp->flag & _WRITE) {
    if ((nc = fp->ptr - fp->base) > 0) {
      if (write(fp->fd, fp->base, nc) != nc) {
        rc = -1;
      }
    }
    if (rc != -1) { /* no errors yes ? */
      rc = lseek(fp->fd, offset, whence);
    }
  }
  return (rc == -1) ? -1 : 0;
}

int main() {}
