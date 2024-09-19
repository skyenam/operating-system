#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int print_state(pid_t pid) {
  char buffer[4096];
  int ret = snprintf(buffer, sizeof(buffer), "/proc/%d/status", pid);
  if (ret < 0) {
    return ret;
  }
  int fd = open(buffer, O_RDONLY);
  if (fd < 0) {
    printf("unknown (macOS?)\n");
    return fd;
  }
  ret = read(fd, buffer, sizeof(buffer));
  if (ret < 0) {
    return ret;
  }
  close(fd);

  ssize_t bytes_read = ret;
  char state_prefix[] = "State:\t";
  for (int i = 0; i < bytes_read; ++i) {
    size_t remaining = bytes_read - i;
    size_t state_len = sizeof(state_prefix) - 1;
    if (remaining < state_len) {
      break;
    }
    if (strncmp(buffer + i, state_prefix, state_len) == 0) {
      for (int j = (i + state_len); j < bytes_read; ++j) {
	      ret = printf("%c", buffer[j]);
	      if (ret < 0) {
	        return ret;
	      }
	      if (buffer[j] == '\n') {
	        break;
	      }
      }
      break;
    }
  }

  return 0;
}

int main(void) {
  pid_t pid = fork(); //we fork to create another process (we have 2 in total).
  if (pid == -1) {
    return errno;
  }
  if (pid == 0) { //child exists for 2 secs
    sleep(2);
  }
  else {
    int ret;
    sleep(1); //parent sleeps for 1 sec
    printf("Child process state: "); //wakes up, print child's process state
    ret = print_state(pid); // note:child should be still sleeping since it's 1 sec in (child is sleeping for 2 sec)
	  //would output "Child's proess state: S (sleeping)
    if (ret < 0) { return errno; }
    sleep(2); // so we wait another 2 sec
    printf("Child process state: "); //print child's proces state (3 secs have elapsed)
    ret = print_state(pid);
	  //would output "Child's process state : Z (zombie) 
	 	 //zombie means child terminated but wait is not called yet so PID still exists 
    if (ret < 0) { return errno; }
  }
  return 0;
}
