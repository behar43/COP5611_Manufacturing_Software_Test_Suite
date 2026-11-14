// Author: Ben Prishtina
// Purpose: Semester Project
// Class: COP 5611 Operating Systems Design Principles
template<class NODETYPE> BLIST::ListNode< NODETYPE >::ListNode(const NODETYPE &info)
    : data(info), nextPtr(0)
{
}
template<class NODETYPE > NODETYPE BLIST::ListNode< NODETYPE >::getData() const
{
    return data;
}
