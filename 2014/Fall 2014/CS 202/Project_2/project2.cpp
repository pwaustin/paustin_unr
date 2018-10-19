
        /*****************************************************************************************/

        /* PROGRAM: project2.cpp (Card deal program with structs - CS 202 Project 2 )

        /*                                                                                       */

        /* AUTHOR: Patrick Austin 

        /*                                                                                       */

        /* DATE: 11 September 2014

        /*                                                                                       */

        /* REVISIONS: revision of project1.cpp (Card shuffle program - CS 202 Project 1 )

        /*                                                                                       */

        /* PURPOSE: Reads a deck of cards from a data file. Can write the unshuffled deck to the
		    screen or output the shuffled deck into another data file. Can also create a full game state 
			for a game of SCAT at the point immediately after the deal has been completed and show/track
			disposition and state of each card therein. Uses structs for cards and players. 

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

struct player { char name[50]; int total; card hand[3]; } ;

//Function Prototypes

        /**************************************************************/

        /* FUNCTION: strLen                                                                 */

        /*                                                                                      */

        /* PURPOSE: counts the number of characters in a c-style string and returns the number.
			used by strCat function.

        /*                                                                             

        /**************************************************************/

	int strLen ( char arr[] );

        /**************************************************************/

        /* FUNCTION: strCat                                                                */

        /*                                                                                      */

        /* PURPOSE: appends the contents of the second string onto the end of the first string,
			with a space in between them.

        /*                                                                             

        /**************************************************************/

	void strCat ( char first[], char second[] );

        /**************************************************************/

        /* FUNCTION: strCopy                                                                */

        /*                                                                                      */

        /* PURPOSE: overwrites the value of dest string with the contents of source string.

        /*                                                                             

        /**************************************************************/


	void strCopy ( char src[], char dest[] );

        /**************************************************************/

        /* FUNCTION: makeACard                                                               */

        /*                                                                                      */

        /* PURPOSE: initializes target card with default values in all data member fields.

        /*                                                                             

        /**************************************************************/

	void makeACard ( card &target );

        /**************************************************************/

        /* FUNCTION: makeAPlayer                                                              */

        /*                                                                                      */

        /* PURPOSE: initializes target player with default values in all data member fields -
			calls makeACard to initialize the values for the cards in the player's hand

        /*                                                                             

        /**************************************************************/

	void makeAPlayer ( player &target );

        /**************************************************************/

        /* FUNCTION: initializeGame                                                              */

        /*                                                                                      */

        /* PURPOSE: uses looping of makeACard and makeAPlayer functions to set all data members of all players
			and cards relevant to the program to default/initial values

        /*                                                                             

        /**************************************************************/

	void initializeGame ( card unshuffled[][RANKS_CAPACITY], card toBeShuffled[], card shuffled[], card discard[], card stock[], player players[] );

        /**************************************************************/

        /* FUNCTION: modifyLocation                                                             */

        /*                                                                                      */

        /* PURPOSE: changes the value of target card's location based on the locationType parameter
			receieved. If the card's location is being changed to a player name, that c-string should be
			sent as the name parameter- otherwise the name parameter is not used and a dummy value can be sent.

        /*                                                                             

        /**************************************************************/

	void modifyLocation ( card &target, int locationType, char name[] );

	    /**************************************************************/

        /* FUNCTION: addCardFromFile                                                             */

        /*                                                                                      */

        /* PURPOSE: using the values taken in from the data file, puts the suit, rank, and card value
			into the initial 2D card array at the location specified by the parameters

        /*                                                                             

        /**************************************************************/

	void addCardFromFile ( card unshuffled[][RANKS_CAPACITY], char tempOne[], char tempTwo[], int tempInt, int suitIndex, int rankIndex );

        /**************************************************************/

        /* FUNCTION: getUnshuffledCards                                                           */

        /*                                                                                      */

        /* PURPOSE: loops through the data file, reading in initial card values. Uses 
			function addCardFromFile to put each card into the initial 2D card array.

        /*                                                                             

        /**************************************************************/

	void getUnshuffledCards ( card arr[][RANKS_CAPACITY], ifstream &fin );

        /**************************************************************/

        /* FUNCTION: getPlayers                                                            */

        /*                                                                                      */

        /* PURPOSE: reads player names into the player array from the data file

        /*                                                                             

        /**************************************************************/

	void getPlayers ( player players[], ifstream &fin );

        /**************************************************************/

        /* FUNCTION: printUnshuffledCards                                                              */

        /*                                                                                      */

        /* PURPOSE: prints the unshuffled cards stored in the initial 2D card array to the 
		console using cout

        /*                                                                             

        /**************************************************************/

	void printUnshuffledCards ( card arr[][RANKS_CAPACITY] );

        /**************************************************************/

        /* FUNCTION: transferCards                                                          */

        /*                                                                                      */

        /* PURPOSE: copies the cards in the initial 2D unshuffled card array into 
			a 1D array that will be used by the shuffle

        /*                                                                             

        /**************************************************************/

	void transferCards ( card unshuffled[][RANKS_CAPACITY], card shuffled[] );

        /**************************************************************/

        /* FUNCTION: shuffleCards                                                            */

        /*                                                                                      */

        /* PURPOSE: takes the 1D unshuffled card array and shuffles the cards into a
			second, shuffled 1D array

        /*                                                                             

        /**************************************************************/

	void shuffleCards ( card toBeShuffled[], card shuffled[] );

        /**************************************************************/

        /* FUNCTION: copyCard                                                          */

        /*                                                                                      */

        /* PURPOSE: copies the values for the data members of the source card into the values of
			destination card
        /*                                                                             

        /**************************************************************/

	void copyCard ( card src, card &dest );

        /**************************************************************/

        /* FUNCTION: dealCards                                                             */

        /*                                                                                      */

        /* PURPOSE: handles card dealing operation for a game of SCAT - copies cards from the shuffled
			array of cards into the player's hands, the discard pile, and the stock

        /*                                                                             

        /**************************************************************/

	void dealCards ( card shuffled[], player players[], card discard[], card stock[] );

        /**************************************************************/

        /* FUNCTION: outputCardInformation                                                              */

        /*                                                                                      */

        /* PURPOSE: prints the information from each data member of target card to console. Used
			for full deal diagnostic.

        /*                                                                             

        /**************************************************************/

	void outputCardInformation ( card target );

        /**************************************************************/

        /* FUNCTION: outputPlayerInformation                                                             */

        /*                                                                                      */

        /* PURPOSE: prints the information from each data member of target player to console.
			calls on outputCardInformation function to show player hands. Used for full deal
			diagnostic.

        /*                                                                             

        /**************************************************************/

	void outputPlayerInformation ( player target );

        /**************************************************************/

        /* FUNCTION: showDealAbbreviated                                                             */

        /*                                                                                      */

        /* PURPOSE: prints simple and straightforward information about the deal to console, nicely
			formatted.

        /*                                                                             

        /**************************************************************/

	void showDealAbbreviated ( card shuffled[], player players[], card discard[], card stock[] );

        /**************************************************************/

        /* FUNCTION: showFullDeal                                                              */

        /*                                                                                      */

        /* PURPOSE: prints full diagnostic information about the deal to console - the disposition
			of each data member for each player, the cards in their hands, and the cards in the stock
			and discard piles. This is a huge wall of text, so the function is only called if the
			user opts to see it.

        /*                                                                             

        /**************************************************************/

	void showFullDeal ( card shuffled[], player players[], card discard[], card stock[] );

        /**************************************************************/

        /* FUNCTION: outputShuffled                                                             */

        /*                                                                                      */

        /* PURPOSE: writes the contents of the shuffled deck to a data file, called
		shuffled_cards.txt

        /*                                                                             

        /**************************************************************/

	void outputShuffled ( card arr[], ofstream &fout );


//Main Program

int main()
{

	//declare variables

	card unshuffledCards[SUITS_CAPACITY][RANKS_CAPACITY];

	card toBeShuffledCards[CARD_CAPACITY];

	card shuffledCards[CARD_CAPACITY];

	card discardPile[CARD_CAPACITY];

	card stockPile[CARD_CAPACITY];

	player players[4];

	char userInput = '0';

	bool loopThroughMenu = true;

	bool shuffledFlag = false;

	ifstream fin;

	ofstream fout;

	//print welcome message

	cout << "Welcome to the CS 202 card game program." << endl << endl;

	//set all player and card array values to defaults

	initializeGame ( unshuffledCards, toBeShuffledCards, shuffledCards, discardPile, stockPile, players ) ;

	//open unshuffled cards file and read in values
	//function: getUnshuffledCards

	getUnshuffledCards ( unshuffledCards, fin );

	//copy unshuffled cards to 'to be shuffled' array
	//function: copyCards

	transferCards ( unshuffledCards, toBeShuffledCards );

	//get players

	getPlayers ( players, fin );

	//loop back to main menu until user quits program

	while ( loopThroughMenu == true )
	{

	//reset user input

	userInput = '0';

	//print menu

		cout << "Select an option:" << endl << endl;

		cout << "1. Display unshuffled cards" << endl;

		cout << "2. Shuffle cards" << endl;

		cout << "3. Write shuffled cards to file" << endl;

		cout << "4. Deal cards" << endl;

		cout << "5. Quit card game program" << endl << endl;

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

		//return to main menu

			//print message

			cout << "Returning to main menu... " << endl << endl;

	   }

	//if prompted, shuffle deck

	if ( userInput == '2' )
	   {

		//conduct shuffling operation
		//function: shuffleCards

		shuffleCards ( toBeShuffledCards, shuffledCards );

		shuffledFlag = true;

		//return to main menu

			//print message

			cout << "The cards have been shuffled. Returning to main menu... " << endl << endl ;

	   }

	//if prompted, write shuffled deck to file

	if ( userInput == '3' )
	   {

		if ( shuffledFlag == false )
		{
	
		//print error

		cout << "ERROR: The cards have not yet been shuffled. Returning to main menu..." << endl << endl;

		}

		if ( shuffledFlag == true )
		{

		//conduct file output operation
		//function: outputShuffled

		outputShuffled ( shuffledCards, fout );

		//return to main menu

			cout << "The cards have been printed to shuffled_cards.txt. Returning to main menu... " << endl << endl ;

		}

	   }

	//if prompted, deal cards

	if ( userInput == '4' )
		{
	
		 if ( shuffledFlag == false )
		 {
	
		 //print error

		 cout << "ERROR: The cards cannot be dealt until they are shuffled. Returning to main menu..." << endl << endl;

		 }

		 if ( shuffledFlag == true )
		 {
	
		 //handle card dealing operations

		 dealCards ( shuffledCards, players, discardPile, stockPile );

		 //output simple dealing message

		 showDealAbbreviated ( shuffledCards, players, discardPile, stockPile );

		 //print prompt for full diagnostic

		 cout << "To see complete game state diagnostic information, press 1. To return to the main menu, press any other key: " ;

		 cin >> userInput;

		 cout << endl;

		 if ( userInput == '1' )
			{
	
			//show full deal diagnostic

			showFullDeal ( shuffledCards, players, discardPile, stockPile );

			}

		 //print user message

		 cout << "Returning to main menu... " << endl << endl;

		}

		}

	//if prompted, quit program

	if ( userInput == '5' )
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

int strLen ( char arr[] )
{
	
	int index = 0;
	
	while ( arr[index] != '\0' )
		{
		
		index++;
	
		}
	
	return index;

}

void strCat ( char first[], char second[] )
{
	
	int srcIndex = 0;
	int destIndex = strLen ( first );
	
	first[destIndex] = ' ';
	destIndex++;
	
	while ( second[srcIndex] != '\0' )
		{
		
		first[destIndex] = second[srcIndex];
		destIndex++;
		srcIndex++;
	
		}
	
		first[destIndex] = '\0';

}

void strCopy( char src[], char dest[] )
{
	
	int index = 0;

	while ( src[index] != '\0' )
		{
	
		dest[index] = src[index];

		index++;

		}

	dest[index] = '\0';

}

void makeACard ( card &target )
{
	
	//declare variables

	char suit[]     = "suit" ;
	char rank[]     = "rank" ;
	char location[] = "location";
	
	//set initial value for suit
	
	strCopy ( suit, target.suit );
	
	//set initial value for rank

	strCopy ( rank, target.rank );
	
	//set initial value for cvalue

	target.cardValue = 0;
	
	//set initial value for location

	strCopy ( location, target.location );

}

void makeAPlayer ( player &target )
{
	
	//declare variables

	char name[] = "first last" ;
	
	//set initial value for name

	strCopy ( name, target.name );
	
	//set initial value for total

	target.total = 0;
	
	//set initial values for hand

	makeACard ( target.hand[0] );
	makeACard ( target.hand[1] );
	makeACard ( target.hand[2] );

}

void initializeGame ( card unshuffled[][RANKS_CAPACITY], card toBeShuffled[], card shuffled[], card discard[], card stock[], player players[] )
{
	
	//declare variables

	int index;
	int innerIndex;

	//initialize unshuffled array

	for ( index = 0 ; index < 4; index++ )
		{
	
		for ( innerIndex = 0 ; innerIndex < 13; innerIndex++ )
			{
	
			makeACard ( unshuffled[index][innerIndex] );

			}

		}

	//initialize toBeShuffled array

	for ( index = 0; index < 52; index++ )
		{
	
		makeACard ( toBeShuffled[index] );

		}

	//initialize shuffled array

	for ( index = 0; index < 52; index++ )
		{
	
		makeACard ( shuffled[index] );

		}

	//initialize discard array

	for ( index = 0; index < 52; index++ )
		{
	
		makeACard ( discard[index] );

		}

	//initialize stock array

	for ( index = 0; index < 52; index++ )
		{
	
		makeACard ( stock[index] );

		}

	//initialize players array

	for ( index = 0; index < 4; index++ )
		{
	
		makeAPlayer ( players[index] );

		}

}

void modifyLocation ( card &target, int locationType, char name[] )
{
	
	//declare variables

	char unshuffled[] = "unshuffled" ;
	char shuffled[]   = "shuffled" ;
	char stock[]      = "stock" ;
	char discard[]    = "discard" ;

	//assign location according to type requested in locationType parameter		
	
	if ( locationType == 0 )
		{
		
		strCopy ( unshuffled, target.location );
	
		}
	
	if ( locationType == 1 )
		{
		
		strCopy ( shuffled, target.location );
	
		}
	
	if ( locationType == 2 )
		{
		
		strCopy ( name, target.location );
	
		}
	
	if ( locationType == 3 )
		{
		
		strCopy ( discard, target.location );
	
		}
	
	if ( locationType == 4 )
		{
		
		strCopy ( stock, target.location );
	
		}

}

void addCardFromFile ( card unshuffled[][RANKS_CAPACITY], char tempOne[], char tempTwo[], int tempInt, int suitIndex, int rankIndex )
{

	//put suit value into card

	strCopy ( tempOne, unshuffled[suitIndex][rankIndex].suit );

	//put rank value into card

	strCopy ( tempTwo, unshuffled[suitIndex][rankIndex].rank );

	//put cardValue into the card

	unshuffled[suitIndex][rankIndex].cardValue = tempInt;

	//set card location to "unshuffled"

	modifyLocation ( unshuffled[suitIndex][rankIndex], 0, unshuffled[suitIndex][rankIndex].suit );

}

void getUnshuffledCards ( card arr[][RANKS_CAPACITY], ifstream &fin )
{
	
	//declare variables

	char tempOne[STRING_CAPACITY];
	char tempTwo[STRING_CAPACITY];
	int  tempInt;

	int rankIndex;
	int suitIndex;

	//prompt for filename

	//clear file

	fin.clear();

	//open file

	fin.open ( "unshuffled_cards.txt" );

	//loop over the whole array

	for ( suitIndex = 0 ; suitIndex < 4 ; suitIndex++ )
		{

		for ( rankIndex = 0 ; rankIndex < 13 ; rankIndex++ )
			{
	
			//read in a rank, then a suit, then cardValue
	
			fin >> tempOne;

			fin >> tempTwo;

			fin >> tempInt;

			//copy the card info into the main array

			addCardFromFile ( arr, tempOne, tempTwo, tempInt, suitIndex, rankIndex );

			}

		}

	//close file

	fin.close();

}

void getPlayers ( player players[], ifstream &fin )
{
	
	//declare variables

	char tempOne[50];
	char tempTwo[50];

	int index;

	//prompt for filename

	//clear file

	fin.clear();

	//open file

	fin.open ( "players.txt" );

	//take values, insert them into array

	for ( index = 0 ; index < 4 ; index++ )
		{
	
		fin >> tempOne;
		fin >> tempTwo;

		strCat ( tempOne, tempTwo );

		strCopy( tempOne, players[index].name );

		}

	//close file

	fin.close();

}

void printUnshuffledCards ( card arr[][RANKS_CAPACITY] )
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

			cout << arr[suitIndex][rankIndex].suit << ' ' << arr[suitIndex][rankIndex].rank ;

			cout << ' ' ;

			}

			//end line after listing 13 values

			cout << endl;

		}

	//end line once finished printing values

	cout << endl;

}

void transferCards ( card unshuffled[][RANKS_CAPACITY], card toBeShuffled[] )
{

	//declare variables	
	
	int suitIndex;
	int rankIndex;
	int cardIndex = 0;	

	//loop over array - copy values and update card location

	for ( suitIndex = 0 ; suitIndex < 4 ; suitIndex ++ )
		{

		for ( rankIndex = 0 ; rankIndex < 13 ; rankIndex++ )
			{

			copyCard ( unshuffled[suitIndex][rankIndex], toBeShuffled[cardIndex] );

			modifyLocation ( toBeShuffled[cardIndex], 0, toBeShuffled[0].suit );

			cardIndex++;

			}
	
		}

}

void shuffleCards ( card toBeShuffled[], card shuffled[] )
{

	//declare variables
	
	int copyIndex;
	int index = 51;
	int random;
	
	card temp;

	//seed random number
	
	srand ( time(NULL) );

	//copy contents of toBeShuffled into shuffled, update card location

	for ( copyIndex = 0 ; copyIndex < 52 ; copyIndex++ )
		{
	
		copyCard ( toBeShuffled[copyIndex], shuffled[copyIndex]) ;

		modifyLocation ( shuffled[copyIndex], 1, shuffled[0].suit );

		}
	
	//loop from the top to all but the final index position
	
	while ( index > 1 )
		{
		
		//get a random number from 0-index
	
		random = rand() % index ;
	
		//swap the cards at the index position and the random number position
	
		copyCard ( shuffled[index], temp );

		copyCard ( shuffled[random], shuffled[index] );

		copyCard ( temp, shuffled[random] );
	
		//decrement

		index--;
	
		}

}

void copyCard ( card src, card &dest )
{
	
	//copy suit

	strCopy ( src.suit, dest.suit );

	//copy rank
	
	strCopy ( src.rank, dest.rank );

	//copy cvalue

	dest.cardValue = src.cardValue;

	//copy location

	strCopy ( src.location, dest.location );

}

void dealCards ( card shuffled[], player players[], card discard[], card stock[] )
{
	
	//declare variables
	
	int index;
	int innerIndex;
	int count = 0;
	int stockCount = 0;
	
	//reset total values from any previous deals

	for ( index = 0 ; index < 4; index++ )
		{
	
		players[index].total = 0;

		}

	//player 0 deals. deal 1 card to each of the players, in descending order from player 3 to player 0, three times

	for ( index = 0 ; index < 3; index++ )
		{

		for ( innerIndex = 3 ; innerIndex > -1 ; innerIndex -- )
			{

			//copy the card into the player's hand

			copyCard( shuffled[count], players[innerIndex].hand[index] );
		
			//increment count

			count++;

			//change the card's location to the player's hand

			modifyLocation ( players[innerIndex].hand[index], 2, players[innerIndex].name ); 

			//update the player's score total using the card's value

			players[innerIndex].total += players[innerIndex].hand[index].cardValue ;

			}

		}

	//put next card at the start of the discard pile, update count and location

	copyCard( shuffled[count], discard[0] );
	count++;
	modifyLocation ( discard[0], 3, discard[0].suit );

	//put remaining cards in the stock, updating location, until you reach the end of the deck

	while ( count < 52 )
		{
	
		copyCard ( shuffled[count], stock[stockCount] );
		modifyLocation ( stock[stockCount], 4, stock[0].suit );

		count++;
		stockCount++;

		}

}

void outputCardInformation ( card target )
{
	
	//print information for each data member of target card to the console

	cout << "The card suit is     : " << target.suit << endl;
	cout << "The card rank is     : " << target.rank << endl;
	cout << "The card value is    : " << target.cardValue << endl;
	cout << "The card location is : " << target.location << endl << endl;

}

void outputPlayerInformation ( player target )
{
	
	int index;

	cout << "The player's name is: " << target.name << endl << endl;

	for ( index = 0; index < 3; index++ )
		{
		
		cout << "Card " << (index + 1) << " info:" << endl;

		outputCardInformation ( target.hand[index] );

		}

	cout << "The player's total score is: " << target.total << endl << endl;


}


void showDealAbbreviated ( card shuffled[], player players[], card discard[], card stock[] )
{
	int index;

	for ( index = 0 ; index < 4 ; index++ )
		{

		cout << players[index].name << " has been dealt: ";

		cout << players[index].hand[0].suit << " " << players[index].hand[0].rank << ", ";
		cout << players[index].hand[1].suit << " " << players[index].hand[1].rank << ", and ";
		cout << players[index].hand[2].suit << " " << players[index].hand[2].rank << "." << endl;

		//say value of player's hand

		cout << "The value of his/her starting hand is: " << players[index].total << "." << endl << endl;

		}

	//say card in discard pile

	cout << "The card " << discard[0].suit << " " << discard[0].rank << " has been placed in the discard pile. The remaining cards have been placed in the stock pile." << endl << endl;

}

void showFullDeal ( card shuffled[], player players[], card discard[], card stock[] )
{

	int index;

	//show the cards in each player's hand, then their total

	for ( index = 0; index < 4; index++ )
		{
	
		cout << "Player " << (index + 1 ) << " information:" << endl << endl;
	
		outputPlayerInformation ( players[index] );

		}

	//show the card in the discard pile

	cout << "The discard pile contains: " << endl << endl;

	outputCardInformation ( discard[0] );

	//show the cards in the stock pile

	cout << "The stock pile contains: " << endl << endl;

	for ( index = 0; index < 39; index++ )
		{
	
		outputCardInformation ( stock[index] );

		}

}

void outputShuffled ( card arr[], ofstream &fout )
{
	
	//declare variables
	
	int index;
	
	//open file
	
	fout.open ( "shuffled_cards.txt" );
	
	//print the strings
	
	for ( index = 0 ; index < 52 ; index++ )
		{
		
		fout << arr[index].suit << " " << arr[index].rank ;
		
		fout << endl;
	
		}
	
	//close file
	
	fout.close();

}

