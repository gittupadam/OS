#include<unistd.h>
#include<sys/wait.h>
#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
        int pipe1fd[2];

        pid_t pid;
        int status;

        pipe(pipe1fd);

        switch(pid=fork())
        {
                case -1:  printf("can't fork");
                          exit(-1);
                case 0:
                          dup2(pipe1fd[1],1);
                          close(pipe1fd[0]);
                          execlp("pwd","pwd",NULL);
                default:
                          wait(&status);
                          dup2(pipe1fd[0],0);
                          close(pipe1fd[1]);
                          execlp("wc","wc",NULL);
        }
}
