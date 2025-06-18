#include "MemoryMapper.h"
#include <cstdio>
#include <cstdlib>

void* operator new(std::size_t size)
{
    std::printf("Size = %zu\n", size);
    return nullptr;
}

void* operator new(std::size_t size, void* ptr)
{
    std::printf("Size = %zu | ptr = %p\n", size, ptr);
    return nullptr;
}

void* operator new[](std::size_t size)
{
    std::printf("Size = %zu\n", size);
    return nullptr;
}

void* operator new[](std::size_t size, void* ptr)
{
    std::printf("Size = %zu | ptr = %p\n", size, ptr);
    return nullptr;
}