// Author: Ben Prishtina
// Purpose: Semester Project
// Class: COP 5611 Operating Systems Design Principles
#ifndef ATP_ARG_H
#define ATP_ARG_H
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>

namespace ARGS
{
    class ATP_ARG 
    {
        public:
            ATP_ARG();
            ATP_ARG(int tid, bool stopOnErr, std::string devname, int parm, int parm2);
            ATP_ARG(int tid, std::string devname, int parm, int parm2);
            int get_tid();
            bool get_stopOnErr();
            std::string get_devname();
            int get_parm();
            int get_parm2();
            bool stopOnErr;

        private:
            int tid;
            std::string devname;
            int parm;
            int parm2;
    };
}
#endif
