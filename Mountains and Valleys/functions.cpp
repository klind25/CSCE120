#include <iostream>
#include "functions.h"

using std::cout, std::endl;

bool is_valid_range(int a, int b) {
	// TODO(student): validate input range
	bool valid = false;

	if ((a <= b) && (a >= 10) && (b < 10000)) {
		valid = true;
	}

	return valid;
}

char classify_mv_range_type(int number) {
	// TODO(student): return 'M' if number has /\/\... pattern,
	// return 'V' if number has \/\/ pattern, and return 'N' otherwise
	bool increase = false;
	bool decrease = false;
	int digit = 0;
	int digit2 = 0;

	while (number != 0) {
		// Number slicing
		digit = number % 10;
		number /= 10;
		digit2 = number % 10;

		if (digit2 < digit) {
			if (increase == true) {
				return 'N';
			}
			increase = true;
			decrease = false;
			if (number / 10 == 0) {
				return 'M';
			}
		} else if (digit2 > digit) {
			if (decrease == true) {
				return 'N';
			}
			increase = false;
			decrease = true;
			if (number / 10 == 0) {
				return 'V';
			}
		} else {return 'N';}
	}
	return 'N';
	
}

void count_valid_mv_numbers(int a, int b) {
	// TODO(student): count the number of valid mountain ranges and valley
	// ranges in the range [a, b] and print out to console using the format
	// in Requirement 4 of the homework prompt
	int i;
	int mountain_count = 0;
	int valley_count = 0;

	for (i = a; i <= b; ++i) {
		if (classify_mv_range_type(i) == 'V') {
			++valley_count;
		} else if (classify_mv_range_type(i) == 'M') {
			++mountain_count;
		}

	}
	
	cout << "There are " << mountain_count << " mountain ranges and " << valley_count << " valley ranges between " << a << " and " << b << "." << endl;

	return;
}