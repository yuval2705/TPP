#pragma once
#include "MemoryEntry.h"


class MemoryEntryList
{
  public:
    MemoryEntryList();
    MemoryEntry* getValue();
    MemoryEntryList* getPrev();
    MemoryEntryList* getNext();

    void setPrev(MemoryEntryList* prev);
    void setNext(MemoryEntryList* next);

    unsigned getTotalSize();

  private:
    MemoryEntryList* m_prev;
    MemoryEntry* const m_value;
    MemoryEntryList* m_next;
};
