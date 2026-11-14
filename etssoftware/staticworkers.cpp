// Author: Ben Prishtina
// Purpose: Semester Project
// Class: COP 5611 Operating Systems Design Principles
#include "staticworkers.h"

bool STCW::staticworkers::get_bit(unsigned int data, unsigned int bitNumber)
{
    return (data & (1UL << bitNumber));
}
