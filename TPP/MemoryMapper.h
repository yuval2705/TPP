#pragma once
#include <cstdlib>

void* operator new(std::size_t size);
void* operator new(std::size_t size, void* ptr);

void* operator new[](std::size_t size);
void* operator new[](std::size_t size, void* ptr);
