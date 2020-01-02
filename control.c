#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <errno.h>

#define KEY 93847
#define SEG_SIZE 200

int main(){
  int shmd;
  char[600] story;
  char * addition;
  char input[3];
  if 
  shmd = shmget(KEY,SEG_SIZE,IPC_CREAT | IPC_EXCL |0644);
  
  
}
