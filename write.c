#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <errno.h>

#define KEY 93847
#define SEG_SIZE 200

int main(){
  char * addition;
  int semd = semget(KEY,1,0);
  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_op = -1;
  printf("trying to get in!\n");
  semop(semd, &sb, 1);
  int shmd = shmget(KEY,SEG_SIZE,0);
  addition = shmat(shmd,0,0);
  printf("Last Addition: %s\n",addition);
  printf("Your Addition: ");
  fgets(addition, SEG_SIZE, stdin);
  FILE * fp = fopen("story.txt","a");
  fputs(addition,fp);
  shmdt(addition);
  sb.sem_op = 1;
  semop(semd, &sb, 1);
}
