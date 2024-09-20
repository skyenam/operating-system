#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// P100 -> P101 
//100 is a parent of 101
//and P100 creates another child P102 

int main(void) 
  pid_t pid = fork();
  if (pid > 0) {
    fork();
  //P101 (pid= 0)
  //P100 (pid =101)
  //P102 (pid=101)  which will end first because P101 goes to sleep for 2 secs
  }
//P101 (pid=0)
  if(pid==-1){
    return errno; 
  }
  if (pid == 0) {
    sleep(seconds: 2);
    return 42;
    //P101 (pid=0)
  }
  else {
    //P100 pid = 101
    printf("Calling wait\n");
    int wstatus;
    //P102 (pid=101)
    pid_t wait_pid = wait(&wstatus);
    if(wait_pid ==-1){
      print("crapp.........oopsie no children to wait for\n");
      return 34; //arbitrary cool number
    }
    if (WIFEXITED(wstatus)) {
      printf("Wait returned for an exited process! pid: %d, status: %d\n", wait_pid, WEXITSTATUS(wstatus));
    }
    else {
      return ECHILD;
    }
  }
  return 0;
}
