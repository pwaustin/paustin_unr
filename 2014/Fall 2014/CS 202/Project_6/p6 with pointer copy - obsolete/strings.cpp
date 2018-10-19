using namespace std;

int strLen ( char* targetArrayLocation )
{

	//declare variables	

	int index = 0;
	
	//starting from location 0 of the array being pointed at, count until you hit null char

	while ( *targetArrayLocation != '\0' )
		{
		
		targetArrayLocation++;

		index++;
	
		}
	
	//return the count

	return index;

}

void strCat ( char* destArrayLocation, char* srcArrayLocation )
{
	
	//declare variables

	int index;
	int destIndex = strLen ( destArrayLocation );

	//count to the end of the first string

	for ( index = 0 ; index < destIndex ; index++ )
		{

		destArrayLocation++;

		} 

	//put a space at the end and increment the location

	*destArrayLocation = ' ';
	destArrayLocation++;

	//until you reach null char in the second array, copy its values onto the end of the first array

	while ( *srcArrayLocation != '\0' )
		{
		
		*destArrayLocation = *srcArrayLocation ;
		destArrayLocation++;
		srcArrayLocation++;
	
		}

	//re-add null char to the end of the combined array
	
	*destArrayLocation = '\0';

}

void strCopy ( char* destArrayLocation, char* srcArrayLocation )
{

	//copy values from source into dest until you hit null char

	while ( *srcArrayLocation != '\0' )
		{
	
		*destArrayLocation = *srcArrayLocation;
		srcArrayLocation++;
		destArrayLocation++;

		}

	//re-add null char to the end of the dest array

	*destArrayLocation = '\0' ;

}

int strCmp ( char* first, char* second )
{

	//loop through both strings until one or both of them hit null char

	while ( *first != '\0' && *second != '\0' )
		{
	
		first++;
		second++;

		}

	//if they both hit null char, they are of equal length - return 0

	if ( first == second )
		{
	
		return 0;

		}

	//if only the first one hit null char, then the second one is longer - return 2

	if ( first == '\0' )
		{
	
		return 2;

		}

	//otherwise, the first one is longer - return 1

	else
		{
	
		return 1;

		}

}
