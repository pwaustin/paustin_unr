

        /*****************************************************************************************/

        /* PROGRAM: project1.cpp (Card shuffle program - CS 202 Project 1 )

        /*                                                                                       */

        /* AUTHOR: Patrick Austin 

        /*                                                                                       */

        /* DATE: 4 September 2014

        /*                                                                                       */

        /* REVISIONS: N/A

        /*                                                                                       */

        /* PURPOSE: Reads a deck of cards from a data file. Can write the unshuffled deck to the
		    screen or output the shuffled deck into another data file.

        /*****************************************************************************************/



//Header Files

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

//Global Constants

const int SUITS_CAPACITY  = 4;
const int RANKS_CAPACITY  = 13;
const int STRING_CAPACITY = 14;
const int CARD_CAPACITY   = 52;

//Function Prototypes

        /**************************************************************/

        /* FUNCTION: strCat                                                                  */

        /*                                                                                      */

        /* PURPOSE: appends the contents of c-string srcTwo onto the end of srcOne, 
		replacing the null char at the end of srcOne with a space

        /*                                                                             

        /**************************************************************/

	void strCat ( char srcOne[], char srcTwo[] );

        /**************************************************************/

        /* FUNCTION: strCpyOne                                                              */

        /*                                                                                      */

        /* PURPOSE: conducts first string copy operation - copying a value from a
		temporary 1D array into the 3D array at the instructed location

        /*                                                                             

        /**************************************************************/

	void strCpyOne ( char src[], char dest[][RANKS_CAPACITY][STRING_CAPACITY], int suit, int rank );

        /**************************************************************/

        /* FUNCTION: strCpyTwo                                                                  */

        /*                                                                                      */

        /* PURPOSE: conducts second string copy operation - copying a value from the
		3D array of unshuffled cards into the 2D array that will be shuffled

        /*                                                                             

        /**************************************************************/

	void strCpyTwo ( char src[][RANKS_CAPACITY][STRING_CAPACITY] , char dest[][STRING_CAPACITY], int 				suit, int rank, int position );

        /**************************************************************/

        /* FUNCTION: getUnshuffledCards                                                                 */

        /*                                                                                      */

        /* PURPOSE: prompts user for a filename, then reads in the deck values into
		the 3D array using that data file

        /*                                                                             

        /**************************************************************/

	void getUnshuffledCards ( char arr[][RANKS_CAPACITY][STRING_CAPACITY], ifstream &fin );

        /**************************************************************/

        /* FUNCTION: printUnshuffledCards                                                               */

        /*                                                                                      */

        /* PURPOSE: prints the unshuffled cards stored in the 3D array to the 
		console using cout

        /*                                                                             

        /**************************************************************/

	void printUnshuffledCards ( char arr[][RANKS_CAPACITY][STRING_CAPACITY] );

        /**************************************************************/

        /* FUNCTION: copyCards                                                                */

        /*                                                                                      */

        /* PURPOSE: copies the card c-strings from the unshuffled 3D array
		into the 2D array to prepare them for shuffling

        /*                                                                             

        /**************************************************************/

	void copyCards ( char unshuffled[][RANKS_CAPACITY][STRING_CAPACITY], char shuffled[][STRING_CAPACITY] 				);

        /**************************************************************/

        /* FUNCTION: shuffleCards                                                                 */

        /*                                                                                      */

        /* PURPOSE: loops through the 2D array and swaps "cards" into random
		positions, so that the deck will be shuffled

        /*                                                                             

        /**************************************************************/

	void shuffleCards ( char shuffled[][STRING_CAPACITY] );

        /**************************************************************/

        /* FUNCTION: shuffleSwap                                                                 */

        /*                                                                                      */

        /* PURPOSE: manages the swapping operations during the shuffle - writes
		card one to a temp array, copies the value of card two into
		card one's position, then copies the value of card one from
		the temp array into card two's position

        /*                                                                             

        /**************************************************************/

	void shuffleSwap( char arr[][STRING_CAPACITY], int index, int random );

        /**************************************************************/

        /* FUNCTION: outputShuffled                                                                 */

        /*                                                                                      */

        /* PURPOSE: writes the contents of the shuffled deck to a data file, called
		shuffled_cards.txt

        /*                                                                             

        /**************************************************************/

	void outputShuffled ( char arr[][STRING_CAPACITY], ofstream &fout );

//Main Program

int main()
{

	//declare variables

	char unshuffledCards[SUITS_CAPACITY][RANKS_CAPACITY][STRING_CAPACITY];

	char shuffledCards[CARD_CAPACITY][STRING_CAPACITY];

	char userInput = '0';

	char dummyInput;

	bool loopThroughMenu = true;

	ifstream fin;

	ofstream fout;

	//print welcome message

	cout << "Welcome to the CS 202 card game program." << endl << endl;

	//open unshuffled cards file and read in values
	//function: getUnshuffledCards

	getUnshuffledCards ( unshuffledCards, fin );

	//copy unshuffled cards to 2d array
	//function: copyCards

	copyCards ( unshuffledCards, shuffledCards );

	//loop back to main menu until user quits program

	while ( loopThroughMenu == true )
	{

	//reset user input

	userInput = '0';

	//print menu

		cout << "Select an option:" << endl << endl;

		cout << "1. Display unshuffled cards" << endl;

		cout << "2. Shuffle cards" << endl;

		cout << "3. Write cards to file" << endl;

		cout << "4. Quit card game program" << endl << endl;

		cout << "Enter your selection: " ;

	//accept menu navigation

		cin >> userInput;

		cout << endl;

	//if prompted, print unshuffled cards to console

	if (userInput == '1' )
	   {

		//print cards
		//function: printUnshuffledCards

		printUnshuffledCards ( unshuffledCards );

		//hold for user input

			//print message

			cout << "Press any key to return to main menu: ";

			//wait for input

			cin >> dummyInput;

			cout << endl;

	   }

	//if prompted, shuffle deck

	if ( userInput == '2' )
	   {

		//conduct shuffling operation
		//function: shuffleCards

		shuffleCards ( shuffledCards );

		//hold for user input

			//print message

			cout << "The cards have been shuffled. Press any key to return to main menu: " ;

			//wait for input

			cin >> dummyInput;

			cout << endl;

	   }

	//if prompted, write shuffled deck to file

	if ( userInput == '3' )
	   {

		//conduct file output operation
		//function: outputShuffled

		outputShuffled ( shuffledCards, fout );

		//print user confirmation

			//print confirmation message

			cout << "The cards have been printed to shuffled_cards.txt" << endl << endl << "Press any key to return to main menu: " ;

			//hold for user input

			cin >> dummyInput;

			cout << endl;

	   }

	//if prompted, quit program

	if ( userInput == '4' )
	   {

		//print user message

		cout << "Thank you for using the card game program. Press any key to quit: " ;

		cin >> dummyInput;

		//return 0
		return 0;

	   }

	}

}

//Function Implementations

void strCat ( char first[], char second[] )
{
	
	//declare variables

	int countIndex = 0;
	int destIndex = 0;
	
	//move destIndex until you reach null char

	while ( first[destIndex] != '\0' )
		{
		
		destIndex++;
	
		}

	//where destIndex had a null char, replace with a space

	first[destIndex] = ' ';

	//increment destIndex

	destIndex++;
	
	//copy into destIndex, starting at countIndex, until you reach null char

	while ( second[countIndex] != '\0' )
		{
		
		first[destIndex] = second[countIndex];
		
		countIndex++;
		destIndex++;
	
		}

	//re-add null char

	first[destIndex] = '\0';

}

void strCpyOne ( char src[], char dest[][RANKS_CAPACITY][STRING_CAPACITY], int suit, int rank )
{
	
	//declare variables

	int index = 0;
	
	//copy until you reach null char

	while ( src[index] != '\0' )
		{
		
		dest[suit][rank][index] = src[index];
	
		index++;
	
		}

	//re-add null char

	dest[suit][rank][index] = '\0' ;

}

void strCpyTwo ( char src[][RANKS_CAPACITY][STRING_CAPACITY] , char dest[][STRING_CAPACITY], int suit, int rank, int position )
{
	
	//declare variables

	int index = 0;

	//copy until you reach null char

	while ( src[suit][rank][index] != '\0' )
		{
	
		dest[position][index] = src[suit][rank][index] ;

		index++;

		}

	//re-add null char

	dest[position][index] = '\0';

}

void getUnshuffledCards ( char arr[][RANKS_CAPACITY][STRING_CAPACITY], ifstream &fin )
{
	
	//declare variables

	char tempOne[STRING_CAPACITY];
	char tempTwo[STRING_CAPACITY];
	char filename[100];

	int rankIndex;
	int suitIndex;

	//prompt for filename

	cout << "Please enter the file name of the deck of unshuffled cards: " ;

	cin >> filename;

	cout << endl;

	//clear file

	fin.clear();

	//open file

	fin.open ( filename );

	//loop over the whole array

	for ( suitIndex = 0 ; suitIndex < 4 ; suitIndex++ )
		{

		for ( rankIndex = 0 ; rankIndex < 13 ; rankIndex++ )
			{
	
			//read in a rank, then a suit
	
			fin >> tempOne;

			fin >> tempTwo;

			//combine the suit into the rank
	
			strCat ( tempOne, tempTwo );

			//copy the string into the main array

			strCpyOne ( tempOne, arr, suitIndex, rankIndex );

			}

		}

	//close file

	fin.close();

}

void printUnshuffledCards ( char arr[][RANKS_CAPACITY][STRING_CAPACITY] )
{

	//declare variables

	int rankIndex;
	int suitIndex;

	//loop over array

	for ( suitIndex = 0 ; suitIndex < 4 ; suitIndex++ )
		{

		for ( rankIndex = 0 ; rankIndex < 13 ; rankIndex++ )
			{

			//print value at position, then a space

			cout << arr[suitIndex][rankIndex];

			cout << ' ' ;

			}

			//end line after listing 13 values

			cout << endl;

		}

	//end line once finished printing values

	cout << endl;

}

void copyCards ( char unshuffled[][RANKS_CAPACITY][STRING_CAPACITY], char shuffled[][STRING_CAPACITY] )
{

	//declare variables	
	
	int suitIndex;
	int rankIndex;
	int cardIndex = 0;	

	//loop over array

	for ( suitIndex = 0 ; suitIndex < 4 ; suitIndex ++ )
		{

		for ( rankIndex = 0 ; rankIndex < 13 ; rankIndex++ )
			{
		
			//copy string

			strCpyTwo ( unshuffled, shuffled, suitIndex, rankIndex, cardIndex );
	
			cardIndex++;

			}
	
		}

}

void shuffleCards ( char shuffled[][STRING_CAPACITY] )
{

//declare variables

int index = 51;
int random;

//seed random number

srand ( time(NULL) );

//loop from the top to all but the final index position

while ( index > 1 )
	{
	
	//get a random number from 0-index

	random = rand() % index ;

	//swap the strings at the index position and the random number position

	shuffleSwap( shuffled, index, random );

	//decrement

	index--;

	}

}

void shuffleSwap( char arr[][STRING_CAPACITY], int index, int random )
{

//declare variables

int swapIndex = 0;	
char temp[STRING_CAPACITY];

//move string at index into temp

while ( arr[index][swapIndex] != '\0' )
	{
	
	temp[swapIndex] = arr[index][swapIndex] ; 
	swapIndex++;

	}

//re-add null char

temp[swapIndex] = '\0';

//reset count

swapIndex = 0;

//move string at random into index position

while ( arr[random][swapIndex] != '\0' )
	{
	
	arr[index][swapIndex] = arr[random][swapIndex];
	swapIndex++;

	}

//re-add null char

arr[index][swapIndex] = '\0';

//reset count

swapIndex = 0;

//move string in temp into random position

while ( temp[swapIndex] != '\0' )
	{
	
	arr[random][swapIndex] = temp[swapIndex];
	swapIndex++;

	}

//re-add null char

arr[random][swapIndex] = '\0' ;

}

void outputShuffled ( char arr[][STRING_CAPACITY], ofstream &fout )
{

//declare variables

int index;

//open file

fout.open ( "shuffled_cards.txt" );

//print the strings

for ( index = 0 ; index < 52 ; index++ )
	{
	
	fout << arr[index];
	
	fout << endl;

	}

//close file

fout.close();

}

