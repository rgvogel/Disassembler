/*
 * binToDec
 *
 * This function converts the binary digits from string[begin] to
 * string[end] to a decimal integer.
 *
 * int binToDec(char string[], int begin, int end)
 *   Pre-condition:  begin and end are valid indices in array string;
 *   		     every character from string[begin] to string[end]
 *		     (including those two) has a character value '0' or '1'
 *   Returns: the decimal equivalent of the binary number represented by
 *	      the characters in string[begin] - string[end].
 *            (If begin > end, this function arbitrarily returns 0.)
 *
 * For example, assume A is a character array that contains the
 *    following characters:
 *            '1'  '0'  '1'  '1'  '0'  '1'  '0'  '0'  '1'
 *    The call binToDec(A, 2, 5) converts the binary number 1101
 *    (represented by the substring A[2] - A[5]) to the decimal integer
 *    13 and returns it.
 *
 * Note: The decimal value returned may appear to be negative if the
 * string being converted is long enough (end - begin + 1 == 32)
 * and if the first character is '1'.
 *
 * Implementation:
 *	This is implemented by going through each of the characters in the sub string from the begin section.
 *	and checking if it is  a 1. if it is a one it takes 2 to the power of the index of the binary number
 *	( the count represents what binary number it is at in the substring). It stores this value
 *	as temp and adds it to binary which stores the total of all previous values. at the end of the code
 *	it binary is returned which is the total value number in a 10 based system.
 * Author:  Roderick Vogel
 *
 * Creation Date:  4/7/16
 *
 *
 *
 */
#include <math.h>
long long binToDec(char string[], int begin, int end)
{
	long long decimal = 0; //
	long long p = 0; //the number that represents the start of the index of the binary number
	long long s = 2;//power of 2 to convert from binary
	long long temp;//value of a single digit in the binary code
	/*
	 * goes through each charter in the substring
	 */
	for( int i = end; i>=begin; i--)
	{
		/**
		 * finds the value of one of the binary characters and adds it to the previously
		 * collected values.
		 */
		if(string[i] =='1')
		{
			temp = powl( s, p);//puts it to the power based on the binary numbers index
			decimal = temp + decimal;//adds to total of previously collected values
		}
		p++;// add one to the index
	}

	return decimal; // returns the decimal which is the same value of the binary substring
}
