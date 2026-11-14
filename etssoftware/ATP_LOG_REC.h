// Author: Ben Prishtina
// Purpose: Semester Project
// Class: COP 5611 Operating Systems Design Principles
#ifndef ATP_LOG_REC_H
#define ATP_LOG_REC_H
#include <iostream>
class ATP_LOG_REC
{
    public:
        ATP_LOG_REC();
        ATP_LOG_REC(unsigned int mid, 
                            unsigned int tid,
                            unsigned int err,
                            unsigned int dev,
                            unsigned int cnt,
                            unsigned int dat);
        ATP_LOG_REC(const ATP_LOG_REC &copy);
        const ATP_LOG_REC &operator=(const ATP_LOG_REC &right);
        friend std::ostream& operator<< (std::ostream& stream, const ATP_LOG_REC &thelog);

        unsigned int mid; //message id
        unsigned int tid; //test ID
        unsigned int err; //error code
        unsigned int dev; //device ID
        unsigned int cnt; //loop counter
        unsigned int dat; //extra info
};
#endif

