#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
  pid_t pid = fork();
  if (pid == -1) {
    int err = errno;
    perror("fork failed");
    return err;
  }
  //it got orphaned because parent lasted 1 sec and child lasted 2 sec. 
  //child 
  if (pid == 0) {
    printf("Child parent pid: %d\n", getppid()); //get parent process ID -> it will print original parent's PID
    sleep(2);
    printf("Child parent pid (after sleep): %d\n", getppid()); // it will print a new parent's PID: 1721, which is systemd (init)
  }
    
  //parent sleeps for 1 sec then return
  else {
    sleep(1);
  }
  return 0;
}


