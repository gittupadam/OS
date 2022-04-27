#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
void main()
{
        int forkresult;

        printf("I am the parent. Remember My Process-id! : %d\n", getpid());
        printf("Parent now going to fork ... \n");

        forkresult=fork();

        if(forkresult==-1)
        {
                printf("Fork failed\n");
                exit(0);
        }
        else if(forkresult!=0)
        {
                printf("Parent will execute this code\n");
                printf("Parent prints:My child's pid is %d\n", forkresult);
                wait(NULL);
                printf("Parent executes pwd\n");
                execlp("pwd","pwd",NULL);
                printf("This line gets printed when the above exec statement pwd fails\n");
        }
        else
        {
                printf("Hi ! I am the child with process-id %d.\n",getpid());
                printf("I'm now going to execute ls!\n\n\n");
                execlp ("ls", "ls", NULL);
                printf ("Child prints %d: AAAAH ! ! My EXEC failed ! ! ! !\n", getpid());
                exit(1);
        }
        printf ("Process id %d prints : like father like son. \n", getpid());
}
