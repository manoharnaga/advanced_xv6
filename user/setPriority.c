#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main(int argc, char *argv[])
{
  printf("hello\n");
  if(argc < 3){
    printf("Less number of arguments!!\n");
    return 0;
  }
  int old_sp = setpriority(atoi(argv[1]),atoi(argv[2]));
  printf("Old static priority: %d\n",old_sp);
  return 0;
}
