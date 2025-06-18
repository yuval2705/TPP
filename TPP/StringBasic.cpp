#include <stdlib.h>
#include "StringBasic.h"
#include <string>



StringBasic::StringBasic(const char str[])
{
    this->m_length = (unsigned)std::strlen(str);

    this->m_str = new char[this->m_length + 1];
    std::memset(this->m_str, 0, this->m_length + 1);
    std::memcpy(this->m_str, str, m_length);
}

StringBasic::StringBasic(char* str)
{
    this->m_length = (unsigned)std::strlen(str);
    this->m_str = str;
}


StringBasic::StringBasic() : StringBasic("")
{
}

unsigned StringBasic::getLength()
{
    return this->m_length;
}

char* StringBasic::getStr()
{
    return this->m_str;
}

StringBasic::~StringBasic()
{
    delete this->m_str;
}