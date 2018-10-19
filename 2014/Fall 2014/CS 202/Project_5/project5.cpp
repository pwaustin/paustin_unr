
        /*****************************************************************************************/

        /* PROGRAM: project5.cpp (Card deal program with dynamic memory - CS 202 Project 5 )

        /*                                                                                       */

        /* AUTHOR: Patrick Austin 

        /*                                                                                       */

        /* DATE: 30 September 2014

        /*                                                                                       */

        /* REVISIONS: revision of project4.cpp (Card shuffle program with dynamic memory - CS 202 Project 4)

        /*                                                                                       */

        /* PURPOSE: Prompts user for number of players. Reads a deck of cards and a set of players 
					(of the number specified by the user) from user-provided data files. Can shuffle the cards, 
					then perform a correct deal of the cards to the players as per the rules of scat. As 
					specified, this program maintains project 4's rules re: pointers and dynamic memory.
					Square brackets are only used to allocate or deallocate arrays out of dynamic memory.

        /*****************************************************************************************/



//Header Files

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>
#include "string_spec.h"
using namespace std;

//Structs

struct card { char* rank; char* suit; int cardValue; char* location; } ;

struct player { char* name; card* hand; int total; } ;

//Function Prototypes

        /**************************************************************/

        /* FUNCTION: makeACard                                                                 */

        /*                                                                                      */

        /* PURPOSE: initializes card being pointed at with default values for each data member

        /*                                                                                      */

        /**************************************************************/

	void makeACard ( card* targetPointer );

        /**************************************************************/

        /* FUNCTION: makeAPlayer                                                                */

        /*                                                                                      */

        /* PURPOSE: initializes player being pointed at with default values for each data member;
					calls makeACard to initialize the player's hand

        /*                                                                                      */

        /**************************************************************/

	void makeAPlayer ( player* playerPointer );

        /**************************************************************/

        /* FUNCTION: initializeCards                                                                 */

        /*                                                                                      */

        /* PURPOSE: initializes cards in the target deck with default values using looping makeACard function

        /*                                                                                      */

        /**************************************************************/

	void initializeCards ( card* targetDeck );

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
		0 means unshuffled, 1 means shuffled, 2 means discard, 3 means stock, 4 means to use the name given by
		the namePointer parameter. Deallocates previous location value in the process. User can use a dummy
		value for namePointer if a player's name is not the intended location of the card.

        /*                                                                                      */

        /**************************************************************/

	void modifyLocation ( card* targetPointer, char* namePointer, int locationType );

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

        /* PURPOSE: asks the user how many players will be dealt to in the game. If the user enters
			a value under 2 or over 8, it will default to the nearest value.
        /*                                                                                      */

        /**************************************************************/

	int howManyPlayers ();

        /**************************************************************/

        /* FUNCTION: getPlayers                                                                 */

        /*                                                                                      */

        /* PURPOSE: opens the datafile specified by the filename parameter and reads the player values into the
		players array. Deallocates temp values for player names in the process.

        /*                                                                                      */

        /**************************************************************/

	void getPlayers ( ifstream &fin, player* playersPointer, int numberOfPlayers );

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

        /* FUNCTION: deallocateCard                                                                 */

        /*                                                                                      */

        /* PURPOSE: deallocates and nulls the pointer to each data member of target card

        /*                                                                                      */

        /**************************************************************/

	void deallocateCard ( card* targetCard );

        /**************************************************************/

        /* FUNCTION: deallocateCards                                                                */

        /*                                                                                      */

        /* PURPOSE: deallocates the dynamic memory reserved for each data member of target deck
		of 52 cards and sets pointers for those data members to NULL.

        /*                                                                                      */

        /**************************************************************/

	void deallocateDeck ( card* targetDeck );

        /**************************************************************/

        /* FUNCTION: deallocatePlayers                                                      */

        /*                                                                                      */

        /* PURPOSE: deallocates the dynamic memory reserved for the name and hand of each player and sets pointers 
		for those data members to NULL. Uses deallocateCard to free allocated data for cards in hand and set those
		pointers to NULL.

        /*                                                                                      */

        /**************************************************************/

	void deallocatePlayers ( player* playersPointer, int numberOfPlayers );

        /**************************************************************/

        /* FUNCTION: resetTotals                                                      */

        /*                                                                                      */

        /* PURPOSE: resets the total score of each player to 0. Called before dealing operation to assure
		a fresh and correct score after the deal should the user deal multiple times.

        /*                                                                                      */

        /**************************************************************/

	void resetTotals ( player* playersPointer, int numberOfPlayers );

        /**************************************************************/

        /* FUNCTION: dealCards                                                   */

        /*                                                                                      */

        /* PURPOSE: Deals the cards to the players, the first step of the deal for the scat card game.
		As per the rules, deals a card from the top of the deck to each player, repeated 3 times. Returns
		the number of cards dealt out of the deck so far, for use in subsequent deal operations.

        /*                                                                                      */

        /**************************************************************/

	int dealCards ( card* shuffledPointer, player* playersPointer, int numberOfPlayers );

       /**************************************************************/

        /* FUNCTION: dealToDiscard                                            */

        /*                                                                                      */

        /* PURPOSE: Deals a card to the discard pile. To be called after the players have been dealt their
		cards, as per the rules of scat. Uses the number of cards dealt so far to determine which card to deal.
		Returns the updated number of cards dealt (previous value + 1)

        /*                                                                                      */

        /**************************************************************/

	int dealToDiscard ( card* shuffledPointer, card* discardPointer, int cardsDealt );

       /**************************************************************/

        /* FUNCTION: dealToStock                                                  */

        /*                                                                                      */

        /* PURPOSE: Deals whatever is left in the shuffled deck into the stock, the last part of the deal
		for the scat card game. Uses cardsDealt value returned from dealToDiscard to figure out how many
		cards need to go into the stock.

        /*                                                                                      */

        /**************************************************************/

	void dealToStock ( card* shuffledPointer, card* stockPointer, int cardsDealt );

//Main Program

int main()
{

	//declare variables

	char userInput = '0';

	bool loopThroughMenu = true;

	bool shuffledFlag = false;

	ifstream fin;

	int numberOfPlayers;

	int cardsDealt;

	//print welcome message

	cout << "Welcome to the CS 202 card game program." << endl << endl;

	//allocate memory for and initialize cards

		//allocate dynamic memory for cards
	
		card* unshuffledPointer = new card[52];
		card* shuffledPointer = new card[52];
		card* discardPointer = new card[52];
		card* stockPointer = new card[52];
	
		//initialize the cards with default values
	
		initializeCards ( unshuffledPointer );
		initializeCards ( shuffledPointer );
		initializeCards ( discardPointer );
		initializeCards ( stockPointer );

	//allocate memory for and initialize players

		//prompt for number of players

		numberOfPlayers = howManyPlayers();

		//allocate dynamic memory array for the number of players found

		player* playersPointer = new player[numberOfPlayers];

		//initalize all players with default values

		initializePlayers ( playersPointer, numberOfPlayers );

	//prompt for and read in the values from players datafile

	getPlayers ( fin, playersPointer, numberOfPlayers );

	//prompt for and read in the values from the unshuffled cards datafile

	getUnshuffledCards ( fin, unshuffledPointer );

	//loop back to main menu until user quits program

	while ( loopThroughMenu == true )
		{
	
		//reset user input
	
		userInput = '0';
	
		//print menu
	
		cout << "Select an option:" << endl << endl;
	
		cout << "<1> Shuffle cards" << endl;
	
		cout << "<2> Display unshuffled deck" << endl;
	
		cout << "<3> Display shuffled deck" << endl;
	
		cout << "<4> Deal cards" << endl;
	
		cout << "<5> Quit card game program" << endl << endl;
	
		cout << "Enter your selection: " ;
	
		//accept menu navigation
	
		cin >> userInput;
	
		cout << endl;
	
		//if prompted, shuffle cards
	
		if ( userInput == '1' )
		   {
	
			//conduct shuffling operation: copy cards from unshuffled to shuffled, shuffle them, set flag to indicate that shuffling has happened
	
			transferCards ( unshuffledPointer, shuffledPointer );
	
			shuffleCards ( shuffledPointer );
	
			shuffledFlag = true;
	
			//return to main menu
	
			cout << "The cards have been shuffled. Returning to main menu... " << endl << endl ;
	
		   }
	
		//if prompted, print unshuffled deck
	
		if ( userInput == '2' )
			{
	
			cout << "The unshuffled deck contains: " << endl << endl;
	
			printDeck ( unshuffledPointer );
	
			cout << "Returning to main menu..." << endl << endl;
	
			}
	
		//if prompted, print shuffled deck
	
		if ( userInput == '3' )
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
	
		//if prompted, deal cards
	
		if ( userInput == '4' )
			{
	
			//if the cards have not been shuffled, don't allow deal
	
			if ( shuffledFlag == false )
				{
	
				//print error
	
				cout << "ERROR: The cards cannot be dealt until they are shuffled. Returning to main menu..." << endl << endl;
	
				}
	
			//if the cards have been shuffled, conduct deal operations
	
			if ( shuffledFlag == true )
				{
		
				//reset the player totals from any previous deals
	
				resetTotals ( playersPointer, numberOfPlayers );
	
				//deal cards to the players
	
				cardsDealt = dealCards ( shuffledPointer, playersPointer, numberOfPlayers );
	
				//deal a card into the discard pile
	
				cardsDealt = dealToDiscard ( shuffledPointer, discardPointer, cardsDealt );
	
				//deal the remaining cards into the stock pile
	
				dealToStock ( shuffledPointer, stockPointer, cardsDealt );
	
				//loop through deal options until user quits to main menu
	
				while ( loopThroughMenu == true )
					{
	
					//print menu for showing the deal
		
					cout << "The cards have been dealt. Select an option: " << endl << endl;
		
					cout << "<1> Display players" << endl;
					cout << "<2> Display discard and stock piles" << endl;
					cout << "<3> Return to main menu" << endl << endl;			
		
					cout << "Enter your selection: ";
		
					//take user input
		
					cin >> userInput;
		
					cout << endl;
		
		
					//if instructed, show players
	
					if ( userInput == '1' )
						{
		
						cout << "The players are: " << endl << endl;
	
						printPlayers ( playersPointer, numberOfPlayers );	
	
						cout << "Returning to deal menu..." << endl << endl;
	
						}
	
					//if instructed, show stock and discard
	
					if ( userInput == '2' )
						{
			
						//show discard
	
						cout << "The discard pile contains: " << endl << endl;
			
						cout << "Card 1: " << endl;
	
						outputCardInformation ( discardPointer );
	
						//show stock
	
						cout << "The stock pile contains: " << endl << endl;
	
						//loop over however many cards there are in the stock (52-cardsDealt)
						
						card* stockReset = stockPointer;
	
						for ( int index = 0 ; index < (52 - cardsDealt ); index++ )
							{
		
							cout << "Card " << index+1 << ":" << endl;
	
							outputCardInformation( stockPointer);
	
							cout << endl;
	
							stockPointer++;
	
							}
						
						stockPointer = stockReset;
	
						cout << "Returning to deal menu..." << endl << endl;
	
						}
	
					//if instructed, return to main menu
	
					if ( userInput == '3' )
						{
	
						cout << "Returning to main menu..." << endl << endl;
	
						loopThroughMenu = false;
	
						}
		
					}
			
				}
	
			}
	
		//if prompted, quit program
	
		if ( userInput == '5' )
			{
	
			//print user message
	
			cout << "Thank you for using the card game program. Press any key to quit: " ;
	
			cin >> userInput;
	
			//deallocate the remaining dynamic memory
	
				//deallocate data members of main arrays
	
				deallocateDeck ( unshuffledPointer );
				deallocateDeck ( shuffledPointer );
				deallocateDeck ( stockPointer );
				deallocateDeck ( discardPointer );
				deallocatePlayers ( playersPointer, numberOfPlayers ) ;
	
				//deallocate main arrays
	
				delete [] unshuffledPointer;
				delete [] shuffledPointer;
				delete [] stockPointer;
				delete [] discardPointer;
				delete [] playersPointer;
	
				//null main arrays
	
				unshuffledPointer = NULL;
				shuffledPointer = NULL;
				stockPointer = NULL;
				discardPointer = NULL;
				playersPointer = NULL;
	
			//return 0
	
			return 0;
	
			}
	
		//reset loopThroughMenu
	
		loopThroughMenu = true;
	
		}

}

//Function Implementations

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
	
	//declare variables

	int index;

	//set initial value for name

	(*playerPointer).name = new char [ strLen("first last") + 1 ];

	strCopy ( (*playerPointer).name, "first last" );
	
	//set initial value for total

	(*playerPointer).total = 0;

	//set initial values for hand

		//allocate memory for hand

		(*playerPointer).hand = new card [3];

		//create reset pointer

		card* resetPointer = (*playerPointer).hand;

		//give each card in the hand initial values	

		for ( index = 0; index < 3; index++ )
			{
	
			makeACard ( (*playerPointer).hand );

			(*playerPointer).hand++;

			}

		//reset the hand pointer to the beginning of the hand

		(*playerPointer).hand = resetPointer;

}

void initializeCards ( card* targetDeck )
{
	
	//declare variables

	int index;

	//initialize unshuffled and shuffled arrays

	for ( index = 0; index < 52; index++ )
		{
	
		makeACard ( targetDeck );

		targetDeck++;

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

void modifyLocation ( card* targetPointer, char* namePointer, int locationType )
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

	if ( locationType == 2 )
		{
	
		//deallocate old string

		delete [] (*targetPointer).location;

		//allocate new string

		(*targetPointer).location = new char [ strLen("discard") + 1 ];
	
		//copy value

		strCopy ( (*targetPointer).location, "discard" );

		}

	if ( locationType == 3 )
		{
	
		//deallocate old string

		delete [] (*targetPointer).location;

		//allocate new string

		(*targetPointer).location = new char [ strLen("stock") + 1 ];
	
		//copy value

		strCopy ( (*targetPointer).location, "stock" );

		}

	if ( locationType == 4 )
		{
	
		//deallocate old string

		delete [] (*targetPointer).location;

		//allocate new string

		(*targetPointer).location = new char [ strLen(namePointer) + 1 ];
	
		//copy value

		strCopy ( (*targetPointer).location, namePointer );

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
	
		modifyLocation ( unshuffledPointer, "dummy", 0 );

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


int howManyPlayers ( )
{

	//declare variables

	int numberOfPlayers;
	bool loopUntilValid = false;

	//prompt the user until she gives a valid input

	while ( loopUntilValid == false )
		{
	
		//print user prompt and take user input
	
		cout << "Enter the number of players: ";

		cin >> numberOfPlayers;
	
		cout << endl;
	
		//if user input was invalid, print an error message

		if ( numberOfPlayers > 8 || numberOfPlayers < 2 )
			{
	
			cout << "ERROR: You must specify a number of players between 2 and 8, inclusive." << endl << endl ;

			}

		//if user input was valid, leave the loop

		if ( numberOfPlayers >= 2 && numberOfPlayers <= 8 )
			{
	
			loopUntilValid = true;

			}

		}

	//return value

	return numberOfPlayers;

}

void getPlayers ( ifstream &fin, player* playersPointer, int numberOfPlayers )
{
	
	//declare variables

	int index;
	char* tempOne = new char[50];
	char* tempTwo = new char[50];

	//prompt user for filename

	cout << "Enter player information datafile: " ;
	
	cin >> tempOne;

	cout << endl;

	//put filename in exactly sized array

	char* filename = new char [ strLen(tempOne) + 1 ];
	
	strCopy ( filename, tempOne );

	//clear file

	fin.clear();

	//open file

	fin.open ( filename );

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

	//deallocate dynamic memory

	delete [] tempOne;
	delete [] tempTwo;
	delete [] filename;

	//null pointers

	tempOne = NULL;
	tempTwo = NULL;
	filename = NULL;

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

		modifyLocation ( shuffledPointer, "dummy", 1 );

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
	cout << "Card location: " << (*targetPointer).location << "   " << endl;

}

void outputPlayerInformation ( player* targetPointer )
{
	
	//declare variables

	int index;

	//print information for each data member of target player to console

	cout << "Player's name: " << (*targetPointer).name << "   ";

	cout << "Player's total score: " << (*targetPointer).total << endl;

	//print the three cards in their hand

	card* resetPointer = (*targetPointer).hand;

	for ( index = 0; index < 3; index++ )
		{
	
		//print a card

		cout << "Card " << index + 1 << ": ";

		outputCardInformation ( (*targetPointer).hand );

		//move to the next card

		(*targetPointer).hand++;

		}

	//reset hand pointer to original position

	(*targetPointer).hand = resetPointer;

	cout << endl;

}

void printDeck ( card* deckLocation)
{
	
	//declare variables

	int index;

	//loop over the whole deck, printing each card to the screen

	for ( index = 0; index < 52; index++ )
		{
	
		//print a card
	
		cout << "Card " << index + 1 << ":" << endl;
	
		outputCardInformation ( deckLocation );

		//move to the next card

		deckLocation++;

		}

	cout << endl;

}

void printPlayers ( player* playersLocation, int numberOfPlayers )
{

	//declare variables
	
	int index;

	//loop over all players, printing each player's information to the screen

	for ( index = 0; index < numberOfPlayers; index++ )
		{
	
		//print a player

		cout << "Player " << index + 1 << ":" << endl;
	
		outputPlayerInformation ( playersLocation );

		//move to the next player

		playersLocation++;

		}

}

void deallocateCard ( card* targetCard )
{

		//deallocate data members

		delete [] (*targetCard).suit;

		delete [] (*targetCard).rank;

		delete [] (*targetCard).location;

		//set data member pointers to null

		(*targetCard).suit = NULL;

		(*targetCard).rank = NULL;

		(*targetCard).location = NULL;

}

void deallocateDeck ( card* targetDeck )
{
	
	//declare variables

	int index;

	//deallocate each data member of each card

	for ( index = 0 ; index < 52 ; index++ )
		{
	
		//deallocate a card

		deallocateCard ( targetDeck );

		//move to the next card

		targetDeck++;

		}

}

void deallocatePlayers ( player* playersPointer, int numberOfPlayers )
{
	
	//declare variables

	int outerIndex;
	int innerIndex;

	//deallocate each name and each hand in each player

	for ( outerIndex = 0 ; outerIndex < numberOfPlayers ; outerIndex++ )
		{
	
		//deallocate name array

			//deallocate name array

			delete [] (*playersPointer).name;

			//set pointer to null

			(*playersPointer).name = NULL;

		//deallocate hand

			//create reset pointer for player's hand
	
			card* resetHand = (*playersPointer).hand;
	
			//deallocate data members of cards in hand
	
			for ( innerIndex = 0; innerIndex < 3; innerIndex++ )
				{
		
				deallocateCard ( (*playersPointer).hand );
	
				(*playersPointer).hand++;
	
				}
	
			//reset hand pointer back to spot 0
	
			(*playersPointer).hand = resetHand;
	
			//deallocate hand itself
	
			delete [] (*playersPointer).hand;
	
			//set pointer for hand to null
	
			(*playersPointer).hand = NULL;

		//move to the next player

		playersPointer++;

		}

}

void resetTotals ( player* playersPointer, int numberOfPlayers )
{
	
	//declare variables

	int index;

	//loop over each player, setting total back to 0

	for ( index = 0 ; index < numberOfPlayers ; index++ )
		{
	
		(*playersPointer).total = 0;

		playersPointer++;

		}

}

int dealCards ( card* shuffledPointer, player* playersPointer, int numberOfPlayers )
{

	//declare variables

	int outerIndex;
	int innerIndex;
	int cardsDealt = 0;

	player* playersReset = playersPointer;

	//going down the deck, deal a card to each player 3 times

	for ( outerIndex = 0; outerIndex < 3; outerIndex ++ )
		{

		for ( innerIndex = 0; innerIndex < numberOfPlayers; innerIndex++ )
			{
	
			//if the player has at least one card already, start by moving to the next space in her hand
	
			if ( outerIndex > 0 )
				{
	
				(*playersPointer).hand++;

				}

			//copy the card information

			copyCard ( (*playersPointer).hand , shuffledPointer );

			//update the card's location

			modifyLocation ( (*playersPointer).hand, (*playersPointer).name, 4 );

			//update the player's total

			(*playersPointer).total += (*shuffledPointer).cardValue;

			//after the player has been dealt her third card, move her hand pointer back to its original location

			if ( outerIndex == 2 )
				{
	
				(*playersPointer).hand--;
				(*playersPointer).hand--;

				}

			//move to next player and next card in the deck

			playersPointer++;			

			shuffledPointer++;

			//increment cardsDealt

			cardsDealt++;

			}

		//after everyone has been dealt a card, go back to the first player

		playersPointer = playersReset;

		}

	//return the number of cards that have been dealt to players

	return cardsDealt;

}

int dealToDiscard ( card* shuffledPointer, card* discardPointer, int cardsDealt )
{
	
	//declare variables

	int index;

	//loop shuffledpointer past the cards that have already been dealt

	for ( index = 0 ; index < cardsDealt; index++ )
		{
	
		shuffledPointer++;

		}
	
	//deal the next card into the discard pile

	copyCard ( discardPointer, shuffledPointer );

	//update the card's location
	
	modifyLocation ( discardPointer, "dummy", 2 );

	//increment cards dealt

	cardsDealt++;

	//return number of cards dealt

	return cardsDealt;

}

void dealToStock ( card* shuffledPointer, card* stockPointer, int cardsDealt )
{
	
	//declare variables

	int index;

	//loop shuffledPointer past the cards that have already been dealt

	for ( index = 0 ; index < cardsDealt ; index++ )
		{
	
		shuffledPointer++;

		}

	//deal the remaining cards into the stock pile

	for ( index = cardsDealt ; index < 52 ; index++ )
		{
	
		//deal a card

		copyCard ( stockPointer, shuffledPointer );

		//update card location

		modifyLocation ( stockPointer, "dummy", 3 );

		//move to the next location in the stock and shuffled piles

		stockPointer++;

		shuffledPointer++;

		}

}
