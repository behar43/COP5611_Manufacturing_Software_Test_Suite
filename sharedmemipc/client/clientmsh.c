// Author: Ben Prishtina
// Purpose: Semester Project
// Class: COP 5611 Operating Systems Design Principles
// Purpose: This is a stand alone client to test the servermsh 
//          This way I can also terminate the server properly by senging a "q"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
 
#define SHMSZ     1024
 
int main(void)
{
    int shmid;
    key_t key;
    char *shm;

    // We need to get the segment named
    // "1234", created by the server.
    key = 1234;

    // Locate the segment.
    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) 
    {
        perror("shmget");
        return 1;
    }

    //Now we attach the segment to our data space.
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) 
    {
        perror("shmat");
        return 1;
    }
    memset(shm,0,SHMSZ); // Zero out memory segment

    // Client writes user input character to memory
    // for server to read.
    for(;;)
    {
        char tmp = getchar();
        // Eat the enter key
        getchar();

        if(tmp == 'q')
        {
            *shm = 'q';
            break;
        }
        *shm = tmp;
    }

    if(shmdt(shm) != 0)
    {
        fprintf(stderr, "Could not close memory segment.\n");
    }
    return 0;
}

