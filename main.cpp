/******************************************************************************

File: main.cpp
Author: Prof. Lupoli & Andrew Nemec
Date: 2/16/2021
Section: 
E-mail: slupoli@tamu.edu
Description:
This file contains C++  code that will simulate data collected from a track 
event with 9 lanes. The code will sort the order, then display the results

Updates
Author: J. Michael Moore & Paul Taele
Author: J. Michael Moore

Input information format
<Time (double)> <Abbreviated Country (String)> <Uniform number (int)> <Lastname (String)>
32.7 USA 12 Moore
36.5 RUS 35 Polsley
45.8 ENG 73 Teale
52.34 CHN 14 Nemec
76.45 ITY 23 Lupoli     

*******************************************************************************/

#include <iostream>
#include <cstring>
#include "parallel_tracks.h"

using std::cin; using std::cout; using std::endl;

int main()
{
    double times[9];
    char names[9][STRING_SIZE];
    char countries[9][STRING_SIZE];
    unsigned int number[9];
    unsigned int rankings[9];

    prep_double_array(times);
    prep_unsigned_int_array(number);
    prep_string_array(names);
    prep_string_array(countries);

    if (!get_runner_data(times, countries, number, names)) {
        cout << "Bad input";
        return 1;
    }

    get_ranking(times, rankings);

    print_results(times, countries, names, rankings);
    
    return 0; 
}

