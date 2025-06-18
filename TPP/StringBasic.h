#pragma once

class StringBasic
{
  public:
    StringBasic();
    StringBasic(const char str[]);
    StringBasic(const StringBasic& str);
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

    /*
    * Compares between this StringBasic object and the given one.
    * 
    * @param str [IN] The StringBasic object to compare with.
    * @return negetive if this is smaller, 0 if equal and positive if bigger.
    */
    int compare(const StringBasic& str) const;

    /*
    * Compares between this StringBasic object and a given string.
    *
    * @param str [IN] The string to compare with.
    * @return negetive if this is smaller, 0 if equal and positive if bigger.
    */
    int compare(const char str[]) const;

    /*
    * Compares between this StringBasic object and a given string.
    *
    * @param str [IN] The string to compare with.
    * @return negetive if this is smaller, 0 if equal and positive if bigger.
    */
    int compare(char* str) const;

    /*
    * Appends the given str to this str.
    * 
    * @param str [IN] The str to append to this str.
    */
    void append(const StringBasic& str);

    
    /*
     * Appends the given str to this str.
     *
     * @param str [IN] The str to append to this str.
     */
    void append(const char* str);
    
    /*
    * Replaces the first occurence of the given char with another char.
    * 
    * @param oldC [IN] The char to find and replace.
    * @param newC [IN] The char to replace with.
    * @return The index of the swapping.
    */
    unsigned replace(char oldC, char newC);

    /*
    * Returns a bool indicating if its an empty string or not.
    * 
    * @return true if the string is empty and false if its not.
    */
    bool isEmpty() const;

    /*
    * The char in the given index.
    * 
    * @return the char in the given index.
    */
    char& operator[](std::size_t i);

  private:
    char* m_str;
    int m_length;
};