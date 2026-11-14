#include "etss.h"
#include "atpPingTest.h"
#include "Queue.h"
#include "utilities.h"
#include "ATP_LOG_REC.h"

extern BLIST::Queue<ATP_LOG_REC> theQs[ATP_TEST_MAX];

void ETSS::etss::atpCanBus(ARGS::ATP_ARG arg)
{
    int errorflag = 0;
    unsigned int cnt = 0;           // loop counter 
    unsigned int errCnt = 0;            // loop counter 
    bool errFlag = false;       // error flag 
    int tid = arg.get_tid();
    bool stopOnErr = arg.get_stopOnErr();
    ATP_LOG_REC testresult;

    ret_param retvalstruct;
    std::string ldata[20];
    char chararr[20];

    for (int i = 0; i < 20; i++)
    {
        ldata[i] = "";
        chararr[i] = '\0';
    }

    while (true)
    {
        cnt++;
        std::cout << "Sending CAN message" << arg.get_devname() << std::endl;
        ParseParametersFromString(arg.get_devname().c_str(), &retvalstruct);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        for(int i = 0; i < 20; i++) 
        {
            ldata[i] = std::to_string(retvalstruct.data[i]);
        }

        for(int i = 0; i < 20; i++) 
        {
            vxcan_loop(retvalstruct.data[i], chararr, i);  // loop back CAN data to ETS
            std::string thestring(chararr);
            if (ldata[i] == thestring)
            {
                errorflag |= 0;
            }
            else
            {
                errorflag |= 1;
            }
        }

        if (errorflag != 0)
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
            std::cout << "atpCanBus: atpStatusCheck returned FALSE" << std::endl;
            std::cout << "atpCanBus: TERMINATING TASK\n" << std::endl;
            break;
        }
    }
}
