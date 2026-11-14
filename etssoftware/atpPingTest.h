// Author: Ben Prishtina
// Purpose: Semester Project
// Class: COP 5611 Operating Systems Design Principles
#ifndef ATP_PING_TEST_H
#define ATP_PING_TEST_H
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <csignal>

namespace ETSS
{
    class atp_ping_test
    {
        public:
            int theping(std::string destination);
    };
}
#endif
