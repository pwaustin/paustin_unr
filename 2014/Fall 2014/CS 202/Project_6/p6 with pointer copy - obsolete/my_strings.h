//function specifications

        /**************************************************************/

        /* FUNCTION: strLen                                                                  */

        /*                                                                                      */

        /* PURPOSE: returns length of c-string being pointed at as an int.

        /*                                                                                      */

        /**************************************************************/

	int strLen ( char* targetArrayLocation );

        /**************************************************************/

        /* FUNCTION: strCat                                                               */

        /*                                                                                      */

        /* PURPOSE: appends the c-string pointed at by the source pointer to the string pointed at by
		the dest pointer, with a space in-between. Uses strLen.

        /*                                                                                      */

        /**************************************************************/

	void strCat ( char* destArrayLocation, char* srcArrayLocation );

        /**************************************************************/

        /* FUNCTION: strCopy                                                                 */

        /*                                                                                      */

        /* PURPOSE: copies the c-string pointed at by source pointer into the c-string pointed at by
		the dest pointer.

        /*                                                                                      */

        /**************************************************************/

	void strCopy ( char* destArrayLocation, char* srcArrayLocation );

        /**************************************************************/

        /* FUNCTION: strCmp                                                              */

        /*                                                                                      */

        /* PURPOSE: compares the lengths of the the strings passed as parameters. Returns 0 if the strings
		are of equal length, 1 if the first string is larger, and 2 if the second string is larger.

        /*                                                                                      */

        /**************************************************************/

	int strCmp ( char* first, char* second );
