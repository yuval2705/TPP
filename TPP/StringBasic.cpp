#include <stdlib.h>
#include <string>
#include <exception>
#include "StringBasic.h"

StringBasic::StringBasic(char* str)
{
    this->m_length = (unsigned)std::strlen(str);

    this->m_str = new char[this->m_length + 1]{0};
    std::memcpy(this->m_str, str, m_length);
}

StringBasic::StringBasic(const char str[]) : StringBasic((char*)(str))
{
    // This is empty on purpose! We want the same things to happen for each type.
}

StringBasic::StringBasic() : StringBasic("")
{
    // This is empty on purpose! We want the same things to happen for each type.
}

StringBasic::StringBasic(char chr) : StringBasic("-")
{
    this->m_str[0] = chr;
}

StringBasic::StringBasic(const StringBasic& str) : StringBasic(str.getStr())
{
    // This is empty on purpose! We want the same things to happen for each type.
}

unsigned StringBasic::getLength() const
{
    return this->m_length;
}

char* StringBasic::getStr() const
{
    return this->m_str;
}

StringBasic::~StringBasic()
{
    delete[] this->m_str;
}

bool StringBasic::isEmpty() const
{
    return (this->m_length == 0) || (this->m_str == nullptr);
}

char& StringBasic::operator[](std::size_t i)
{
    if (i < 0 || i >= this->m_length)
    {
        throw std::runtime_error("Index is out of bounds!");
    }

    return this->m_str[i];
}

int StringBasic::compare(char* str) const
{
    return std::strcmp(this->m_str, str);
}

int StringBasic::compare(const StringBasic& str) const
{
    return this->compare(str.getStr());
}

int StringBasic::compare(const char str[]) const
{
    return this->compare((char*)str);
}

void StringBasic::append(const char* str)
{
    unsigned appended_str_length = (unsigned)std::strlen(str);

    char* new_m_str = new char[this->m_length + appended_str_length + 1]{0};
    std::memcpy(new_m_str, this->m_str, this->m_length);
    std::memcpy(new_m_str + this->m_length, str, appended_str_length);
    delete[] this->m_str;
    this->m_str = new_m_str;
    this->m_length = appended_str_length + this->m_length;
}

void StringBasic::append(const StringBasic& str)
{
    this->append(str.getStr());
}

unsigned StringBasic::replace(char oldC, char newC)
{
    char* swappingPointer = std::strchr(this->m_str, oldC);
    *swappingPointer = oldC;
    return (unsigned) (swappingPointer - this->m_str);
}