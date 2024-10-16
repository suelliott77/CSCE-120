#include <iostream>
#include "functions.h"

using std::cout, std::endl;

bool is_valid_range(int a, int b) {
	if(a <= b && a >= 10 && b < 10000) {        
		return true;  
	   }   
	return false;
}

char classify_mv_range_type(int number) {
	//
	int x = number, count = 0, y;     
	// counting total digts of the number     
	while(x > 0) {         
		x/=10;         
		count++;     
	}          
	// finding p which is the quotient initially     
	// in power of 10 to find the digits of the     
	// number from starting     
	int p = 1;     
	for(int i = 1 ;i < count; i++) {     
		p *= 10;       
	}   
		// m and v defines if it is a mountain or valley     
		// inc and dec are increment and decrement     
		// which tells if digits are increasing or decreasing     
	int inc = 0, dec = 0, m = 0, v = 0;     
	// finding the first digit of the number     
	x = number / p;     
	number = number % p;     
	p /= 10;       
	// loop to check further       
	while(p > 0) {            
		// next digit of the number              
		y = number/p;         
		// if next and previous digit are equal return N         
		if(y == x) {             
		return 'N'; 
		}        
		// finding if a mountain is there or valley initially         
		if(m == 0 && v == 0) {                         
			if(y > x) {                 
				m = 1; 
			}            
			else {             
				v = 1;  
			}           
		}         
		// incrementing if next number is greater         
		if(y > x) {
			inc++;             
			dec = 0;        
		}         
		// decrementing if next number is greater         
		else {
			dec++;             
			inc = 0;         
		}         
		// if there is more than 1 continouous increment         
		// or decrement of digits return N         
		if(inc > 1 || dec > 1) {      
			return 'N';
		}         
		// making the previous digit equal to next         
		x = y;         
		number = number % p;         
		p/=10;     }              
		// if m is 1 it is mountain     
		if(m == 1) {
			return 'M'; 
		}    
		// else it is valley     
		else {         
			return 'V'; 
			}
}

void count_valid_mv_numbers(int a, int b) {
	int mountains = 0, valleys = 0;     
	for(int i = a; i <= b ;i++) {         
		char c = classify_mv_range_type(i);         
		if(c == 'M') {           
		mountains++; 
	    }        
		else if(c == 'V') {       
		valleys++;
	    }     
	}  
	cout << "There are " << mountains << " mountain ranges and " << valleys << " valley ranges between " << a << " and " << b << "." << endl; 
}
