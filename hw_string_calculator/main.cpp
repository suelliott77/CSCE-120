#include <iostream>
#include <string>
#include <limits>
#include "./string_calculator.h"

using std::cout, std::endl, std::cin;
using std::string;

int main() {
    cout << "String Calculator" << endl;
    cout << "\"q\" or \"quit\" or ctrl+d to exit" << endl;

    string rhs;
    string lhs;
    string operator_type;
    string ans;

    int loopcon = 0;
    while (loopcon == 0) {
        cin >> lhs;
        
        // if user inputs "quit" or "q"
        if (lhs == "quit" || lhs == "q") { 
            cout << ">>" << endl;
            cout << "farvel!" << endl;
            loopcon = 1;
        }

        else {
            cin >> operator_type;
            cin >> rhs;
            if (operator_type == "+") {
                ans = add(lhs, rhs);
            }
            else if (operator_type == "*") {
                ans = multiply(lhs, rhs);
            }
            else {
                throw std::invalid_argument("Argument is not valid");
            }
            cout << ">>" << endl;
            cout << "ans =" << endl;
            cout << endl;
            cout << "    " << ans << endl;
            cout << endl;
        }


    }
        
}

