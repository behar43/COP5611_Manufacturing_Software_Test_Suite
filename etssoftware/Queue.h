// Author: Ben Prishtina
// Purpose: Semester Project
// Class: COP 5611 Operating Systems Design Principles
#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include <cassert>
#include <mutex>
#include "List.h"
namespace BLIST
{
    template< class NODETYPE > 
    class Queue : public List < NODETYPE >
    {
        public:
            Queue();
            ~Queue();
            void enqueue(const NODETYPE &value);
            bool dequeue(NODETYPE &value);
        private:
            std::mutex Qmutex;
    };
}
#include "Queue.cpp"
#endif
