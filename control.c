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

int main(int argc, char * argv[]){
  int shmd;
  int semd;
  FILE * ptr;
  int filenum;
  if (argc < 2){
    printf("Include command line argument");
    exit(0);
  }
  if (strcmp(argv[1],"-c") == 0){
      semd = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
      if (semd == -1){
	printf("error %d: %s\n", errno, strerror(errno));
	exit(0);
      }
      else {
	union semun us;
	us.val = 1;
        semctl(semd, 0, SETVAL, us);
	printf("semaphore created\n");
      }
      if ((shmd = shmget(KEY,SEG_SIZE, IPC_CREAT | IPC_EXCL | 0644)))
	printf("shared memory segment created\n");
      else{
	printf("error %d: %s\n", errno, strerror(errno));
	exit(0);
      }
      ptr = fopen("story.txt","w+");
      filenum = fileno(ptr);
      close(filenum);
      printf("file created\n");
  }
  if (strcmp(argv[1],"-v") == 0){
    printf("The story so far:\n");
    ptr = fopen("story.txt","r");
    filenum = fileno(ptr);
    char buff[SEG_SIZE];
    while (fgets(buff,SEG_SIZE,ptr)){
      printf("%s",buff);
    }
    close(filenum);
  }
  if (strcmp(argv[1],"-r") == 0){
    semd = semget(KEY, 1, 0);
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_op = -1;
    printf("waiting to get in\n");
    printf("The story so far:\n");
    ptr = fopen("story.txt","r");
    filenum = fileno(ptr);
    char buff[SEG_SIZE];
    while (fgets(buff,SEG_SIZE,ptr)){
      printf("%s",buff);
    }
    shmd = shmget(KEY,SEG_SIZE,0);
    semd = semget(KEY,1,0);
    semop(semd, &sb, 1);
    shmctl(shmd,IPC_RMID,0);
    printf("shared memory removed\n");
    semctl(semd,IPC_RMID, 0);
    printf("semaphone removed\n");
    close(filenum);
    printf("file closed\n");
  }
}
