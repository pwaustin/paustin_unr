using namespace std;

int strLen ( const char* targetArrayLocation ) 
{

	//declare variables	

	int index = 0;
	
	//starting from location 0 of the array being pointed at, count until you hit null char

	while ( targetArrayLocation[index] != '\0' )
		{

		index++;
	
		}
	
	//return the count

	return index;

}

void strCat ( char* destArrayLocation, const char* srcArrayLocation )
{
	
	//declare variables

	int index = strLen( destArrayLocation );
	int srcIndex = 0;

	//put a space at the end and increment the location

	destArrayLocation[index] = ' ';
	index++;

	//until you reach null char in the second array, copy its values onto the end of the first array

	while ( srcArrayLocation[srcIndex] != '\0' )
		{
		
		destArrayLocation[index] = srcArrayLocation[srcIndex] ;
		index++;
		srcIndex++;
	
		}

	//re-add null char to the end of the combined array
	
	destArrayLocation[index] = '\0';

}

void strCopy ( char* destArrayLocation, const char* srcArrayLocation )
{

	//initialize variables

	int index = 0;

	//copy values from source into dest until you hit null char

	while ( srcArrayLocation[index] != '\0' )
		{
	
		destArrayLocation[index] = srcArrayLocation[index];
		index++;

		}

	//re-add null char to the end of the dest array

	destArrayLocation[index] = '\0' ;

}

bool strCmp ( const char* first, const char* second )
{

	//initialize variables

	int index = 0;

	//check that the strings are identical, character by character

	while ( first[index] == second[index] )
		{

		//if they are identical up to and including the null char, return true

		if ( (first[index] == '\0') && (second[index] == '\0') )
			{

			return true;			

			}

		index++;

		}

	//if they are not identical, return false

	return false;

}
