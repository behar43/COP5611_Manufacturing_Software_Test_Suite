// Author: Ben Prishtina
// Purpose: Semester Project
// Class: COP 5611 Operating Systems Design Principles
#include "ATP_ARG.h"

ARGS::ATP_ARG::ATP_ARG()
:devname()
{
    this->tid = 1;
    this->stopOnErr = false;
    this->parm = 0;
    this->parm2 = 0;
}
ARGS::ATP_ARG::ATP_ARG(int tid, bool stopOnErr, std::string devname, int parm, int parm2)
:devname(devname)
{
    this->tid = tid;
    this->stopOnErr = stopOnErr;
    this->parm = parm;
    this->parm2 = parm2;
}
ARGS::ATP_ARG::ATP_ARG(int tid, std::string devname, int parm, int parm2)
:devname(devname)
{
    this->tid = tid;
    this->stopOnErr = false;
    this->parm = parm;
    this->parm2 = parm2;
}
int ARGS::ATP_ARG::get_tid()
{
    return tid;
}
bool ARGS::ATP_ARG::get_stopOnErr()
{
    return stopOnErr;
}
std::string ARGS::ATP_ARG::get_devname()
{
    return devname;
}
int ARGS::ATP_ARG::get_parm()
{
    return parm;
}
int ARGS::ATP_ARG::get_parm2()
{
    return parm2;
}

