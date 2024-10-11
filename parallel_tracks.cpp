#include <iostream>
#include <iomanip>
#include <cstring>
#include "parallel_tracks.h"

using std::cin, std::cout, std::endl;

//-------------------------------------------------------
// Name: prep_double_array
// PreCondition:  an array of doubles is passed in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_double_array(double ary[])
// making sure all values within the array are set to 0.0;
{
	for (int i = 0; i < 9; i++){ 		
		ary[i] = 0.0; 	
		} 
}

//-------------------------------------------------------
// Name: prep_unsigned_int_array
// PreCondition:  an array of unsigned ints is passed in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_unsigned_int_array(unsigned int ary[])
// making sure all values within the array are set to 0;
{
  for (int i = 0; i < 9; i++) {
  	ary[i] = 0; 	
	}
}

//-------------------------------------------------------
// Name: prep_string_array
// PreCondition:  an array of strings is passed in
// PostCondition: each element in the array is set to "N/A"
//---------------------------------------------------------
void prep_string_array(char ary[][STRING_SIZE])
{
	for (unsigned int i = 0; i < SIZE; ++i) {
		strcpy(ary[i], "N/A");
	}
}

//-------------------------------------------------------
// Name: trim
// PreCondition:  the cstring
// PostCondition: whitespace has been removed from beginning and end of string
//---------------------------------------------------------
void trim(char str[STRING_SIZE]) {
	int num1 = 0;
	int num2 = 0;
	int counter = 0;
	bool checker = true;
	while ((str[num1] == 32) || (str[num1] == '\t')) {
		// TEST CODE: str[pos1] = 'A';
		num1++;
	}

	while(checker) {
		num2++;
		if (str[num2] =='\0') {
			checker = false;
		}
	}

	num2--;
	while((str[num2] == 32) || (str[num2] == '\t')) {
		//MORE TEST CODE: str[pos2] = 'A';
		num2--;
	}

	while (num1 <= num2) {
		str[counter] = str[num1];
		counter++;
		num1++;
	}
	str[counter] = 0;
}

//-------------------------------------------------------
// Name: get_runner_data
// PreCondition:  the prepped parallel arrays
// PostCondition: all arrays contain data from standard in
//---------------------------------------------------------
bool get_runner_data(double timeArray[], char countryArray[][STRING_SIZE], 
		unsigned int numberArray[], char lastnameArray[][STRING_SIZE]) 
{
  int counter;
  bool check = true;

  for (unsigned int i=0; i < SIZE; ++i) {
	// checks the time to make sure it is valid 
	cin >> timeArray[i];
	if (timeArray[i] <= 0) {
		return false;
	}

	// checks the country to make sure it is uppercase and only three letters 
	cin >> countryArray[i];
	if (strlen(countryArray[i]) != 3) {
		return false;
	}
	for (int j = 0; j < 3; j++) {
			if (!isupper(countryArray[i][j])){
				return false;
			}
		}

	// checks the number is only 1 or 2 digits 
	cin >> numberArray[i];
	if ((numberArray[i] > 99)) {
		return false;
	}

	// checks the name to make sure it is valid
	cin >> lastnameArray[i];
	trim(lastnameArray[i]);

	counter = 0;
	if (strlen(lastnameArray[i]) <= 1) {
		return false;
	}
	check = true;
	while(check) {
		if (!(isalpha(lastnameArray[i][counter])) && !(isspace(lastnameArray[i][counter]))) {
			return false;
		}
		counter++;
		if (lastnameArray[i][counter] == '\0') {
			check = false;
		}
	}
	}
  return true;
}

//-------------------------------------------------------
// Name: get_ranking
// PreCondition:  just the time array is passed in, and has valid data
// PostCondition: after a very inefficient nested loop to determine the placements 
// and places the ranks in a new array. That new array is returned
//---------------------------------------------------------
void get_ranking(const double timeArray[], unsigned int rankArray[]) {
	int i;
	int rank = 1;
	for (i = 0; i < (int) SIZE;  i++) {
		rank = 1;
		int j;
		for (j = 0; j < (int) SIZE; j++) {
			if (timeArray[i] > timeArray[j]) {
				rank++;
			}
		}

		rankArray[i] = rank;
	}

}


//-------------------------------------------------------
// Name: print_results
// PreCondition:  all parallel arrays are passed in and have valid data
// PostCondition: after a very inefficient nested loop to determine the ranks
// it then displays them along with a delta in time from the start
//---------------------------------------------------------
void print_results(const double timeArray[], const char countryArray[][STRING_SIZE],
		const char lastnameArray[][STRING_SIZE], const unsigned int rankArray[])
{

	std::cout << "Final results!!";
	std::cout << std::setprecision(2) << std::showpoint << std::fixed << std::endl;
	double best_time = 0.0;
		
	// print the results, based on rank, but measure the time difference_type
	for(unsigned int j = 1; j <= SIZE; j++)
	{
		
		// go thru each array, find who places in "i" spot
		for(unsigned int i = 0; i < SIZE; i++)
		{
			if(rankArray[i] == 1) // has to be a better way, but need the starting time
			{
				best_time = timeArray[i];
			}
			
			
			if(rankArray[i] == j) // then display this person's data
			{
				// this needs precision display
				std::cout << "[" << j << "]  " << timeArray[i] << " " << std::setw(15) << std::left << lastnameArray[i] << "\t" << "(" << countryArray[i] << ")  +" << (timeArray[i] - best_time) << std::endl; 
			}
			
		}
	}	
}

 