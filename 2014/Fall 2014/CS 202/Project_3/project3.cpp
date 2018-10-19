
        /*****************************************************************************************/

        /* PROGRAM: project3.cpp (Card shuffle program with pointers - CS 202 Project 3 )

        /*                                                                                       */

        /* AUTHOR: Patrick Austin 

        /*                                                                                       */

        /* DATE: 17 September 2014

        /*                                                                                       */

        /* REVISIONS: revision of project2.cpp (Card deal program with structs - CS 202 Project 2)

        /*                                                                                       */

        /* PURPOSE: Reads a deck of cards and a set of players from user-provided data files. Can shuffle the cards,
					then output a full list of unshuffled and shuffled decks as well as players to the
					console. As specified, square brackets are only used for declaration of arrays, 
					so the program features heavy use of pointers for its operations.

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

//Structs

struct card { char rank[STRING_CAPACITY]; char suit[STRING_CAPACITY]; int cardValue; char location[50]; } ;

struct player { char name[50]; int total; } ;

//Function Prototypes



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
		the dest pinter.

        /*                                                                                      */

        /**************************************************************/

	void strCopy ( char* destArrayLocation, char* srcArrayLocation );

        /**************************************************************/

        /* FUNCTION: makeACard                                                                 */

        /*                                                                                      */

        /* PURPOSE: initializes target card with default values for each data member.

        /*                                                                                      */

        /**************************************************************/

	void makeACard ( card &target );

        /**************************************************************/

        /* FUNCTION: makeAPlayer                                                                */

        /*                                                                                      */

        /* PURPOSE: initializes target player with default values for each data member.

        /*                                                                                      */

        /**************************************************************/

	void makeAPlayer ( player &target );

        /**************************************************************/

        /* FUNCTION: initializeGame                                                                  */

        /*                                                                                      */

        /* PURPOSE: initializes all cards and players unshuffled, shuffled, and players arrays with default values
		using makeACard and makeAPlayer functions

        /*                                                                                      */

        /**************************************************************/

	void initializeGame ( card* unshuffledPointer, card* shuffledPointer, player* playersPointer );

        /**************************************************************/

        /* FUNCTION: modify location                                                                  */

        /*                                                                                      */

        /* PURPOSE: changes the location of target card to the value specified by locationType int parameter;
		0 means unshuffled, 1 means shuffled.

        /*                                                                                      */

        /**************************************************************/

	void modifyLocation ( card &target, int locationType );

        /**************************************************************/

        /* FUNCTION: getUnshuffledCards                                                                */

        /*                                                                                      */

        /* PURPOSE: prompts user for filename containing unshuffled deck, then reads appropriate values
		into the unshuffled deck array.

        /*                                                                                      */

        /**************************************************************/

	void getUnshuffledCards ( card* unshuffledPointer, ifstream &fin );

        /**************************************************************/

        /* FUNCTION: getPlayers                                                                 */

        /*                                                                                      */

        /* PURPOSE: prompts user for filename containing player names, then reads the values into
		the players array. Uses strCat to combine first and last names.

        /*                                                                                      */

        /**************************************************************/

	void getPlayers ( player* playersPointer, ifstream &fin );

        /**************************************************************/

        /* FUNCTION: transferCards                                                                */

        /*                                                                                      */

        /* PURPOSE: copies the cards from the unshuffled array into the shuffled array. NOTE: does not
		conduct the shuffling operation, but prepares the array to be shuffled.

        /*                                                                                      */

        /**************************************************************/

	void transferCards ( card* unshuffledPointer, card *shuffledPointer );

        /**************************************************************/

        /* FUNCTION: shuffleCards                                                               */

        /*                                                                                      */

        /* PURPOSE: conducts shuffling operation on shuffled cards array. Uses incrementing and resetting
		of pointers to handle "targetting" random cards for the shuffle

        /*                                                                                      */

        /**************************************************************/

	void shuffleCards ( card* shuffledPointer );

        /**************************************************************/

        /* FUNCTION: copyCard

        /*                                                                                      */

        /* PURPOSE: copies the values in each data member of source card into corresponding values
		of destination card.

        /*                                                                                      */

        /**************************************************************/

	void copyCard ( card* destLocation, card* srcLocation );

        /**************************************************************/

        /* FUNCTION: outputCardInformation                                                               */

        /*                                                                                      */

        /* PURPOSE: prints the values contained in each data member of target card to console.

        /*                                                                                      */

        /**************************************************************/

	void outputCardInformation ( card target );

        /**************************************************************/

        /* FUNCTION: outputPlayerInformation                                                                  */

        /*                                                                                      */

        /* PURPOSE: prints the values contained in each data member of target player to console.

        /*                                                                                      */

        /**************************************************************/

	void outputPlayerInformation ( player target );

        /**************************************************************/

        /* FUNCTION: printDeck                                                                 */

        /*                                                                                      */

        /* PURPOSE: prints the values contained in each data member of each card, for a whole deck of
		cards. Uses loop of outputCardInformation function.

        /*                                                                                      */

        /**************************************************************/

	void printDeck ( card* deckLocation );

        /**************************************************************/

        /* FUNCTION: printPlayers                                                                  */

        /*                                                                                      */

        /* PURPOSE: prints the values contained in each data member of each player, for a list of
		user-provided players. Uses loop of outputPlayerInformation function.

        /*                                                                                      */

        /**************************************************************/

	void printPlayers ( player* playersLocation );

//Main Program

int main()
{

	//declare variables

	card unshuffledCards[CARD_CAPACITY];

	card shuffledCards[CARD_CAPACITY];

	player players[4];

	char userInput = '0';

	bool loopThroughMenu = true;

	bool shuffledFlag = false;

	ifstream fin;

	ofstream fout;

	//declare pointers

	card* unshuffledPointer = unshuffledCards;

	card* shuffledPointer = shuffledCards;

	player* playersPointer = players;

	//print welcome message

	cout << "Welcome to the CS 202 card game program." << endl << endl;

	//set all player and card array values to defaults

	initializeGame ( unshuffledPointer, shuffledPointer, playersPointer );

	//open unshuffled cards file and read in values
	//function: getUnshuffledCards

	getUnshuffledCards ( unshuffledPointer, fin );

	//get players

	getPlayers ( players, fin );

	//loop back to main menu until user quits program

	while ( loopThroughMenu == true )
	{

	//reset user input

	userInput = '0';

	//print menu

	cout << "Select an option:" << endl << endl;

	cout << "1. Shuffle cards" << endl;

	cout << "2. Display decks and players" << endl;

	cout << "3. Quit card game program" << endl << endl;

	cout << "Enter your selection: " ;

	//accept menu navigation

	cin >> userInput;

	cout << endl;

	//if prompted, print unshuffled cards to console

	if (userInput == '1' )
	   {

		//conduct shuffling operation

		transferCards ( unshuffledPointer, shuffledPointer );

		shuffleCards ( shuffledPointer );

		shuffledFlag = true;

		//return to main menu

			//print message

			cout << "The cards have been shuffled. Returning to main menu... " << endl << endl ;

	   }

	//if prompted, print decks

	if ( userInput == '2' )
		{

		//if cards have not been shuffled, do not allow print
	
		 if ( shuffledFlag == false )
		 	{
		
			 //print error

			 cout << "ERROR: The cards must be shuffled before the decks can be displayed. Returning to main menu..." << endl << endl;

			 }

		//if cards have been shuffled, handle print

		 if ( shuffledFlag == true )
			{
	
			//print message
	
			cout << "The unshuffled deck contains: " << endl << endl;

			printDeck ( unshuffledPointer );

			//print message

			cout << "The shuffled deck contains: " << endl << endl;

			printDeck ( shuffledPointer );

			//print players

			cout << "The players are: " << endl << endl;

			printPlayers ( playersPointer );
	
			//return to main menu

			cout << "The decks and players have been displayed. Returning to main menu..." << endl << endl;

			}

		}

	//if prompted, quit program

	if ( userInput == '3' )
	   {

		//print user message

		cout << "Thank you for using the card game program. Press any key to quit: " ;

		cin >> userInput;

		//return 0

		return 0;

	   }

	}

}

//Function Implementations

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

void makeACard ( card &target )
{
	
	//declare variables

	card* targetPointer = &target;

	char suit[]     = "suit" ;
	char rank[]     = "rank" ;
	char location[] = "location";

	char* suitPointer = suit;
	char* rankPointer = rank;
	char* locationPointer = location;
	
	//set initial value for suit
	
	strCopy ( (*targetPointer).suit, suitPointer );
	
	//set initial value for rank

	strCopy ( (*targetPointer).rank, rankPointer );
	
	//set initial value for cvalue

	target.cardValue = 0;
	
	//set initial value for location

	strCopy ( (*targetPointer).location, locationPointer );

}

void makeAPlayer ( player &target )
{
	
	//declare variables

	player* targetPointer = &target;

	char name[] = "first last" ;

	char* namePointer = name;
	
	//set initial value for name

	strCopy ( (*targetPointer).name, namePointer );
	
	//set initial value for total

	target.total = 0;

}

void initializeGame ( card* unshuffledPointer, card* shuffledPointer, player* playersPointer )
{
	
	//declare variables

	int index;

	//initialize unshuffled array

	for ( index = 0; index < 52; index++ )
		{
	
		makeACard ( *unshuffledPointer );
		
		unshuffledPointer++;

		}

	//initialize shuffled array

	for ( index = 0; index < 52; index++ )
		{
	
		makeACard ( *shuffledPointer );

		shuffledPointer++;

		}

	//initialize players array

	for ( index = 0; index < 4; index++ )
		{
	
		makeAPlayer ( *playersPointer );

		playersPointer++;

		}

}

void modifyLocation ( card &target, int locationType )
{
	
	//declare variables

	card* targetPointer = &target;

	char unshuffled[] = "unshuffled" ;
	char shuffled[]   = "shuffled" ;

	char* unshuffledPointer = unshuffled;
	char* shuffledPointer = shuffled;

	//assign location according to type requested in locationType parameter		
	
	if ( locationType == 0 )
		{
		
		strCopy ( (*targetPointer).location, unshuffledPointer );
	
		}
	
	if ( locationType == 1 )
		{
		
		strCopy ( (*targetPointer).location, shuffledPointer );
	
		}

}

void getUnshuffledCards ( card* unshuffledPointer, ifstream &fin )
{
	
	//declare variables

	char tempOne[STRING_CAPACITY];
	char tempTwo[STRING_CAPACITY];
	int  tempInt;

	char filename[50];

	int index;

	//prompt for filename

	cout << "Enter the name of the unshuffled cards data file: ";

	cin >> filename;

	cout << endl;

	//clear file

	fin.clear();

	//open file

	fin.open ( filename );

	//loop over the whole array

	for ( index = 0 ; index < 52; index++ )
		{

		//read in a rank, then a suit, then cardValue
	
		fin >> tempOne;

		fin >> tempTwo;

		char* tempOnePointer = tempOne;

		char* tempTwoPointer = tempTwo;

		fin >> tempInt;

		//copy the card info into the main array

			//suit

			char* suitPointer = (*unshuffledPointer).suit;

			strCopy ( suitPointer, tempOnePointer );

			//rank

			char* rankPointer = (*unshuffledPointer).rank;

			strCopy ( rankPointer, tempTwoPointer );

			//cardValue

			(*unshuffledPointer).cardValue = tempInt;

		//update location
	
		modifyLocation ( *unshuffledPointer, 0 );			

		//move to the next card

		unshuffledPointer++;

		}

	//close file

	fin.close();

}

void getPlayers ( player* playersPointer, ifstream &fin )
{
	
	//declare variables

	char filename[50];

	char tempOne[50];
	char tempTwo[50];

	int index;

	//prompt for filename

	cout << "Enter the name of the players data file: ";

	cin >> filename;

	cout << endl;

	//clear file

	fin.clear();

	//open file

	fin.open ( filename );

	//take values, insert them into array

	for ( index = 0 ; index < 4 ; index++ )
		{
	
		//read in first and last names, assign pointers

		fin >> tempOne;

		fin >> tempTwo;

		char* tempOnePointer = tempOne;

		char* tempTwoPointer = tempTwo;

		//append last name into first name array

		strCat ( tempOnePointer, tempTwoPointer );

		//copy from temp array into player struct

		char* namePointer = (*playersPointer).name ;

		strCopy( namePointer, tempOnePointer );

		//move to the next player

		playersPointer++;

		}

	//close file

	fin.close();

}

void transferCards ( card* unshuffledPointer, card *shuffledPointer )
{
	
	//declare variables

	int index;

	//copy each card from unshuffled to shuffled

	for ( index = 0; index < 52; index++ )
		{
	
		//copy card

		copyCard ( shuffledPointer, unshuffledPointer );

		//update location fron unshuffled to shuffled

		modifyLocation ( *shuffledPointer, 1);
		
		//increment pointers

		unshuffledPointer++;
		shuffledPointer++;

		}


}

void shuffleCards ( card* shuffledPointer )
{
	
	//declare variables
	
	card temp;
	card* homePointer = shuffledPointer;
	card* randomPointer = shuffledPointer;
	card* tempPointer = &temp;

	int index;
	int innerIndex;

	int random;
	int count = 0;

	//seed random number

	srand ( time(NULL) );

	//move homePointer and count to the end of the array

	for ( index = 0; index < 51; index++ )
		{
	
		homePointer++;
		count++;

		}

	//loop from the end to all but the first array position

	for ( index = 51; index > 1; index-- )
		{
	
		//get a random number from 0-count

		random = rand() % count;

		//move randomPointer to that location in the array

		for ( innerIndex = 0; innerIndex < random; innerIndex++ )
			{
	
			randomPointer++;

			}

		//swap the cards at homePointer and randomPointer

		copyCard ( tempPointer, homePointer );
		copyCard ( homePointer, randomPointer );
		copyCard ( randomPointer, tempPointer );

		//reset randomPointer to initial 0 location in array

		randomPointer = shuffledPointer;
		
		//decrement homePointer and count

		homePointer--;
		count--;

		}

}

void copyCard ( card* destLocation, card* srcLocation )
{
	
	//declare variables

	char* rankSrc = (*srcLocation).rank;
	char* suitSrc = (*srcLocation).suit;
	char* locationSrc = (*srcLocation).location; 

	char* rankDest = (*destLocation).rank;
	char* suitDest = (*destLocation).suit;
	char* locationDest = (*destLocation).location; 

	//copy suit

	strCopy ( suitDest, suitSrc );

	//copy rank
	
	strCopy ( rankDest, rankSrc );

	//copy cvalue

	(*destLocation).cardValue = (*srcLocation).cardValue; 

	//copy location

	strCopy ( locationDest, locationSrc );

}

void outputCardInformation ( card target )
{
	
	//print information for each data member of target card to the console

	cout << "Suit: " << target.suit << "   ";
	cout << "Rank: " << target.rank << "   ";
	cout << "Card value: " << target.cardValue << "   ";
	cout << "Card location: " << target.location << "   " << endl << endl;

}

void outputPlayerInformation ( player target )
{

	//print information for each data member of target player to console

	cout << "Player's name: " << target.name << "   ";

	cout << "Player's total score: " << target.total << endl << endl;

}

void printDeck ( card* deckLocation)
{
	
	//declare variables

	int index;

	//loop over the whole deck, printing each card to the screen

	for ( index = 0; index < 52; index++ )
		{
	
		cout << "Card " << index + 1 << ":" << endl;
	
		outputCardInformation ( *deckLocation );

		deckLocation++;

		}

}

void printPlayers ( player* playersLocation )
{

	//declare variables
	
	int index;

	//loop over all players, printing each player's information to the screen

	for ( index = 0; index < 4; index++ )
		{
	
		cout << "Player " << index + 1 << ":" << endl;
	
		outputPlayerInformation ( *playersLocation );

		playersLocation++;

		}

}
