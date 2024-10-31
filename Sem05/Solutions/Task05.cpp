int getNumOnIdxX(int X, const SinglyLinkedList& sll)
{
    if(X >= sll.size)
        return -1;
    
    Node* head = sll.head;
    int pos = 0;
    while(head)
    {
        if(pos == X)
            return head->value;
        
        pos++;
        head = head->next;
    }
    
    return -1;
}

void SinglyLinkedList::replace(int X)
{
    int a = getNumOnIdxX(X, *this);

    if(a == -1)
        return;
  
    Node* curr = head;
    while(curr)
    {
        if(curr->value == a && curr->next)
        {
            curr->value = curr->next->value;
        }
        
        curr = curr->next;
    }
}
