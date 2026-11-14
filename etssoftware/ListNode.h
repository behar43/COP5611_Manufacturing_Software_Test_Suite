// Author: Ben Prishtina
// Purpose: Semester Project
// Class: COP 5611 Operating Systems Design Principles
#ifndef LISTND_H
#define LISTND_H

namespace BLIST
{
    template< class NODETYPE > class List; // forward declaration
    
    template< class NODETYPE >
    class ListNode
    {
        friend class List< NODETYPE >; // make List a friend
        public:
            ListNode (const NODETYPE &info); // constructor
            NODETYPE getData() const;      // return data in the node
        private:
            NODETYPE data;                 // data
            ListNode< NODETYPE > *nextPtr; // next node in the list
    };
}
#include "ListNode.cpp"
#endif
