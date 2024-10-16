// TODO: Implement this source file
#include "MyString.h"
#include <iostream>
using std::ostream, std::iostream;
MyString::MyString(): capacityPriv(1), sizePriv(0), cString(new char[1]{'\0'}){}
MyString::MyString(const char* object): capacityPriv(1), sizePriv(0), cString(new char[1]{'\0'}){
    size_t n = 0;
    while(object[n]) {
        n++;
    }
    resize(n);
    delete[] cString;
    cString = new char[n+1];
    for (size_t i = 0; i <= n; ++i) {
        cString[i] = object[i];
    }
    //delete[] object;
}

MyString::MyString(MyString& other): capacityPriv(1), sizePriv(0), cString(new char[1]{'\0'}) {
    delete[] cString;
    cString = new char[other.capacity()];
    sizePriv = other.length();
    capacityPriv = other.capacity();
    for (size_t i = 0; i <= other.length(); ++i) {
        cString[i] = other.cString[i];
    }
}

MyString& MyString::operator=(MyString& other) {
    if (this != &other) {
        delete[] cString;
        cString = new char[other.capacity()];
        sizePriv = other.length();
        capacityPriv = other.capacity();
        for (size_t i = 0; i <= other.length(); ++i) {
            cString[i] = other.cString[i];
        }
    }
    return *this;
}

MyString& MyString::operator+=(MyString& other) {
    size_t val = capacityPriv + other.capacity() - 1;
    char* newArray = new char[val];
    for (size_t i = 0; i < sizePriv; i++) {
        newArray[i] = cString[i];
    }
    for (size_t i = sizePriv; i < val; i++) {
        newArray[i] = other.data()[i - sizePriv];
    }
    delete[] cString;
    resize(val-1);
    cString = new char[val];
    for (size_t i = 0; i < val; i++) {
        cString[i] = newArray[i];
    }
    //delete[] other.data();
    delete[] newArray;
    return *this;
}

bool operator==(const MyString& lhs, const MyString& rhs) {
    if (lhs.length() != rhs.length() || lhs.capacity() != rhs.capacity()) {
        return false;
    }
    else { 
        for (size_t i = 0; i < lhs.capacity(); i++) {
            if (lhs.data()[i] != rhs.data()[i]) {
                return false;
            }
        }
    }
    //delete[] lhs.data();
    //delete[] rhs.data();
    return true;
}

MyString operator+ (const MyString& lhs, const MyString& rhs) {
    size_t val = lhs.capacity() + rhs.capacity() -1;
    char* newArray = new char[val];
    for (size_t i = 0; i < lhs.length(); i++) {
        newArray[i] = lhs.data()[i]; 
    }
    for (size_t i = lhs.length(); i < val; i++) {
        newArray[i] = rhs.data()[i - lhs.length()];
    }
    //delete[] lhs.data();
    //delete[] rhs.data();
    return newArray;
    delete[] newArray;
}

size_t MyString::size() const{ return sizePriv;}
size_t MyString::length() const{return sizePriv;}
size_t MyString::capacity() const{return capacityPriv;}

char& MyString::at(size_t pos) const{
    if (pos >= sizePriv || sizePriv == 0) {
        throw std::out_of_range("Size if out of range");
    }
    return cString[pos];
}

char& MyString::front() const{
    if (capacityPriv == 0) {
        throw std::out_of_range("Size is out of range"); 
    }
    return cString[0];
}

bool MyString::empty() {
    if (cString[0] != '\0') {
        return false;
    }
    return true;
}

void MyString::clear() {
    delete[] cString;
    sizePriv = 0;
    capacityPriv = 1;
    cString = new char[1]{'\0'};
}

void MyString::resize (size_t n){sizePriv = n; capacityPriv = n+1;}

char* MyString::data() const{
    char* newArray = new char [capacityPriv];
    for (size_t i = 0; i <= sizePriv; i++) {
        newArray[i] = cString[i];
    }
    //delete[] cString;
    //cString = new char[1]{'\0'};
    return newArray;
    delete[] newArray;
    delete[] cString;
}

size_t MyString::find (const MyString& val, size_t pos) const noexcept {
    size_t startIndex = -1;
    size_t index;size_t n = 1;
    for (size_t i = pos; i < capacityPriv; i++) {
        if (val.data()[0] == cString[i]) {
            startIndex = i;
            index = i+1;
            while(val.data()[n] != '\0') {
                if (val.data()[n] != cString[index]) {
                    startIndex = -1;
                    break;
                }
                n++;
                index++;
            }
        }
    }
    //delete[] val.data();
    return startIndex;
}

MyString::~MyString(){delete[] cString;}
ostream& operator<<(ostream& os,const MyString& str) {
    os << str.data();
    //delete[] str.data();
    return os;
}