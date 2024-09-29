//running the program lets you write in the terminal. if you press enter it will spit back whatever you wrote


#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
  char buffer[4096];
  ssize_t bytes_read;
  while ((bytes_read = read(fd:0, buf:buffer, nbytes: sizeof(buffer))) > 0) {
    ssize_t bytes_written = write(fd:1, buf: buffer, n: bytes_read);
    if (bytes_written == -1) {
      int err = errno;
      perror("write");
      return err;
    }
    assert(bytes_read == bytes_written); //sanity check: if false, will crash the program
  }
  if (bytes_read == -1) {
    int err = errno;
    perror("read");
    return err;
  }
  assert(bytes_read == 0);
  return 0;
}
