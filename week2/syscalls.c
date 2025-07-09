#include <sys/types.h>  // For caddr_t
#include <unistd.h>     // For _sbrk prototype (optional but good)
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>

int _write(int file, char *ptr, int len) {
  return len;
}

int _read(int file, char *ptr, int len) {
  return 0;
}

int _close(int file) {
  return -1;
}

int _fstat(int file, struct stat *st) {
  st->st_mode = S_IFCHR;
  return 0;
}

int _lseek(int file, int ptr, int dir) {
  return 0;
}

int _isatty(int file) {
  return 1;
}

void _exit(int status) {
  while(1);
}

int _kill(int pid, int sig) {
  errno = EINVAL;
  return -1;
}

int _getpid(void) {
  return 1;
}

caddr_t _sbrk(int incr) {
  extern char _end;
  static char *heap_end;
  char *prev_heap_end;

  if (heap_end == 0) {
    heap_end = &_end;
  }
  prev_heap_end = heap_end;
  heap_end += incr;
  return (caddr_t)prev_heap_end;
}

