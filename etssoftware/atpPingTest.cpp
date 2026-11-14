// Author: Ben Prishtina
// Purpose: Semester Project
// Class: COP 5611 Operating Systems Design Principles
#include "etss.h"
#include "atpPingTest.h"
#include "Queue.h"
#include "ATP_LOG_REC.h"

extern BLIST::Queue<ATP_LOG_REC> theQs[ATP_TEST_MAX];
int ETSS::atp_ping_test::theping(std::string destination)
{
    pid_t pid = 0;
    int status;
    int retval = 0;

    pid = fork();
    if (pid == 0) 
    {
        printf("atpPing: I am the child.\\n");
        execl("/bin/ping", "/bin/ping", "-c", "4", destination.c_str(), (char *) 0);
        printf("atpPing: PING EXEC ERROR: In exec(): ");
        retval |= -1;
    }
    if (pid > 0) 
    {
        printf("atpPing: I am the parent, and the child is %d.\n", pid);
        pid = wait(&status); // wait for child process to end
        printf("atpPing: End of process %d: ", pid);
        if (WIFEXITED(status)) 
        {
            retval |= WEXITSTATUS(status);
            printf("atpPing: The process ended with exit(%d).\n", retval);
        }
        if (WIFSIGNALED(status)) 
        {
            retval |= WTERMSIG(status);
            printf("atpPing: The process ended with kill -%d.\n", retval);
        }
    }
    if (pid < 0) 
    {
        printf("atpPing: In fork():");
        retval = -2;
    }
    return retval;
}
//The ping TEST
void ETSS::etss::atpPing(ARGS::ATP_ARG arg)
{
    atp_ping_test ping_obj;
    unsigned int cnt = 0;           // loop counter 
    unsigned int errCnt = 0;            // loop counter 
    bool errFlag = false;       // error flag 
    int tid = arg.get_tid();
    bool stopOnErr = arg.get_stopOnErr();
    std::string pingStr = arg.get_devname();
    ATP_LOG_REC testresult;

    while (true)
    {
        cnt++;
        std::cout << "atpPing: ipaddress value is " << arg.get_devname() << " this is where I would do the ping" << std::endl;
        if (ping_obj.theping(arg.get_devname()) != 0)
        {
            //atpLog(atpMsgWarn, tid, atpErrPing, 0, cnt, 0);
            testresult.tid = tid;
            testresult.err = 3;
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
            testresult.err = 0;
            testresult.cnt = cnt;
            theQs[tid-1].enqueue(testresult);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        if (!etss::atpStatusCheckStatic(tid)) 
        {
            std::cout << "atpPing: atpStatusCheck returned FALSE" << std::endl;
            std::cout << "atpPing: TERMINATING TASK\n" << std::endl;
            break;
        }
    }
}
