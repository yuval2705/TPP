#include "MemoryEntryList.h"



MemoryEntryList* MemoryEntryList::getPrev()
{
    return this->m_prev;
}

MemoryEntryList* MemoryEntryList::getNext()
{
    return this->m_next;
}

MemoryEntry* MemoryEntryList::getValue()
{
    return this->m_value;
}


unsigned MemoryEntryList::getTotalSize()
{
    if (this->m_next == nullptr)
    {
        return 1;
    }
    return 1 + this->m_next->getTotalSize();
}