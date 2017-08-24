/*
 * verifyMIPSInstruction
 *
 * This function verifies that the string provided to it as a paramater
 * contains 32 characters representing binary digits (characters '0' and
 * '1'), followed by a null byte.  If the string contains the wrong
 * number of characters or contains invalid charaters (not '0' or '1'),
 * then the function prints an error message to stderr giving the line
 * number and an appropriate error message.
 *
 *   int verifyMIPSInstruction (int lineNum, char * instruction);
 *
 *	    Pre-condition:  instruction is a null-terminated string
 *	    Post-condition: the characters in "instruction" have not
 *			    been modified
 *	    Returns: 1 if instr contained 32 characters representing binary
 *			    digits ('0' and '1') followed by a null byte
 *		     0 if instr has the wrong number of characters or
 *		            contains invalid characters
 *	    Output: Prints an error message to stderr if necessary
 *
 * Implementation:
 *	Describe interesting implementation details here, if any.
 *     This works by grabbing a line in a a file and first making sure it has 32 characters. if it does not it returns
 *     an error. Then it checks to make sure every number is  a 0 or 1;
 *
 * Author: Roderick Vogel
 *	with assistance from:
 *
 *	modified: 4/7/16	Made it so that after it checks if it is the right length it checks to see if each character is either
 *	0 or 1. If there is an issue it prints out error the line number and the character that is wrong.
 *
 */

#include "pp1.h"
#include "string.h"
static const int INSTR_LENGTH = 32;

int verifyMIPSInstruction (int lineNum, char * instr)
  /*  returns 1 if instr contains INSTR_LENGTH characters representing binary
   *  digits ('0' and '1'); 0 otherwise
   */
{

    int   length;

    length = strlen (instr);
    /**
     * checks to see if string is the designated appropriate length (32).
     * If not prints an error
     */
    if (length != INSTR_LENGTH)
    {
        printError ("Error: line %d does not have %d chars.\n", lineNum, INSTR_LENGTH);
        return 0;
    }
    /**
     * runs through each character in string is either a 0 or 1
     * If not print error and name character
     */
    for( int i = 0; i<length; i++)
    {

    	if( instr[i] != '0' && instr[i] !='1')
    	{
    		printError ("Error: line %d has a a char that is not a 0 or 1. The char is:%c \n", lineNum, instr[i]);
    		return 0;
    	}
    }
    return 1;    /* when it returns run that means that the string is the right length and only composed
    of zeros and ones */
}
