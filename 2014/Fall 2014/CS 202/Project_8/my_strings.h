//function specifications

        /**************************************************************/

        /* FUNCTION: strLen                                                                  */

        /*                                                                                      */

        /* PURPOSE: returns length of c-string being pointed at as an int.

        /*                                                                                      */

        /**************************************************************/

	int strLen ( const char* targetArrayLocation );

        /**************************************************************/

        /* FUNCTION: strCat                                                               */

        /*                                                                                      */

        /* PURPOSE: appends the c-string pointed at by the source pointer to the string pointed at by
		the dest pointer, with a space in-between. Uses strLen.

        /*                                                                                      */

        /**************************************************************/

	void strCat ( char* destArrayLocation, const char* srcArrayLocation );

        /**************************************************************/

        /* FUNCTION: strCopy                                                                 */

        /*                                                                                      */

        /* PURPOSE: copies the c-string pointed at by source pointer into the c-string pointed at by
		the dest pointer.

        /*                                                                                      */

        /**************************************************************/

	void strCopy ( char* destArrayLocation, const char* srcArrayLocation );

        /**************************************************************/

        /* FUNCTION: strCmp                                                              */

        /*                                                                                      */

        /* PURPOSE: compares two strings to see if they are identical. Returns true if they are the same,
		and false if they are not the same.

        /*                                                                                      */

        /**************************************************************/

	bool strCmp ( const char* first, const char* second );
