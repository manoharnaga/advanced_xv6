#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"


#define NFORK 10
#define IO 5

int main() {
  int n, pid;
  int wtime=0, rtime=0;
  int twtime=0, trtime=0;
  for(n=0; n < NFORK;n++) {
      pid = fork();
      if (pid < 0)
          break;
      if (pid == 0) {
#ifndef FCFS
          if (n < IO) {
            sleep(200); // IO bound processes
          } else {
#endif
            for (volatile int i = 0; i < 1000000000; i++) {} // CPU bound process 
#ifndef FCFS
          }
#endif
          printf("\nProcess %d finished", n);
          exit(0);
      } else {
#ifdef PBS
        setpriority(80, pid); // Will only matter for PBS, set lower priority for IO bound processes 
#endif
#ifdef LBS
        settickets(100);   // sets the number of tickets of the calling process
#endif 
      }
  }
  for(;n > 0; n--) {
      if(waitx(0,&rtime,&wtime) >= 0) {
          trtime += rtime;
          twtime += wtime;
          //printf("==%d==\n",rtime);
      } 
  }
  printf("\nAverage rtime %d,  wtime %d\n", trtime / NFORK, twtime / NFORK);
  exit(0);
}