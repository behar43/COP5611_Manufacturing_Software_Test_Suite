// Author: Ben Prishtina
// Purpose: Semester Project
// Class: COP 5611 Operating Systems Design Principles
#include "etss.h"
#include "atpPingTest.h"
#include "Queue.h"
#include "ATP_LOG_REC.h"
#include "utilities.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <csignal>

#define SHMSZ     1024

extern BLIST::Queue<ATP_LOG_REC> theQs[ATP_TEST_MAX];

void ETSS::etss::atpShm(ARGS::ATP_ARG arg)
{
    int errorflag = 0;
    unsigned int cnt = 0;           // loop counter 
    unsigned int errCnt = 0;            // loop counter 
    bool errFlag = false;       // error flag 
    int tid = arg.get_tid();
    bool stopOnErr = arg.get_stopOnErr();
    ATP_LOG_REC testresult;
    int shmid;
    key_t key;
    char *shm;
    unsigned int counter = 0;

    key = (key_t)arg.get_parm(); //shared memory key

    pid_t pid = 0;
    int status;

    pid = fork();
    if (pid == 0) 
    {
        printf("atpShm: I am the child.\\n");
        execl("../sharedmemipc/sharedmemserver/servermsh", "../sharedmemipc/sharedmemserver/servermsh", NULL);
        printf("atpShm: In exec(): ");
        errorflag |= -1;
    }
    if (pid > 0) 
    {
        printf("atpShm: I am the parent, and the child is %d.\n", pid); 
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    }
    if (pid < 0) 
    {
        printf("atpShm: In fork()\n");
        errorflag |= -2;
    }

    //Locate the segment.
    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) 
    {
        std::cout << "atpShm: shmget error " << std::endl;
        errorflag = 1;
    }
    //attach the segment to our data space.
    if ((shm = (char*)shmat(shmid, NULL, 0)) == (char *) -1) 
    {
        std::cout << "atpShm: shmat error " << std::endl;
        errorflag = 2;
    }
    memset(shm,0,SHMSZ); // zero out the segment

    const char* bytestosend = arg.get_devname().c_str();

    while (true)
    {
        cnt++;
        std::cout << "atpShm: Shared Memory Test " << arg.get_devname() << " and this is the key " << arg.get_parm() << std::endl;

        pid_t result = waitpid(pid, &status, WNOHANG);

        if (result == 0)
        {
            std::cout << "atpShm: Child is still running..." << std::endl;
        }
        else if (result == pid)
        {
            if (WIFEXITED(status))
            {
                errorflag |= WEXITSTATUS(status);
                std::cout << "atpShm: ERROR Child exited with status " << errorflag << std::endl;
            }
            else if (WIFSIGNALED(status))
            {
                errorflag |= WTERMSIG(status);
                std::cout << "atpShm: ERROR Child was terminate by signal " << errorflag << std::endl;
            }
            else
            {
                errorflag |= 8;
                std::cout << "atpShm: Child was terminate by an unknown error" << std::endl;
            }
            
        }
        else
        {
            errorflag |= 9;
            std::cout << "atpShm: waitpid error" << std::endl;
        }
        
        if (bytestosend[counter] != '\0')
        {
            *shm = bytestosend[counter];
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            if(consume_char_ipc_Q() == bytestosend[counter])
            {
                std::cout << "atpShm: Shared Memory server reports the same byte" << std::endl;
                errorflag |= 0;
            }
            else //error
            {
                std::cout << "atpShm: ERROR = " << errorflag << std::endl;
                errorflag |= 4;
            }
            counter++;
        }
        else
        {
            *shm = 'X';
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            if(consume_char_ipc_Q() == 'X')
            {
                std::cout << "atpShm: Shared Memory server reports the same byte" << std::endl;
                errorflag |= 0;
            }
            else //error
            {
                std::cout << "atpShm: ERROR = " << errorflag << std::endl;
                errorflag |= 5;
            }
            counter = 0;
        }

        if (errorflag != 0)
        {
            //atpLog(atpMsgWarn, tid, atpErrPing, 0, cnt, 0);
            testresult.tid = tid;
            testresult.err = errorflag; 
            testresult.cnt = cnt;
            theQs[tid-1].enqueue(testresult);
            errFlag = true;
            if (errFlag) 
            {
                errCnt++;
                if (stopOnErr) 
                {
                    etss::atpStatusSetStatic(tid, false);
                    break;
                } 
                else 
                {
                    errFlag = false;
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
            }
        }
        else
        {
            testresult.tid = tid;
            testresult.err = errorflag;
            testresult.cnt = cnt;
            theQs[tid-1].enqueue(testresult);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        if (!etss::atpStatusCheckStatic(tid)) 
        {
            *shm = 'q';
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            if(shmdt(shm) != 0)
            {
                std::cout << "Could not close memory segment." << std::endl;
            }
            std::cout << "atpShm: atpStatusCheck returned FALSE" << std::endl;
            std::cout << "atpShm: TERMINATING TASK\n" << std::endl;
            break;
        }
    }
    
}
