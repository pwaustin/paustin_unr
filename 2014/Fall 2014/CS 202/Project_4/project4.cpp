
        /*****************************************************************************************/

        /* PROGRAM: project4.cpp (Card shuffle program with dynamic memory - CS 202 Project 4 )

        /*                                                                                       */

        /* AUTHOR: Patrick Austin 

        /*                                                                                       */

        /* DATE: 17 September 2014

        /*                                                                                       */

        /* REVISIONS: revision of project3.cpp (Card shuffle program with pointers - CS 202 Project 3)

        /*                                                                                       */

        /* PURPOSE: Reads a deck of cards and a set of players (of a number specified in the data file) from 
					user-provided data files. Can shuffle the cards, then output full lists
					of unshuffled and shuffled decks as well as players to the console. As 
					specified, this program maintains project 3's strictures re: pointers,
					and uses dynamic memory for all arrays.

        /*****************************************************************************************/



//Header Files

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

//Structs

struct card { char* rank; char* suit; int cardValue; char* location; } ;

struct player { char* name; int total; } ;

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
		the dest pointer.

        /*                                                                                      */

        /**************************************************************/

	void strCopy ( char* destArrayLocation, char* srcArrayLocation );

        /**************************************************************/

        /* FUNCTION: makeACard                                                                 */

        /*                                                                                      */

        /* PURPOSE: initializes card being pointed at with default values for each data member.

        /*                                                                                      */

        /**************************************************************/

	void makeACard ( card* targetPointer );

        /**************************************************************/

        /* FUNCTION: makeAPlayer                                                                */

        /*                                                                                      */

        /* PURPOSE: initializes player being pointed at with default values for each data member.

        /*                                                                                      */

        /**************************************************************/

	void makeAPlayer ( player* playerPointer );

        /**************************************************************/

        /* FUNCTION: initializeCards                                                                 */

        /*                                                                                      */

        /* PURPOSE: initializes cards in the unshuffled and shuffled arrays with default values in each
		data member using looping makeACard function

        /*                                                                                      */

        /**************************************************************/

	void initializeCards ( card* unshuffledPointer, card* shuffledPointer );

        /**************************************************************/

        /* FUNCTION: initializePlayers                                                                 */

        /*                                                                                      */

        /* PURPOSE: initializes the number of players specified with default values in each data member
		using looping makeAPlayer function

        /*                                                                                      */

        /**************************************************************/

	void initializePlayers ( player* playersPointer, int numberOfPlayers );

        /**************************************************************/

        /* FUNCTION: modifyLocation                                                                  */

        /*                                                                                      */

        /* PURPOSE: changes the location of target card to the value specified by locationType int parameter;
		0 means unshuffled, 1 means shuffled. Deallocates previous location value in the process.

        /*                                                                                      */

        /**************************************************************/

	void modifyLocation ( card* targetPointer, int locationType );

        /**************************************************************/

        /* FUNCTION: getUnshuffledCards                                                                */

        /*                                                                                      */

        /* PURPOSE: prompts user for filename containing unshuffled deck, then reads appropriate values
		into the unshuffled deck array. Deallocates temp values for the cards in the process.

        /*                                                                                      */

        /**************************************************************/

	void getUnshuffledCards ( ifstream &fin, card* unshuffledPointer );

        /**************************************************************/

        /* FUNCTION: howManyPlayers                                                                */

        /*                                                                                      */

        /* PURPOSE: opens the datafile specified by the filename parameter and reads the first value, which as
		per program specifications should be the number of players. Returns this value as an int. Used
		for the main program to know the size of the players array that should be dynamically allocated
        /*                                                                                      */

        /**************************************************************/

	int howManyPlayers ( ifstream &fin, char* filename );

        /**************************************************************/

        /* FUNCTION: getPlayers                                                                 */

        /*                                                                                      */

        /* PURPOSE: opens the datafile specified by the filename parameter and reads the player values into the
		players array. Deallocates temp values for player names in the process.

        /*                                                                                      */

        /**************************************************************/

	void getPlayers ( ifstream &fin, player* playersPointer, char* filename );

        /**************************************************************/

        /* FUNCTION: transferCards                                                                */

        /*                                                                                      */

        /* PURPOSE: copies the cards from the unshuffled array into the shuffled array. NOTE: does not
		conduct the shuffling operation, but prepares the array to be shuffled. NOTE: deallocates
		the previous values in the process, to make sure dynamic memory is being used efficiently

        /*                                                                                      */

        /**************************************************************/

	void transferCards ( card* unshuffledPointer, card *shuffledPointer );

        /**************************************************************/

        /* FUNCTION: shuffleCards                                                               */

        /*                                                                                      */

        /* PURPOSE: conducts shuffling operation on shuffled cards array. Uses incrementing and resetting
		of pointers to handle "targetting" random cards for the shuffle. Uses a temp card for holding
		values during the card swap, and deallocates the temp card's data at the end.

        /*                                                                                      */

        /**************************************************************/

	void shuffleCards ( card* shuffledPointer );

        /**************************************************************/

        /* FUNCTION: copyCard

        /*                                                                                      */

        /* PURPOSE: copies the values in each data member of source card into corresponding values
		of destination card. NOTE: deallocates previous values during the copy, to make sure
		dynamic memory is being used efficiently

        /*                                                                                      */

        /**************************************************************/

	void copyCard ( card* destCard, card* srcCard );

        /**************************************************************/

        /* FUNCTION: outputCardInformation                                                               */

        /*                                                                                      */

        /* PURPOSE: prints the values contained in each data member of target card to console.

        /*                                                                                      */

        /**************************************************************/

	void outputCardInformation ( card* targetPointer );

        /**************************************************************/

        /* FUNCTION: outputPlayerInformation                                                                  */

        /*                                                                                      */

        /* PURPOSE: prints the values contained in each data member of target player to console.

        /*                                                                                      */

        /**************************************************************/

	void outputPlayerInformation ( player* targetPointer );

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

	void printPlayers ( player* playersLocation, int numberOfPlayers );

        /**************************************************************/

        /* FUNCTION: deallocateCards                                                                */

        /*                                                                                      */

        /* PURPOSE: deallocates the dynamic memory reserved for each data member of each card 
		for the unshuffled and shuffled decks and sets pointers for those data members to NULL. 
		Used to help free up remaining dynamic memory at the end of the program. 

        /*                                                                                      */

        /**************************************************************/

	void deallocateCards ( card* unshuffledPointer, card* shuffledPointer );

        /**************************************************************/

        /* FUNCTION: deallocatePlayers                                                      */

        /*                                                                                      */

        /* PURPOSE: deallocates the dynamic memory reserved for the name of each playe and sets pointers 
		for those names to NULL. Used to help free up remaining dynamic memory at the end of the program. 

        /*                                                                                      */

        /**************************************************************/

	void deallocatePlayers ( player* playersPointer, int numberOfPlayers );

//Main Program

int main()
{

	//declare variables

	char userInput = '0';

	bool loopThroughMenu = true;

	bool shuffledFlag = false;

	ifstream fin;

	int numberOfPlayers;

	char* temp = new char [50];

	//print welcome message

	cout << "Welcome to the CS 202 card game program." << endl << endl;

	//allocate memory for and initialize cards

		//allocate dynamic memory for cards
	
		card* unshuffledPointer = new card[52];
	
		card* shuffledPointer = new card[52];
	
		//initialize the cards with default values
	
		initializeCards ( unshuffledPointer, shuffledPointer );

	//allocate memory for and initialize players

		//prompt for players data file

		cout << "Enter the name of the players data file: " ;

		cin >> temp;

		cout << endl;

		//put the user's filename input in an exactly sized array

		char* filename = new char [ strLen(temp) + 1 ];

		strCopy ( filename, temp );

		//deallocate at temp and null temp pointer - finished with it

		delete [] temp;

		temp = NULL;

		//get the number of players from the data file

		numberOfPlayers = howManyPlayers ( fin, filename );

		//allocate dynamic memory array for the number of players found

		player* playersPointer = new player[numberOfPlayers];

		//initalize all players with default values

		initializePlayers ( playersPointer, numberOfPlayers );

	//read in the values from players datafile

		//get values	

		getPlayers ( fin, playersPointer, filename );

		//deallocate and null filename - finished with it

		delete [] filename;

		filename = NULL;

	//open unshuffled cards datafile and read in values
	//function: getUnshuffledCards

	getUnshuffledCards ( fin, unshuffledPointer );

	//loop back to main menu until user quits program

	while ( loopThroughMenu == true )
	{

	//reset user input

	userInput = '0';

	//print menu

	cout << "Select an option:" << endl << endl;

	cout << "<1> Shuffle cards" << endl;

	cout << "<2> Display players" << endl;

	cout << "<3> Display unshuffled deck" << endl;

	cout << "<4> Display shuffled deck" << endl;

	cout << "<5> Quit card game program" << endl << endl;

	cout << "Enter your selection: " ;

	//accept menu navigation

	cin >> userInput;

	cout << endl;

	//if prompted, shuffle cards

	if ( userInput == '1' )
	   {

		//conduct shuffling operation: copy cards from unshuffled to shuffled, shuffle them, set flag that shuffling happened

		transferCards ( unshuffledPointer, shuffledPointer );

		shuffleCards ( shuffledPointer );

		shuffledFlag = true;

		//return to main menu

		cout << "The cards have been shuffled. Returning to main menu... " << endl << endl ;

	   }

	//if prompted, print players

	if ( userInput == '2' )
		{
	
		cout << "The players are: " << endl << endl;

		printPlayers ( playersPointer, numberOfPlayers );	

		cout << "Returning to main menu..." << endl << endl;
		}

	//if prompted, print unshuffled deck

	if ( userInput == '3' )
		{

		cout << "The unshuffled deck contains: " << endl << endl;

		printDeck ( unshuffledPointer );

		cout << "Returning to main menu..." << endl << endl;

		}

	//if prompted, print shuffled deck

	if ( userInput == '4' )
		{
	
		//if the cards have not yet been shuffled, print an error message

		if ( shuffledFlag == false )
			{
	
			cout << "ERROR: the cards have not yet been shuffled. Returning to main menu..." << endl << endl;

			}

		//if the cards have been shuffled, print the deck
	
		if ( shuffledFlag == true )
			{

			cout << "The shuffled deck contains: " << endl << endl;

			printDeck ( shuffledPointer );

			cout << "Returning to main menu..." << endl << endl;
			
			}

		}

	//if prompted, quit program

	if ( userInput == '5' )
		{

		//print user message

		cout << "Thank you for using the card game program. Press any key to quit: " ;

		cin >> userInput;

		//deallocate the remaining dynamic memory

			//clear data members/secondary arrays

			deallocateCards ( unshuffledPointer, shuffledPointer );

			deallocatePlayers ( playersPointer, numberOfPlayers ) ;

			//clear main arrays

			delete [] unshuffledPointer;
	
			delete [] shuffledPointer;
	
			delete [] playersPointer;

			//null main arrays

			unshuffledPointer = NULL;

			shuffledPointer = NULL;

			playersPointer = NULL;

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

void makeACard ( card* targetPointer )
{

	//set initial value for suit
	
	(*targetPointer).suit = new char [ strLen("suit") + 1 ];

	strCopy ( (*targetPointer).suit, "suit" );

	//set initial value for rank
	
	(*targetPointer).rank = new char [ strLen("rank") + 1 ];

	strCopy ( (*targetPointer).rank, "rank" );

	//set card value

	(*targetPointer).cardValue = 0;

	//set initial value for location

	(*targetPointer).location = new char [ strLen("location") + 1 ];

	strCopy ( (*targetPointer).location, "location" );

}

void makeAPlayer ( player* playerPointer )
{

	//set initial value for name

	(*playerPointer).name = new char [ strLen("first last") + 1 ];

	strCopy ( (*playerPointer).name, "first last" );
	
	//set initial value for total

	(*playerPointer).total = 0;

}

void initializeCards ( card* unshuffledPointer, card* shuffledPointer )
{
	
	//declare variables

	int index;

	//initialize unshuffled and shuffled arrays

	for ( index = 0; index < 52; index++ )
		{
	
		makeACard ( shuffledPointer );

		makeACard ( unshuffledPointer );

		shuffledPointer++;
		
		unshuffledPointer++;

		}

}

void initializePlayers ( player* playersPointer, int numberOfPlayers )
{
	
	//initialize variables

	int index;

	//for however many players there are, initialize each one

	for ( index = 0 ; index < numberOfPlayers ; index++ )
		{
	
		makeAPlayer ( playersPointer );

		playersPointer++;

		}

}

void modifyLocation ( card* targetPointer, int locationType )
{

	//assign location according to type requested in locationType parameter		
	
	if ( locationType == 0 )
		{
	
		//deallocate old string

		delete [] (*targetPointer).location;

		//allocate new string

		(*targetPointer).location = new char [ strLen("unshuffled") + 1 ];

		//copy value

		strCopy ( (*targetPointer).location, "unshuffled" );
	
		}
	
	if ( locationType == 1 )
		{
		
		//deallocate old string

		delete [] (*targetPointer).location;

		//allocate new string

		(*targetPointer).location = new char [ strLen("shuffled") + 1 ];
	
		//copy value

		strCopy ( (*targetPointer).location, "shuffled" );
	
		}

}

void getUnshuffledCards ( ifstream &fin , card* unshuffledPointer )
{
	
	//declare variables

	char* tempOne = new char[50];
	char* tempTwo = new char[50];
	char* filename;
	int  tempInt;

	int index;

	//prompt for filename

	cout << "Enter the name of the unshuffled cards data file: ";

	cin >> tempOne;

	cout << endl;

	//put filename in exactly sized array

	filename = new char [ strLen(tempOne) + 1 ];	

	strCopy ( filename, tempOne );

	//clear file

	fin.clear();

	//open file

	fin.open ( filename );

	//loop over the whole array

	for ( index = 0 ; index < 52 ; index++ )
		{

		//read in a rank, then a suit, then a cardValue
	
		fin >> tempOne;

		fin >> tempTwo;

		fin >> tempInt;

		//copy the card info into the main array

			//suit - deallocate previous temp value first

			delete [] (*unshuffledPointer).suit; 

			(*unshuffledPointer).suit = new char [ strLen(tempOne) + 1 ];

			strCopy ( (*unshuffledPointer).suit, tempOne );

			//rank - deallocate previous temp value first

			delete [] (*unshuffledPointer).rank;

			(*unshuffledPointer).rank = new char [ strLen(tempTwo) + 1 ];
	
			strCopy ( (*unshuffledPointer).rank, tempTwo );

			//cardValue

			(*unshuffledPointer).cardValue = tempInt;

		//update location - function will deallocate previous temp value

		modifyLocation ( unshuffledPointer, 0 );				

		//move to the next card

		unshuffledPointer++;

		}

	//close file

	fin.close();

	//deallocate temp arrays

	delete [] tempOne;
	delete [] tempTwo;
	delete [] filename;

	//null temp arrays

	tempOne = NULL;
	tempTwo = NULL;
	filename = NULL;

}


int howManyPlayers ( ifstream &fin, char* filename )
{

	//declare variables

	int numberOfPlayers;

	//clear file

	fin.clear();

	//open file

	fin.open ( filename );

	//get number of players from the top of the file

	fin >> numberOfPlayers;

	//close file

	fin.close();

	//return the number of players
		
	return numberOfPlayers;

}

void getPlayers ( ifstream &fin, player* playersPointer, char* filename )
{
	
	//declare variables

	int index;
	int numberOfPlayers;

	char* tempOne = new char[50];
	char* tempTwo = new char[50];

	//clear file

	fin.clear();

	//open file

	fin.open ( filename );

	//get number of players

	fin >> numberOfPlayers;

	//take values, insert them into array

	for ( index = 0 ; index < numberOfPlayers ; index++ )
		{
	
		//read in first and last names, assign pointers

		fin >> tempOne;

		fin >> tempTwo;

		//append last name into first name array

		strCat ( tempOne, tempTwo );

		//deallocate previous temp value

		delete [] (*playersPointer).name;

		//allocate memory for the player's name

		(*playersPointer).name = new char [ strLen(tempOne) + 1 ] ;

		//copy from temp array into player struct

		strCopy( (*playersPointer).name, tempOne );

		//move to the next player

		playersPointer++;

		}

	//close file

	fin.close();

	//deallocate temps

	delete [] tempOne;
	delete [] tempTwo;

	//null temps

	tempOne = NULL;
	tempTwo = NULL;

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

		modifyLocation ( shuffledPointer, 1);
		
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

	//initialize the temp card with default values

	makeACard ( tempPointer );

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

	//deallocate memory from the temp card

	delete [] temp.suit;
	delete [] temp.rank;
	delete [] temp.location;

	//null pointers for the temp card

	temp.suit = NULL;
	temp.rank = NULL;
	temp.location = NULL;

}

void copyCard ( card* destCard, card* srcCard )
{
	
	//declare variables

	//copy suit

		//deallocate old value

		delete [] (*destCard).suit;

		//allocate new memory of length of new value

		(*destCard).suit = new char [ strLen( (*srcCard).suit ) + 1 ];

		//copy src suit into dest suit

		strCopy ( (*destCard).suit , (*srcCard).suit );

	//copy rank
	
		//deallocate old value

		delete [] (*destCard).rank;

		//allocate new memory of length of new value

		(*destCard).rank = new char [ strLen( (*srcCard).rank ) + 1];

		//copy src rank into dest rank

		strCopy ( (*destCard).rank , (*srcCard).rank );

	//copy cvalue

	(*destCard).cardValue = (*srcCard).cardValue; 

	//copy location

		//deallocate old value

		delete [] (*destCard).location;

		//allocate new memory of length of new value

		(*destCard).location = new char [ strLen( (*srcCard).location ) + 1 ];

		//copy src location into dest location
		
		strCopy ( (*destCard).location , (*srcCard).location );

}

void outputCardInformation ( card* targetPointer )
{
	
	//print information for each data member of target card to the console

	cout << "Suit: " << (*targetPointer).suit << "   ";
	cout << "Rank: " << (*targetPointer).rank << "   ";
	cout << "Card value: " << (*targetPointer).cardValue << "   ";
	cout << "Card location: " << (*targetPointer).location << "   " << endl << endl;

}

void outputPlayerInformation ( player* targetPointer )
{

	//print information for each data member of target player to console

	cout << "Player's name: " << (*targetPointer).name << "   ";

	cout << "Player's total score: " << (*targetPointer).total << endl << endl;

}

void printDeck ( card* deckLocation)
{
	
	//declare variables

	int index;

	//loop over the whole deck, printing each card to the screen

	for ( index = 0; index < 52; index++ )
		{
	
		cout << "Card " << index + 1 << ":" << endl;
	
		outputCardInformation ( deckLocation );

		deckLocation++;

		}

}

void printPlayers ( player* playersLocation, int numberOfPlayers )
{

	//declare variables
	
	int index;

	//loop over all players, printing each player's information to the screen

	for ( index = 0; index < numberOfPlayers; index++ )
		{
	
		cout << "Player " << index + 1 << ":" << endl;
	
		outputPlayerInformation ( playersLocation );

		playersLocation++;

		}

}

void deallocateCards ( card* unshuffledPointer, card* shuffledPointer )
{
	
	//declare variables

	int index;

	//deallocate each data member of each card

	for ( index = 0 ; index < 52 ; index++ )
		{
	
		//deallocate data members

		delete [] (*unshuffledPointer).suit;

		delete [] (*unshuffledPointer).rank;

		delete [] (*unshuffledPointer).location;

		delete [] (*shuffledPointer).rank;

		delete [] (*shuffledPointer).suit;
		
		delete [] (*shuffledPointer).location;

		//set data member pointers to null

		(*unshuffledPointer).suit = NULL;

		(*unshuffledPointer).rank = NULL;

		(*unshuffledPointer).location = NULL;

		(*shuffledPointer).rank = NULL;

		(*shuffledPointer).suit = NULL;
		
		(*shuffledPointer).location = NULL;	

		//increment arrays to the next card

		unshuffledPointer++;

		shuffledPointer++;

		}

}

void deallocatePlayers ( player* playersPointer, int numberOfPlayers )
{
	
	//declare variables

	int index;

	//deallocate each name in each player

	for ( index = 0 ; index < numberOfPlayers ; index++ )
		{
	
		//deallocate array

		delete [] (*playersPointer).name;

		//set pointer to null

		(*playersPointer).name = NULL;

		//increment to the next player

		playersPointer++;

		}

}
