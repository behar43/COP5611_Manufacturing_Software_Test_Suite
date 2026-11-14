// Author: Ben Prishtina
// Purpose: Semester Project
// Class: COP 5611 Operating Systems Design Principles
template< class NODETYPE > BLIST::Queue< NODETYPE >::Queue()
    :List < NODETYPE >()
{
}
template< class NODETYPE > BLIST::Queue< NODETYPE >::~Queue()
{
    std::cout << "CALLING: ~Queue()" << std::endl;
}
template< class NODETYPE > void BLIST::Queue< NODETYPE >::enqueue(const NODETYPE &value)
{
    Qmutex.lock();
    List<NODETYPE>::insertAtBack(value);
    Qmutex.unlock();
}
template< class NODETYPE > bool BLIST::Queue< NODETYPE >::dequeue(NODETYPE &value)
{
    bool retval;
    Qmutex.lock();
    retval = List<NODETYPE>::removeFromFront(value);
    Qmutex.unlock();
    return retval;
}

