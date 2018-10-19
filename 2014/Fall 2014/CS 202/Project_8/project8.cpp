
        /*****************************************************************************************/

        /* PROGRAM: project8.cpp (Card deal program with operator overload - CS 202 Project 8)

        /*                                                                                       */

        /* AUTHOR: Patrick Austin 

        /*                                                                                       */

        /* DATE: 28 October 2014

        /*                                                                                       */

        /* REVISIONS: revision of project7.cpp (Card deal program with copy constructor and const functions - CS 202 Project 7)

        /*                                                                                       */

        /* PURPOSE: Re-implements the usual scat program functionality - read in cards and players, shuffle and deal as per
		scat rules- using overloaded operators for the player and card classes. This significantly cleans up the
		main driver.

        /*****************************************************************************************/



//Header Files

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>
#include "my_strings.h"
#include "my_scat.h"
using namespace std;

//Function Prototypes

        /**************************************************************/

        /* FUNCTION: getUnshuffledCards                                                                */

        /*                                                                                      */

        /* PURPOSE: prompts user for filename containing unshuffled deck, then reads appropriate values
		into the unshuffled deck array.

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

	const int howManyPlayers ();

        /**************************************************************/

        /* FUNCTION: getPlayers                                                                 */

        /*                                                                                      */

        /* PURPOSE: opens the datafile specified by the filename parameter and reads the player values into the
		players array.

        /*                                                                                      */

        /**************************************************************/

	void getPlayers ( ifstream &fin, player* playersPointer, const int numberOfPlayers );

        /**************************************************************/

        /* FUNCTION: shuffleCards                                                               */

        /*                                                                                      */

        /* PURPOSE: conducts shuffling operation on shuffled cards array. Uses incrementing and resetting
		of pointers to handle "targetting" random cards for the shuffle. Uses a temp card for holding
		values during the card swap.

        /*                                                                                      */

        /**************************************************************/

	void shuffleCards ( card* shuffledPointer );

        /**************************************************************/

        /* FUNCTION: dealCards                                                   */

        /*                                                                                      */

        /* PURPOSE: Deals the cards to the players, the first step of the deal for the scat card game.
		As per the rules, deals a card from the top of the deck to each player, repeated 3 times. Returns
		the number of cards dealt out of the deck so far, for use in subsequent deal operations.

        /*                                                                                      */

        /**************************************************************/

	int dealCards ( card* shuffledPointer, player* playersPointer, const int numberOfPlayers );

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

	int index;

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

	//allocate memory for and initialize players

		//prompt for number of players

		numberOfPlayers = howManyPlayers();

		//allocate dynamic memory array for the number of players found

		player* playersPointer = new player[numberOfPlayers];

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
	
		cout << "<5> Show member function tests and quit card game program" << endl << endl;
	
		cout << "Enter your selection: " ;
	
		//accept menu navigation
	
		cin >> userInput;
	
		cout << endl;
	
		//if prompted, shuffle cards
	
		if ( userInput == '1' )
		   {
	
			//conduct shuffling operation:
	
				//copy the unshuffled deck into the shuffled deck

				for ( index = 0; index < 52; index++ )
					{
				
					//copy

					shuffledPointer[index] = unshuffledPointer[index];

					//update location

					shuffledPointer[index].setLocation("shuffled");

					}

				//shuffle the cards

				shuffleCards ( shuffledPointer );
	
				//set flag to indicate shuffling has taken place

				shuffledFlag = true;

			//return to main menu
	
			cout << "The cards have been shuffled. Returning to main menu... " << endl << endl ;
	
		   }
	
		//if prompted, print unshuffled deck
	
		if ( userInput == '2' )
			{
	
			cout << "The unshuffled deck contains: " << endl << endl;
	
			for ( index = 0; index < 52; index++ )
				{

				cout << "Card " << index + 1 << ":" << endl;

				cout << unshuffledPointer[index];

				}
	
			cout << endl << "Returning to main menu..." << endl << endl;
	
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
	
				for ( index = 0; index < 52; index++ )
					{

					cout << "Card " << index + 1 << ":" << endl;

					cout << shuffledPointer[index];

					}

				cout << endl << "Returning to main menu..." << endl << endl;
				
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
	
						for ( index = 0; index < numberOfPlayers; index++ )
							{

							cout << "Player " << index + 1 << ":" << endl;

							cout << playersPointer[index];

							}	
	
						cout << endl << "Returning to deal menu..." << endl << endl;
	
						}
	
					//if instructed, show stock and discard
	
					if ( userInput == '2' )
						{
			
						//show discard
	
						cout << "The discard pile contains: " << endl << endl;
			
						cout << "Card 1: " << endl;
	
						cout << (*discardPointer);

						cout << endl;
	
						//show stock
	
						cout << "The stock pile contains: " << endl << endl;
	
						//loop over however many cards there are in the stock (52-cardsDealt)
	
						for ( int index = 0 ; index < (52 - cardsDealt ) ; index++ )
							{
		
							cout << "Card " << index+1 << ":" << endl;
	
							cout << stockPointer[index];
	
							}
	
						cout << endl << "Returning to deal menu..." << endl << endl;
	
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
	
		//if prompted, quit program and run member function tests
	
		if ( userInput == '5' )
			{

			//brief code to demonstrate that the copy and parameterized constructors work properly:

			card temp1( "parameterized", "constructor", "used", 555 );

			card temp2 = temp1;

			cout << "Card made with parameterized constructor:" << endl;

			cout << temp1;

			cout << endl;

			cout << "Card made with copy constructor from the previous card:" << endl;

			cout << temp2;

			cout << endl;

			//brief code to demonstrate "<" and "<=" overloaded operators work properly- cards must be shuffled first:

			if ( shuffledFlag == false )
				{

				cout << "Shuffle the cards to enable < and <= overloaded operator tests." << endl << endl;

				}

			if ( shuffledFlag == true )
				{

				cout << "Comparing value of two cards using < and <= overloaded operators:" << endl << endl;

				cout << "Card 1 of shuffled deck: " << endl;

				cout << shuffledPointer[0] << endl;

				cout << "Card 2 of shuffled deck: " << endl;

				cout << shuffledPointer[1] << endl;

				cout << "Is card 1 less than card 2? ";

				if ( shuffledPointer[0] < shuffledPointer[1] )
					{

					cout << "Yes." << endl << endl;

					}

				else
					cout << "No." << endl << endl;

				cout << "Is card 1 less than or equal to card 2? ";

				if ( shuffledPointer[0] <= shuffledPointer[1] )
					{

					cout << "Yes." << endl << endl;

					}

				else
					cout << "No." << endl << endl;

				}

			//print user message
	
			cout << "Thank you for using the card game program. Press any key to quit: " ;
	
			cin >> userInput;
	
			//deallocate the remaining dynamic memory
	
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

void getUnshuffledCards ( ifstream &fin , card* unshuffledPointer )
{
	
	//declare variables

	char* tempOne = new char[50];
	char* filename;
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

		//read in a card
	
		fin >> unshuffledPointer[index];

		//update the card's location

		unshuffledPointer[index].setLocation("unshuffled");

		}

	//close file

	fin.close();

	//deallocate temp array

	delete [] tempOne;
	delete [] filename;

	//null temp array

	tempOne = NULL;
	filename = NULL;

}


const int howManyPlayers ( )
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

void getPlayers ( ifstream &fin, player* playersPointer, const int numberOfPlayers )
{
	
	//declare variables

	int index;
	char* tempOne = new char[50];

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
	
		fin >> playersPointer[index];

		}

	//close file

	fin.close();

	//deallocate dynamic memory

	delete [] tempOne;
	delete [] filename;

	//null pointers

	tempOne = NULL;
	filename = NULL;

}

void shuffleCards ( card* shuffledPointer )
{
	
	//declare variables
	
	card temp;
	int index;
	int random;

	//seed random number

	srand ( time(NULL) );

	//loop from the end to all but the first array position

	for ( index = 51; index > 1; index-- )
		{
	
		//get a random number from 0-index

		random = rand() % index;

		//swap the cards at index and random locations

		temp = shuffledPointer[index];

		shuffledPointer[index] = shuffledPointer[random];

		shuffledPointer[random] = temp;

		}

}

int dealCards ( card* shuffledPointer, player* playersPointer, const int numberOfPlayers )
{

	//declare variables

	int outerIndex;
	int innerIndex;
	int cardsDealt = 0;

	//reset the player totals from any previous deals
	
	for ( innerIndex = 0; innerIndex < numberOfPlayers; innerIndex++ )
		{
			
		playersPointer[innerIndex].setTotal(0);

		}

	//going down the deck, deal a card to each player 3 times round robin style

	for ( outerIndex = 0; outerIndex < 3; outerIndex ++ )
		{

		for ( innerIndex = 0; innerIndex < numberOfPlayers; innerIndex++ )
			{
	
			//copy the card

			card* handPointer = playersPointer[innerIndex].getHand();

			handPointer[outerIndex] = shuffledPointer[cardsDealt];

			//update the player's total - it will equal their previous total plus the value of the card they were just dealt

			playersPointer[innerIndex].setTotal( playersPointer[innerIndex].getTotal() + shuffledPointer[cardsDealt].getCardValue() );

			//update the location to the player's name

			handPointer[outerIndex].setLocation( playersPointer[innerIndex].getName() );

			//increment cards dealt

			cardsDealt++;

			}

		}

	//return the number of cards that have been dealt to players

	return cardsDealt;

}

int dealToDiscard ( card* shuffledPointer, card* discardPointer, int cardsDealt )
{
	
	//deal the next card into the discard pile

	discardPointer[0] = shuffledPointer[cardsDealt];

	//update the card's location
	
	discardPointer[0].setLocation("discard");

	//increment cards dealt

	cardsDealt++;

	//return number of cards dealt

	return cardsDealt;

}

void dealToStock ( card* shuffledPointer, card* stockPointer, int cardsDealt )
{
	
	//declare variables

	int index;
	int stockLocation = 0;

	//deal the remaining cards into the stock pile

	for ( index = cardsDealt ; index < 52 ; index++ )
		{
	
		//deal a card

		stockPointer[stockLocation] = shuffledPointer[index];

		//update card location

		stockPointer[stockLocation].setLocation("stock");

		//move to the next spot in the stock

		stockLocation++;

		}

}
