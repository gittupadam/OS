//SERVER

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define SHMSZ     27

int main()
{
    char c;
    int shmid;
    key_t key;
    char *shm, *s;

    // We'll name our shared memory segment "5678".
    key = 5678;
    shmid = shmget(key, SHMSZ, IPC_CREAT | 0666);

    //Create the segment.
    if (shmid < 0)
    {
        perror("shmget");
        exit(1);
    }

    //Now we attach the segment to our data space.
    shm = shmat(shmid, NULL, 0);
    if (shm == (char *) -1)
    {
        perror("shmat");
        exit(1);
    }

   //Now put some things into the memory for the  other process to read.
     s = shm;

    for (c = 'a'; c <= 'z'; c++)
        *s++ = c;
    *s = NULL;

    /*
     * Finally, we wait until the other process
     * changes the first character of our memory
     * to '*', indicating that it has read what we put there.
     */
    while (*shm != '*')
        sleep(1);

    shmdt(shm);
    shmctl(shmid,IPC_RMID,NULL);
    exit(0);
}

//CLIENT

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include<stdlib.h>

#define SHMSZ     27

int main()
{
    int shmid;
    key_t key;
    char *shm, *s;

    // We need to get the segment named "5678", created by the server.
      key = 5678;

    //Locate the segment.
    shmid = shmget(key, SHMSZ, 0666);
    if (shmid < 0)
    {
        perror("shmget");
        exit(1);
    }

    //Now we attach the segment to our data space.
    shm = shmat(shmid, NULL, 0);
    if (shm == (char *) -1)
    {
        perror("shmat");
        exit(1);
    }

    //Now read what the server put in the memory.
    for (s = shm; *s != NULL; s++)
        putchar(*s);
    putchar('\n');

    /*
     * Finally, change the first character of the
     * segment to '*', indicating we have read the segment.
     */
    *shm = '*';

     shmdt(shm);
    exit(0);
}
