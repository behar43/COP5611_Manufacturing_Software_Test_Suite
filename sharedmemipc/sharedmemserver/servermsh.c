// Author: Ben Prishtina
// Purpose: Semester Project
// Class: COP 5611 Operating Systems Design Principles
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>   // For isprint()
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
 
#define SHMSZ 1024
#define QUEUE_NAME "/my_queue"
 
int main()
{
    int shmid;
    key_t key;
    char *shm;
    mqd_t mq;
    struct mq_attr attr;

    //configure the queue attributes
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(char);
    attr.mq_curmsgs = 0;

    // Create the message queue to produce what I got from shared memory
    // so it can be verified by the ETS
    mq = mq_open(QUEUE_NAME, O_CREAT | O_WRONLY, 0644, &attr);
    if (mq == (mqd_t)-1)
    {
        printf("ERROR servermsh: mq_open");
    }

    key = 1234; // Shared memory segment at 1234

    // Create the segment and set permissions.
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) 
    {
        printf("ERROR servermsh: shmget");
        return 1;
    }
    
    // Now we attach the segment to our data space.
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) 
    {
        printf("ERROR servermsh: shmat");
        return 1;
    }
    memset(shm,0,SHMSZ); // Zero out memory segment

    //  Read user input from client code and tell
    //  the user what was written.
    while (*shm != 'q')
    {
        sleep(1);
        if (*shm == '\0' || *shm == ' ' || !isprint(*shm)) //only print printable characters, no empty, new line ...
            continue;

        printf("servermsh: You pressed %c\n", *shm);
        if (mq_send(mq, shm, sizeof(char), 0) == -1)
        {
            printf("ERROR servermsh: mq_send");
        }

        if (*shm != 'q')
        {
            memset(shm,0,SHMSZ); // Zero out memory if not "q"
        }
    }
    mq_close(mq);
    mq_unlink(QUEUE_NAME);

    if(shmdt(shm) != 0)
    {
        printf("ERROR servermsh: Could not close memory segment.\n");
    }
    return 0;
}

