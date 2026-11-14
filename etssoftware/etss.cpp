// Author: Ben Prishtina
// Purpose: Semester Project
// Class: COP 5611 Operating Systems Design Principles
#include "etss.h"
#include "Queue.h"
#include "ATP_LOG_REC.h"

BLIST::Queue<ATP_LOG_REC> theQs[ATP_TEST_MAX];
bool atpStatus[ATP_TEST_MAX];/* test running status array */
std::mutex atpSemStatus;

void ETSS::etss::atp(unsigned int runMask, unsigned int stopMask)
{
    int tid;
    int i;
    int testNum = ATP_TEST_MAX;

    for (i = 0; i < testNum; i++)
    {
        printf("ATP: index %d\n", i);
        tid = i+1;
        ARGS::ATP_ARG localArg(tid, 
                atpTestDef[i].devname, 
                atpTestDef[i].parm, 
                atpTestDef[i].parm2);
        atpArg[i] = localArg;
        atpArg[i].stopOnErr = (stopMask & (1 << (atpArg[i].get_tid() -1)))? true : false;
        if(STCW::staticworkers::get_bit(runMask, i))
        {
            std::thread atptest(atpTestDef[tid-1].routine, atpArg[tid-1]);
            atptest.detach();
            atpStatusSet(tid, true);

            printf("etss: Launched TEST ID: %d with stopMask = 0x%X , runMask = 0x%X\n", tid, stopMask, runMask);
        }
    }
}
int ETSS::etss::atpTest(unsigned int tid, bool stopOnErr)
{
    unsigned int testNum = ATP_TEST_MAX;
    int retval = 0;
    if (tid < 1 || tid > testNum) 
    {
        std::cout << "Invalid test ID " << std::endl;
        return 1;
    }
    if (!atpStatusCheck(tid))
    {
        std::cout << "Starting Test ID (tid) " << tid << std::endl;
        std::cout << "stopOnErr " << stopOnErr << std::endl;
    
        ARGS::ATP_ARG localArg(tid, stopOnErr, 
                atpTestDef[tid-1].devname, 
                atpTestDef[tid-1].parm, 
                atpTestDef[tid-1].parm2);
    
        atpArg[tid-1] = localArg;
    
        std::thread atptest(atpTestDef[tid-1].routine, atpArg[tid-1]);
        atptest.detach();
        atpStatusSet(tid, true);
    }
    else
    {
        std::cout << "Test ID (tid) " << tid << " is running" << std::endl;
        retval = -2;
    }
    return retval;
}

void ETSS::etss::atpStatusSet(unsigned int tid, bool status)
{
    atpSemStatus.lock();
    atpStatus[tid-1] = status;
    atpSemStatus.unlock();
}
bool ETSS::etss::atpStatusCheck(unsigned int tid)
{
    bool retval = false;
    atpSemStatus.lock();
    retval = atpStatus[tid-1];
    atpSemStatus.unlock();
    return retval;
}
void ETSS::etss::atpStatusSetStatic(unsigned int tid, bool status)
{
    atpSemStatus.lock();
    atpStatus[tid-1] = status;
    atpSemStatus.unlock();
}
bool ETSS::etss::atpStatusCheckStatic(unsigned int tid)
{
    bool retval = false;
    atpSemStatus.lock();
    retval = atpStatus[tid-1];
    atpSemStatus.unlock();
    return retval;
}
void ETSS::etss::atpStop()
{
    for (unsigned int i=0; i < ATP_TEST_MAX; i++) 
    {
        if (atpStatusCheck(i+1) == true) 
        {
            atpStatusSet(i+1, false);
        }
    }
}
bool ETSS::etss::atpTestStop(unsigned int tid)
{
    unsigned int testNum = ATP_TEST_MAX;
    bool retval = false;
    
    if (tid < 1 || tid > testNum) {
        std::cout << "Invalid test ID" << std::endl;
        return false;
    }
    
    if (atpStatusCheck(tid)) 
    {
        std::cout << "B:testID: " << tid << " ::::: atpStatus[" << tid << "-1] = "<< atpStatus[tid-1] << std::endl;
    
        atpStatusSet(tid, false);
        std::cout << "A:testID: " << tid << " ::::: atpStatus[" << tid << "-1] = "<< atpStatus[tid-1] << std::endl;
        retval = true;
    } 
    else 
    {
        std::cout << "The test " << tid << " is not running." << std::endl;
        retval = false;
    }
    return retval;
}
// non members
bool sbcGpioStateSet(int bankNo, int pinNo, bool state)
{
    std::cout << "Simulator bankNo: " << bankNo << std::endl;
    std::cout << "Simulator pinNo: " << pinNo << std::endl;
    std::cout << "Simulator state: " << state << std::endl;

    if (bankNo == 0)
    {
        std::cout << "Simulator returning invalid bank: " << bankNo << std::endl;
        return false; 
    }
    else
    {
        std::cout << "Simulator returning valid bank: " << bankNo << std::endl;
        return true;
    }
}

