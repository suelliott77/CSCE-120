#include "functions.h"
#include <iostream>
#include <string>
using namespace std;

using std::cout, std::cin, std::endl, std::string;

void deobfuscate() {
    char string[100];
    char length[50];
    cout << "Please enter obfuscated sentence: ";
    cin >> string;
    cout << "Please enter deobfuscation details: ";
    cin >> length;
    cout << "Deobfuscated sentence: ";

    int counter = 0;

    for (int i = 0; length[i] != '\0'; i++) {
        char ch = length[i];
        int number= (int)(ch) - 48;

        for (int j = 0; j < number; j++) {
            cout << string[counter + j];
        }
        cout << " ";
        counter += number;
    }
    cout << endl;
}

void wordFilter() {
    // TODO
}

void passwordConverter() {

    string user_password, new_password;     
    char ch, temp;          
    cout << "Please enter your text input: ";     
    cin >> user_password;            
    int size = user_password.length();          
    for(int i=0; i<size; i++) {         
        ch = user_password[i];                  
        switch(ch) {             
            case 'a':                 
            temp = '@';                 
            break;             
            case 'e':                 
            temp = '3';                 
            break;             
            case 'i':                 
            temp = '!';                 
            break;             
            case 'o':                 
            temp = '0';                
            break;             
            case 'u':                 
            temp = '^';                 
            break;             
            default:                 
            temp = ch;         
        }                  
        new_password += temp;     
    }          
    string reversed_string = string(new_password.rbegin(),new_password.rend());          
    new_password.append(reversed_string);          
    cout << "input: " << user_password << endl;           
    cout << "output: " << new_password << endl;          

} 


void wordCalculator() {
    std::string math;
    cin >> math;
    long unsigned int i;

    for (i = 0; i < math.length(); i++) {
        cout << " ";
    }

}

void palindromeCounter() {
    // TODO
}