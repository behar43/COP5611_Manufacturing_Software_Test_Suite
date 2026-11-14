// Author: Ben Prishtina
// Purpose: Semester Project
// Class: COP 5611 Operating Systems Design Principles
template< class NODETYPE > BLIST::List< NODETYPE >::List()
    :firstPtr(0), lastPtr(0)
{
}
template< class NODETYPE > BLIST::List< NODETYPE >::~List()
{
    std::cout << "CALLING: ~List()" << std::endl;
    if(!isEmpty())
    {
        std::cout << "Destroying nodes .. " <<std::endl;
        ListNode< NODETYPE > *currentPtr = firstPtr, *tempPtr;

        while (currentPtr != 0)
        {
            tempPtr = currentPtr;
            std::cout << tempPtr->data << std::endl;
            currentPtr = currentPtr->nextPtr;
            delete tempPtr;
        }
    }
}
template< class NODETYPE > void BLIST::List< NODETYPE >::insertAtFront(const NODETYPE &value)
{
    ListNode< NODETYPE > *newPtr = getNewNode(value);
    if(isEmpty())
    {
        firstPtr = lastPtr = newPtr;
    }
    else
    {
        newPtr->nextPtr = firstPtr;
        firstPtr = newPtr;
    }
}
template< class NODETYPE > void BLIST::List< NODETYPE >::insertAtBack(const NODETYPE &value)
{
    ListNode< NODETYPE > *newPtr = getNewNode(value);
    if(isEmpty())
    {
        firstPtr = lastPtr = newPtr;
    }
    else
    {
        lastPtr->nextPtr = newPtr;
        lastPtr = newPtr;
    }
}
template< class NODETYPE > bool BLIST::List< NODETYPE >::removeFromFront(NODETYPE &value)
{
    if(isEmpty())
    {
        return false;
    }
    else
    {
        ListNode< NODETYPE > *tempPtr = firstPtr;

        if(firstPtr == lastPtr)
        {
            firstPtr = lastPtr = 0;
        }
        else
        {
            firstPtr = firstPtr->nextPtr;
        }
        value = tempPtr->data; // data being removed
        delete tempPtr;
        return true;
    }
}
template< class NODETYPE > bool BLIST::List< NODETYPE >::removeFromBack(NODETYPE &value)
{
    if(isEmpty())
    {
        return false;
    }
    else
    {
        ListNode< NODETYPE > *tempPtr = lastPtr;

        if (firstPtr == lastPtr)
        {
            firstPtr = lastPtr = 0;
        }
        else
        {
            ListNode< NODETYPE > *currentPtr = firstPtr;
            while (currentPtr->nextPtr != lastPtr)
            {
                currentPtr = currentPtr->nextPtr;
            }
            lastPtr = currentPtr;
            currentPtr->nextPtr = 0;
        }
        value = tempPtr->data;
        delete tempPtr;
        return true;
    }
}
template< class NODETYPE > bool BLIST::List< NODETYPE >::isEmpty() const
{
    return firstPtr == 0;
}
template< class NODETYPE > BLIST::ListNode< NODETYPE > *BLIST::List< NODETYPE >::getNewNode(const NODETYPE &value)
{
    ListNode< NODETYPE > *ptr = new ListNode< NODETYPE >(value);
    assert(ptr != 0);
    return ptr;
}
template< class NODETYPE > void BLIST::List< NODETYPE >::print() const
{
    if( isEmpty())
    {
        std::cout << "The list is empty" << std::endl << std::endl;
        return;
    }
    ListNode< NODETYPE > *currentPtr = firstPtr;
    std::cout << "The list is:" << std::endl;
    while (currentPtr != 0)
    {
        std::cout << currentPtr->data << std::endl;
        currentPtr = currentPtr->nextPtr;
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

