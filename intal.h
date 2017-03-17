//intal.h is an header for the library of integers of arbitrary length.
//intal stands for "int"eger of "a"rbitrary "l"ength.

#include <stddef.h>

// intal is an integer of arbitrary length.
// Field s stores a null-terminated string of decimal digits preceded by
// a + or sign indicating positive and negative integers.
// Field n represents the number of decimal digits excluding the sign.
// n is always greater than zero.
// Eg: Zero is represented with s as "+0" and n == 1.
// Eg: 2017 is represented with s as "+2017" and n == 4.
// Eg: -272 is represented with s as "-272" and n == 3.
typedef struct intal {
	char *s; //null terminated string of decimal digits preceded by a +/- sign
	int n; //length of the integer in terms of decimal digits
} intal;

// Creates and returns a pointer to a new intal initialized to zero.
// Initial values of i would be "+0" and n == 1.
intal* create_intal();

// Deletes an intal, especially the memory allocated to it.
// i is a pointer to an intal to be deleted. It also resets *i to null.
void delete_intal(intal** i);

//removes leading zeros from a given number
intal* remove_leading_zeros(intal *num);

// Reads an intal from str into intal struct.
// str should be a null-terminated string just like s inside intal except that
// a postive integer could start without a + sign.
void read_intal(intal* i, char* str);

// Prints the integer into stdout.
// It's just printf of s in intal (with format specifier %s) except that 
// it doesn't print the sign in case of positive integer.
void print_intal(intal* i);

// Adds two intals a and b, and returns the sum.
// Parameters a and b are not modified. Sum is a new intal.
intal* add_intal(intal* a, intal* b);

// Subtracts intal b from intal a. That is, finds a-b and returns the answer.
// Parameters a and b are not modified. a-b is a new intal.
intal* subtract_intal(intal* a, intal* b);

// Multiplys two intals a and b, and returns the product.
// Parameters a and b are not modified. Product is a new intal.
intal* multiply_intal(intal* a, intal* b);

// Divides intal a from intal b and returns the quotient. 
// That is, finds floor(a/b), which is aka integer division.
// Parameters a and b are not modified. Floor(a/b) is a new intal.
// The following division algorithm reduces the number of subtractions and is hence faster than the traditional repeated subrtractions.
intal* divide_intal(intal* a, intal* b);

// Finds a^b, which a to the power of b and returns the result. 
// The result could be undefined if the intal b is negative.
// Parameters a and b are not modified. The result is a new intal.
intal* pow_intal(intal* a, intal* b);

//Pads the given array a with leading zeros upto the length 'num'
//Example : padding array containing +2 where num = 4 gives, +0002.
//a is not modified and the padded array is a new intal
intal* padarray(intal* a, int num);

//Multiplies the given intal a by 10^exp
//a is not modified a*10^exp is a new intal
intal* multiply_byten(intal *a, int exp);

//compares 2 intals a1 and b1. Returns -1 if a1 < b1, +1 if a1 > b1 and 0 if a1 == b1
//parameters are not modified
int compare_intal(intal a1, intal b1);

//Creates a deep copy of the intal
//Parameter a is not modified while a1 is modified and returned
intal deep_copy(intal a1, intal *a);
