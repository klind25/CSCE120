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
#include "rank_functions.h"

using std::cin; using std::cout; using std::endl;

int main()
{
    // TODO: create arrays needed
	double racetime[SIZE];
    char country[SIZE][STRING_SIZE];
    unsigned int number[SIZE];
    char name[SIZE][STRING_SIZE];
    unsigned int rank[SIZE];

    // TODO: prep all arrays
	prep_double_array(racetime);
    prep_unsigned_int_array(number);
    prep_string_array(country);
    prep_string_array(name);
    prep_unsigned_int_array(rank);
    
    // TODO: load the driver's data into the array
    bool valid = get_driver_data(racetime, country, number, name); // Checks for bad input

    // if unable to load runner data
    if (!valid) {
        cout << "Bad input"; // Outputs
        return 1; // Returns 1
    }


    // TODO: determine ranking, notice the rank array receives the results
    set_rankings(racetime, rank);
    // TODO: Output results
    print_results(racetime, country, name, rank);
    // this is not required in C++ but many people still explitly add it
    return 0; 
}

