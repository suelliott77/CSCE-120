#include <iostream>
#include <string>
#include "./string_calculator.h"

using std::cout, std::endl;
using std::string;

unsigned int digit_to_decimal(char digit) {
    if (digit >= '0' && digit <= '9') {         
        return (digit - '0');     
    }     
    else {         
        throw std::invalid_argument("Invalid argument");     
    }      
    return 0;
}

char decimal_to_digit(unsigned int decimal) {
    switch (decimal) {     
        case 0:         
            return '0';      
        case 1:         
            return '1';      
        case 2:         
            return '2';      
        case 3:         
            return '3';      
        case 4:         
            return '4';      
        case 5:         
            return '5';      
        case 6:         
            return '6';      
        case 7:         
            return '7';     
        case 8:         
            return '8';     
        case 9:         
            return '9';      
        default:         
            throw std::invalid_argument("Invalid argument");         
            break;     
    }      
    return '\0'; 
}


string trim_leading_zeros(string num) {
    bool zero_num = true;
    int index_num = 0;
    //Checking all zero number
    if (num.at(0) == '-') {
        num = num.substr(1,num.length());index_num = 1;
    }
    //Checking zero string
    for (string::size_type i = 0; i <= (num.size()-1); ++i){
        if ((num.at(i)) != '0') {
            zero_num = false;
            break;
        }
    }
    if (zero_num == true) {
        num = "0";
        return num;
    }
    //Main function trimming zero
    for ( string::size_type i = 0; i <= (num.size()); ++i) {
        if (num.at(i) == '0') {
            num.replace(i,1,"*");
        }
        else {
            num = num.substr(i,num.size());
            if (index_num == 1) {
                num.insert(0,"-");
                //add '-' for negative number
            }
        return num;
        }
    }
    return num;
}

string add(string lhs, string rhs) {
    // trim leadings 0's
    lhs = trim_leading_zeros(lhs);
    rhs = trim_leading_zeros(rhs);

    int num1 = 0;
    int num2 = 0;
    string answer = "";

    int counter1 = lhs.length() - 1;
    int counter2 = rhs.length() - 1;

    // carry variable is for the addition if it is bigger than 10 
    int carry = 0;
    int currentNum = 0;

    // addition loop 
    while(true) {
        if(counter1 >= 0) {
            num1 = digit_to_decimal(lhs[counter1]);
            counter1--;
        }
        else {
            num1 = 0;
        }

        if (counter2 >= 0) {
            num2 = digit_to_decimal(rhs[counter2]);
            counter2--;
        }
        else {
            num2 = 0;
        }
        
        //doing the math 
        currentNum = num1 + num2 + carry;
        carry = currentNum / 10;
        currentNum = currentNum % 10;

        // convert int to string 
        answer.insert(answer.begin(), decimal_to_digit(currentNum));

        // checks if both numbers have been fully used in the addition process
        if(counter1 == -1 && counter2 == -1){
            if(carry == 1) {
                answer.insert(answer.begin(), '1');
            }
            break;
        }
    }

    return answer;

}

string multiply(string lhs, string rhs) {
    // TODO(student): implement
    string copy_lhs = lhs;
    string copy_rhs = rhs; 
    //eliminate 0
    lhs = trim_leading_zeros(lhs);
    rhs = trim_leading_zeros(rhs);

    string temp_result = "";
    string multi_result = "0";
    int carry = 0;
    int result = 0;
    int number = 0;

    if (lhs.at(0) == '-') {
        lhs = lhs.substr(1,lhs.length());
    }
    if (rhs.at(0) == '-') {
        rhs = rhs.substr(1,rhs.length());
    }

    for ( int i = rhs.length()-1; i >= 0; --i) {
        for ( int j = lhs.length()-1; j >= 0; --j) {
            result = digit_to_decimal(lhs.at(j)) * digit_to_decimal(rhs.at(i)) +carry;
            carry = 0;
        
            if (result > 9) {
                temp_result.insert(0,string(1,decimal_to_digit(result % 10)));
                carry =result / 10;
            }
            else {
                temp_result.insert(0,string(1,decimal_to_digit(result)));
            }
            result = 0;
            }
            if (carry != 0) {
                temp_result.insert(0,string(1,decimal_to_digit(carry)));
                carry = 0;
            }
            for (int k = 0; k < number; ++k) {
                temp_result.append("0");
            }
            number ++;
            multi_result = add(multi_result,temp_result);
            temp_result = "";
        }
        if ((copy_lhs.at(0) == '-') ^ (copy_rhs.at(0) == '-')) {
            multi_result.insert(0,"-");
        }

    return multi_result;
    }

