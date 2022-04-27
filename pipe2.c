include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

int main()
{
  int fd1[2], fd2[2], pid;

  if(pipe(fd1) == -1){
    printf("err in creating pipe");
  }
  if(pipe(fd2) == -2){
    printf("err in creating pipe");
  }

  pid = fork();

  if(pid == 0){
    //reading from pipe2
    close(fd2[1]);
    int x;
    read(fd2[0], &x, sizeof(x));
    printf("\n child read value %d from pipe 2\n", x);
    close(fd2[0]);

    //writing into pipe1
    x = x*10;
    printf("\n child write value %d\n",x);
    close(fd1[0]);
    write(fd1[1], &x, sizeof(x));
    close(fd1[1]);
  }
  else{
   // writing initial value into pipe 2
   close(fd2[0]);
   int a = 3;
   write(fd2[1], &a, sizeof(a));
   close(fd2[1]);
   printf("\nparent writes value %d into pipe 2\n", a);
   
   //reading from pipe 1
   close(fd1[1]);
   int x;
   read(fd1[0], &x, sizeof(x));
   printf("\nparent reads multiplied value from pipe 1 as %d\n", x);
   close(fd1[0]);
  }
}
