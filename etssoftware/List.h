// Author: Ben Prishtina
// Purpose: Semester Project
// Class: COP 5611 Operating Systems Design Principles
#ifndef LIST_H
#define LIST_H
#include <iostream>
#include <cassert>
#include "ListNode.h"
namespace BLIST
{
    template< class NODETYPE > 
    class List
    {
        public:
            List();// Constructor
            virtual ~List(); // destructor
            void insertAtFront(const NODETYPE &value);
            void insertAtBack(const NODETYPE &value);
            bool removeFromFront(NODETYPE &value);
            bool removeFromBack(NODETYPE &value);
            bool isEmpty() const;
            void print() const;
        private:
            ListNode< NODETYPE > *firstPtr; //ptr to first node
            ListNode< NODETYPE > *lastPtr;  //ptr to last node
            //Utility function to allocate a new node
            ListNode< NODETYPE > *getNewNode( const NODETYPE &value );
    };
}
#include "List.cpp"
#endif
