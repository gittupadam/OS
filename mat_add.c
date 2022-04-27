#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>

#define matSz 5

int main()
{
        int shmid;
        key_t key;
        int* shm;

        int (*c)[5];

        int a[matSz][matSz], b[matSz][matSz];
        //int pid = getpid();

        for(int i=0;i<matSz;i++)
        {
                for(int j=0;j<matSz;j++)
                {
                        a[i][j] = rand()%100;
                        b[i][j] = rand()%100;
                }
        }

        printf("Matrix a\n");
        for(int i=0;i<matSz;i++)
        {
                for(int j=0;j<matSz;j++)
                {
                        printf("%d\t",a[i][j]);
                }
                putchar('\n');
        }
        printf("Matrix b\n");
        for(int i=0;i<matSz;i++)
        {
                for(int j=0;j<matSz;j++)
                {
                        printf("%d\t",b[i][j]);
                }
                putchar('\n');
        }

        key = 20101;
        shmid = shmget(key,sizeof(int[matSz][matSz]),IPC_CREAT|0666);
        c = shmat(shmid, NULL, 0);

        if(shmid<0)
        {
                perror("shmget");
                exit(1);
        }
        //s = shm;

        for(int i=0;i<matSz;i++)
        {
                if(fork()==0)
                {
                        for(int j=0;j<matSz;j++)
                        {
                                c[i][j] = a[i][j] + b[i][j];
                                //*s++ = c[i][j];
                        }
                        exit(0);
                }
                else{
                        wait(NULL);

                }

        }
        printf("Matrix c\n");
        for(int i=0;i<matSz;i++)
        {
                for(int j=0;j<matSz;j++)
                {
                        printf("%d\t",c[i][j]);
                }
                putchar('\n');
        }

        shmdt(c);
        shmctl(shmid,IPC_RMID,NULL);
        return 0;
}