// TODO: Implement this header file
#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
using std::ostream;

class MyString {
    private:
        size_t capacityPriv;
        size_t sizePriv;
        char* cString;
        friend ostream& operator<<(ostream& os,const MyString& str);
        friend bool operator== (const MyString& lhs, const MyString& rhs);
        friend MyString operator+ (const MyString& lhs, const MyString& rhs);
    public:
        MyString();
        MyString(const char* object);
        MyString(MyString& other);
        MyString& operator=(MyString& object);
        MyString& operator+=( MyString& other);
        //MyString operator+ (const MyString& lhs, const MyString& rhs);
        //bool operator== (const MyString& lhs, const MyString& rhs);
        //ostream& operator<<(ostream& os,const MyString& str);
        size_t size()const ;
        size_t length() const;
        size_t capacity() const;
        char& at(size_t pos) const;
        char& front() const;
        bool empty();
        void clear();
        void resize (size_t n);
        char* data() const;
        size_t find (const MyString& val, size_t pos = 0) const noexcept;
        ~MyString();
    };
    
    #endif