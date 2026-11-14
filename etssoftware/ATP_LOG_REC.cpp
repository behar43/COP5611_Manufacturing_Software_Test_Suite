// Author: Ben Prishtina
// Purpose: Semester Project
// Class: COP 5611 Operating Systems Design Principles
#include "ATP_LOG_REC.h"

ATP_LOG_REC::ATP_LOG_REC()
{
    this->mid = 0;
    this->tid = 0;
    this->err = 0;
    this->dev = 0;
    this->cnt = 0;
    this->dat = 0;
}
ATP_LOG_REC::ATP_LOG_REC(unsigned int mid, 
                            unsigned int tid,
                            unsigned int err,
                            unsigned int dev,
                            unsigned int cnt,
                            unsigned int dat)
{
    this->mid = mid;
    this->tid = tid;
    this->err = err;
    this->dev = dev;
    this->cnt = cnt;
    this->dat = dat;
}
ATP_LOG_REC::ATP_LOG_REC(const ATP_LOG_REC &copy)
{
    this->mid = copy.mid;
    this->tid = copy.tid;
    this->err = copy.err;
    this->dev = copy.dev;
    this->cnt = copy.cnt;
    this->dat = copy.dat;
}
const ATP_LOG_REC &ATP_LOG_REC::operator=(const ATP_LOG_REC &right)
{
    if (&right != this) //avoid self assignment
    {
        this->mid = right.mid;
        this->tid = right.tid;
        this->err = right.err;
        this->dev = right.dev;
        this->cnt = right.cnt;
        this->dat = right.dat;  
    }
    return *this; //return myself, enables cascaded assignements
}
std::ostream& operator<< (std::ostream& stream, const ATP_LOG_REC &thelog)
{
    stream << "thelog.mid = " << thelog.mid << std::endl;
    stream << "thelog.tid = " << thelog.tid << std::endl;
    stream << "thelog.err = " << thelog.err << std::endl;
    stream << "thelog.dev = " << thelog.dev << std::endl;
    stream << "thelog.cnt = " << thelog.cnt << std::endl;
    stream << "thelog.dat = " << thelog.dat << std::endl;
    return stream;
}
