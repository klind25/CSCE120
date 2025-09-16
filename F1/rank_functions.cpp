#include <iostream>
#include <iomanip>
#include <cstring>
#include "rank_functions.h"

using std::cin, std::cout, std::endl;

//-------------------------------------------------------
// Name: prep_double_array
// PreCondition:  an array of doubles is passed in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_double_array(double ary[])
// making sure all values within the array are set to 0.0;
{
	unsigned int i;
	//TODO
	for (i = 0; i < SIZE; ++i) {
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
  	unsigned int i;
	//TODO
	for (i = 0; i < SIZE; ++i) {
		ary[i] = 0;
  	}
}

//-------------------------------------------------------
// Name: prep_string_array
// PreCondition:  an array of strings is passed in
// PostCondition: each element in the array is set to "N/A"
//---------------------------------------------------------
void prep_string_array(char ary[][STRING_SIZE])
// making sure all values within the array are set to "N/A";
{
	unsigned int i;
	//TODO
	for (i = 0; i < SIZE; ++i) {
		strcpy(ary[i], "N/A");
  	}
}

//-------------------------------------------------------
// Name: trim
// PreCondition:  the cstring
// PostCondition: whitespace has been removed from beginning and end of string
//---------------------------------------------------------
void trim(char str[STRING_SIZE]) {
	unsigned int i = 0;
	unsigned int temp_index = 0;
	unsigned int start_str = 0;
	unsigned int end_str = strlen(str);
	char temp_array[STRING_SIZE];
	bool blank = false;

	while (!isalpha(str[start_str])) { // Get where the string starts
		++start_str;
		if (start_str == strlen(str)) {
			blank = true;
			break;
		}
	}

	while (!isalpha(str[end_str])) { // Get where string ends
		--end_str;
		if (blank) {
			break;
		}
	}
	end_str += 1;
	for (i=start_str; i < end_str + 1; ++i) { // Iterate through not spaces + 1 for null
		temp_array[temp_index] = str[i];
		if (i == end_str) {
			temp_array[temp_index] = '\0'; // Including null terminator
		}
		++temp_index;
	}
	if (blank) {
		temp_array[0] = '\0';
	}
	strcpy(str, temp_array);
}


//-------------------------------------------------------
// Name: get_driver_data
// PreCondition:  the prepped parallel arrays
// PostCondition: all arrays contain data from standard in
//---------------------------------------------------------
bool get_driver_data(double timeArray[], char countryArray[][STRING_SIZE], 
		unsigned int numberArray[], char lastnameArray[][STRING_SIZE]) 
{
	unsigned int i;
	unsigned int j;

  //TODO
	for (i = 0; i < SIZE; ++i) {

		cin >> timeArray[i];
		if (timeArray[i] <= 0) {return false;} // Time validation

		cin >> countryArray[i];

		if (strlen(countryArray[i]) != 3) {return false;} // Country validation
		for (j=0; j < strlen(countryArray[i]); ++j) {
			if (!isupper(countryArray[i][j])) {return false;} 
		}

		cin >> numberArray[i];
		if (numberArray[i] >= 100) {return false;} // Number validation

		cin >> lastnameArray[i];
		trim(lastnameArray[i]); // Last name validation
		if (strlen(lastnameArray[i]) <= 1) {return false;} // Too short
		if (!isupper(lastnameArray[i][0])) {return false;} // Doesn't start with capital
		for (j = 0; j < strlen(lastnameArray[i]); ++j) {
			if (!isalpha(lastnameArray[i][j]) && !isspace(lastnameArray[i][j])) {return false;} // Not only spaces or letters
		}

	}
  return true; // set so it will compile
}

//-------------------------------------------------------
// Name: set_rankings
// PreCondition:  just the time array is passed in, and has valid data
// PostCondition: after a very inefficient nested loop to determine the placements 
// and places the ranks in a new array. That new array is returned
//---------------------------------------------------------
void set_rankings(const double timeArray[], unsigned int rankArray[])
{	
	unsigned int i;
	unsigned int j;
	unsigned int rank;

	//TODO
	for (i = 0; i < SIZE; ++i) { // Checks each person
		rank = 1; // Reinitialize each time
		for (j = 0; j < SIZE; ++j) {
			if (timeArray[i] > timeArray[j]) {
				++rank; // Increases rank if someone is slower than them
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