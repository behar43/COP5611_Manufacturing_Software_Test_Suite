// Author: Ben Prishtina
// Purpose: Semester Project
// Class: COP 5611 Operating Systems Design Principles
#ifndef ETSS_H
#define ETSS_H
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include "ATP_ARG.h"
#include "staticworkers.h"
#include "defines.h"

//#define ATP_TEST_MAX 2
typedef void        (*VOIDFUNCPTR) (ARGS::ATP_ARG); // ptr to function returning void 

namespace ETSS
{
    class ATP_TEST_DEF
    {
        public:
            std::string name;
            VOIDFUNCPTR routine;
            std::string devname;
            int parm;
            int parm2;
    };

    class etss
    {
        public:
            void atp(unsigned int runMask, unsigned int stopMask);
            int atpTest(unsigned int tid, bool stopOnErr);
            void atpStatusSet(unsigned int tid, bool status);
            bool atpStatusCheck(unsigned int tid);
            void atpStop();
            bool atpTestStop(unsigned int tid);
            //Static
            static bool atpStatusCheckStatic(unsigned int tid);
            static void atpStatusSetStatic(unsigned int tid, bool status);
            //TESTS
            static void atpPing(ARGS::ATP_ARG arg);
            static void atpShm(ARGS::ATP_ARG arg);
            static void atpCanBus(ARGS::ATP_ARG arg);
        private:    
            ARGS::ATP_ARG atpArg[ATP_TEST_MAX];/* arguments passed to each test */
            ATP_TEST_DEF atpTestDef[ATP_TEST_MAX] = 
            {   
                {"GigE1", (VOIDFUNCPTR) atpPing, "localhost", 0, 0},//1 "192.168.1.80"
                {"CAN01", (VOIDFUNCPTR) atpCanBus, "canmess01:23:23:43:45:54:267:78:99:80:56:34:54:77:234:42:45:88:89:145:99", 0, 0},//2
                {"SHMEM", (VOIDFUNCPTR) atpShm, "shared_mem_test", 1234, 0}//3
            };
    };
}

bool sbcGpioStateSet(int bankNo, int pinNo, bool state);
#endif
