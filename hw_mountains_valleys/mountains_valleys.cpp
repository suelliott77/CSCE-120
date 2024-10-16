#include <iostream>
#include "functions.h"

using std::cout, std::cin, std::endl;

int main() {
	int a,b;     
	while(1) {         	    
		cout << "Enter numbers 10 <= a <= b < 10000: ";
	//getting the input 	   
	cin >> a >> b;     

	//checking the input 	    
	int i = is_valid_range(a,b); 	    
	if (i == 1) { 
		count_valid_mv_numbers(a, b);	       
		break;   
	}     
	//reprompting if input is not valid 	 
	while (i==0) {        
		cout << "Invalid Input" << endl; 
		cout << "Enter numbers 10 <= a <= b < 10000: ";
		cin >> a >> b;
		i = is_valid_range(a,b);
		}          
	count_valid_mv_numbers(a, b);
	
	return 0;
	}
}