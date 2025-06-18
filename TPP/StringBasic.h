#pragma once

class StringBasic
{
  public:
    StringBasic();
    StringBasic(const char str[]);
    StringBasic(StringBasic& str);
    StringBasic(char chr);
    StringBasic(char* str);

    ~StringBasic();

    void append(StringBasic& str);
    void append(char chr);
    void append(char* str);

    unsigned getLength();
    char* getStr();

    //No need for setters!

  private:
    char* m_str;
    int m_length;
};