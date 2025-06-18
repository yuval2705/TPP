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

    /*
    * Return the current value of m_length.
    * 
    * @return The current value of m_length.
    */
    unsigned getLength() const;

    /*
     * Return the current value of m_str.
     *
     * @return The current value of m_str.
     */
    char* getStr() const;

    //No need for setters!

  private:
    char* m_str;
    int m_length;
};