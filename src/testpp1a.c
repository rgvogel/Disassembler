/*
 * Test Driver to test verifyMIPSInstruction and binToDec.
 *
 * This program reads lines from a file.  For each line, the program
 *      calls verifyMIPSInstruction.  If the line contains characters
 *      representing a valid MIPS instruction, the program calls
 *      binToDec for various segments of the instruction to test the
 *      binToDec function.
 *
 * Usage:
 *          basicTest [ filename ] [ 0|1 ]
 *      where "name" is the name of the executable, "filename" is an
 *      optional file containing the input to read, and " 0" or
 *      "1" specifies that debugging should be turned off or on,
 *      respectively, regardless of any calls to debug_on, debug_off,
 *      or debug_restore in the program.  Both arguments are optional;
 *      if both are present they may appear in either order.  If no
 *      filename is provided, the program reads its input from stdin.
 *      If no debugging choice is provided, the program prints debugging
 *      messages, or not, depending on indications in the code.
 *
 * Input:
 *      The program reads its input from a file passed in as a parameter
 *      on the command line, or reads from the standard input.
 *      To test verifyMIPSInstruction, the file should contain ...
 *
 *              DESCRIBE NECESSARY TEST CASES HERE
 *
 * Output:
 *      For each valid line, the program prints a series of decimal
 *      numbers to test binToDec, representing
 *
 *              DESCRIBE NECESSARY TEST CASES HERE
 *
 *      For each invalid line, the program prints an error message to
 *      stderr saying so.  (The program also prints an error message if
 *      it cannot open the file.)
 *
 * Author:  Roderick Vogel
 *modification:  4/7/16. Called verify MIPSInstructions, and runs test cases for this and binToDec
 * prints out results of tests.
 *
 */

/* include files go here */
#include "pp1.h"
const int SAME = 0;		/* useful for making strcmp readable */
                                /* e.g., if (strcmp (str1, str2) == SAME) */

static FILE * process_arguments(int argc, char * argv[]);

int main (int argc, char *argv[])
{
    FILE * fptr;               /* file pointer */
    char   buffer[BUFSIZ];     /* place to store line that is read in */
    int    length;             /* length of line read in */
    int    lineNum = 0;        /* keep track of input line numbers */
    debug_on();

    if(argc == 2)
    {
    	if((fptr = fopen(argv[1],"r")) == NULL)
    	{
    		fprintf(stderr, "error: cannot open file %s.\n", argv[1]);
    		return 1;
    	}
    }
    else
    		fptr = stdin;
    /* Can turn debugging on or off here (debug_on() or debug_off())
     * or on the command line (pass 1 for on; 0 for off).
     */

    /* Continuously read next line of input until EOF is encountered.
     * Each line should contain a valid MIPS machine language instruction
     * (represented as 32 character '0's and '1's) and newline.
     */
    while (fgets (buffer, BUFSIZ, fptr))   /* fgets returns NULL if EOF */
    {
        lineNum++;
        /* If the last character in the string is a newline, "remove" it
         * by replacing it with a null byte.
         */
        length = strlen(buffer);
        if (buffer[length - 1] == '\n')
            buffer[--length] = '\0';      /* remove; pre-decrement length */
        printf ("\nLine %d: %s\n", lineNum, buffer);
        printDebug ("Length: %d\n", length);

        /* Verify that the string contains 32 '0' and '1' characters.  If
         * it does, do various tests to ensure that binToDec works correctly.
         * If the string is invalid, verifyMIPSinstruction should print
         * an informative error message.
         * tested if it is an empty line( prints error. Tested if there is characters that are not
         * 0 or 1 in either the begining or end or whole thing. gave an error. Tested if there is more then
         * 32 lines prints out an error.
         */

        if( verifyMIPSInstruction(lineNum,  buffer)== 1)
        {

       /* printf("\t bits 3..7: %.5s = %d (decimal)\n",
                  &buffer[3], binToDec(buffer, 3, 7));
        printf("\t bits 1..1: %.1s = %d (decimal)\n",
                         &buffer[1], binToDec(buffer, 1, 1));//test for when there is only one unit being measured
        printf("\t bits 0..0: %.1s = %d (decimal)\n",
                         &buffer[0], binToDec(buffer, 0, 0));//test for if it is just the begining unit
        printf("\t bits 1..32: %.32s = %d (decimal)\n",//test for whole binary code (seems to keep giving me a negative number.
                         &buffer[0], binToDec(buffer, 0, length));
        printf("\t bits 0..45: %.45s = %d (decimal)\n", // test for if the range given is larger then the max
                         &buffer[0], binToDec(buffer, 0, 45));*/

        MIPStrans(buffer);
        }
    }

    /* End-of-file encountered; close the file. */
    fclose (fptr);
    return 0;
}

/*
 * The internal (static) process_arguments function parses the
 * command-line arguments for an optional filename and an optional
 * choice (1 or 0) to turn all debugging messages on or off.  It returns
 * a FILE pointer to an open file (stdin if no filename was passed in)
 * or NULL if process_arguments encounters a fatal error.
 *
 * Usage:
 *      programName  [filename] [0|1]
 * If both a filename and a debugging choice are provided, they may
 * be in either order.
 *
 * The optional filename indicates the input file; if it is provided,
 * process_arguments opens the file and returns it after also processing
 * the debugging option.  If it is not provided, the program reads its
 * input from stdin.
 *
 * A debugging choice argument of 0 or 1 indicates a choice to globally
 * turn debugging off or on, overriding any calls to debug_on,
 * debug_off, and debug_restore in the code.  0 means that no debugging
 * messages should be printed, 1 means that all debugging messages
 * should be printed.  If no debugging choice is specified, the
 * debug_print function will either print or not print messages
 * depending on the current debugging state set by the debug_on,
 * debug_off, and debug_restore functions.
 */
static FILE * process_arguments(int argc, char * argv[])
{
    FILE * fptr;               /* file pointer */

    /* Implementation notes:
     * The arguments are both optional and may be provided in either
     * order, which makes the logic more complicated.  This function
     * processes the debugging choice first, if one was specified, then
     * "erases" it from the argument list so that when we come to process
     * the filename we can assume that it is the first and only argument
     * (if provided at all).  If two arguments are provided but neither
     * is a debugging choice, or if more than two arguments are provided,
     * then a usage error message is printed.
     * The valid combinations are:
     *   program               no arguments are provided
     *   program 0|1           process debugging choice and decrement
     *                         argc so it looks like there were no arguments
     *   program filename      no debugging choice; process filename
     *   program 0|1 filename  process debugging choice and shift
     *                         filename into first argument; now it looks
     *                         like there was just one argument, filename
     *   program filename 0|1  process debugging choice and decrement
     *                         argc; now it looks like there was just
     *                         one argument, filename
     */

    /* Process debugging choice and then "erase" this argument by
     * shifting the filename into its place or just by reducing the
     * argument count, argc, whichever is appropriate (see above for details).
     */
    if ( argc > 1 )
    {
        if ( strcmp(argv[1], "0") == SAME )
        {
            debug_off();  override_debug_changes();
            /* Done processing; move filename down (if it's there). */
            argv[1] = argc > 2 ? argv[2] : argv[1];
            argc--;
        }
        else if ( strcmp(argv[1], "1") == SAME )
        {
            debug_on();  override_debug_changes();
            /* Done processing; move filename down (if it's there). */
            argv[1] = argc > 2 ? argv[2] : argv[1];
            argc--;
        }
        else if ( argc > 2 && strcmp(argv[2], "0") == SAME )
        {
            debug_off();  override_debug_changes();
            argc--;
        }
        else if ( argc > 2 && strcmp(argv[2], "1") == SAME )
        {
            debug_on();  override_debug_changes();
            argc--;
        }
    }

    /* At this point, we have handled/erased the debugging choice, so
     * argc should be 0 or 1, depending on whether a filename was
     * provided.  Check the argument count now, since there's no need to
     * open the file if the argument count is wrong.
     */
    if ( argc > 2 )
    {
        printError("Usage:  %s [filename] [0|1]\n", argv[0]);
        return 0;
    }

    /* Process the filename, if one was passed in. */
    if ( argc > 1 )
    {
        /* Open the file for reading */
        if ((fptr = fopen (argv[1], "r")) == NULL)
        {
            printError("Error: Cannot open file %s.\n", argv[1]);
            return NULL;
        }
    }
    else  /* No file passed in; use standard input. */
        fptr = stdin;

    return fptr;   /* Everything was OK! */
}
