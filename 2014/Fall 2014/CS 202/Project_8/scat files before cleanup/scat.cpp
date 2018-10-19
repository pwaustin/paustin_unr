#include <iostream>
#include <fstream>
#include "my_strings.h"
#include "my_scat.h"
using namespace std;

card::card( const char* rankAddress , const char* locationAddress )
{

	//initialize rank

	rank = new char [50];

	strCopy( rank, rankAddress );

	//initialize suit

	suit = new char [50];

	strCopy ( suit, "suit" );

	//initialize location

	location = new char [50];

	strCopy ( location, locationAddress );

	//initialize cardvalue

	cardValue = 0;

}

card::card( const char* rankPtr, const char* suitPtr, const char* locPtr, const int val )
{

	//initialize rank

	rank = new char [50];

	strCopy ( rank, rankPtr );

	//initialize suit

	suit = new char [50];

	strCopy ( suit, suitPtr );

	//initialize location

	location = new char [50];

	strCopy ( location, locPtr );

	//intialize card value

	cardValue = val;

}

card::card( const card &src )
{

	//copy rank from source card to dest card

	rank = new char [50];

	strCopy( rank, src.rank );

	//copy suit from source card to dest card

	suit = new char[50];

	strCopy( suit, src.suit );

	//copy location from source card to dest card

	location = new char [50];

	strCopy( location, src.location );

	//copy cardValue from source card to dest card

	cardValue = src.cardValue;

}

card::~card()
{
	
	//deallocate rank

	delete [] rank;

	rank = NULL;

	//deallocate suit

	delete [] suit;

	suit = NULL;

	//deallocate location

	delete [] location;

	location = NULL;

	//set card value to 0

	cardValue = 0;

}

card card::operator= ( const card &src )
{

	//check if you're trying to assign a card to itself

	if ( this != &src )
		{

		//if not, clear to copy the values
	
		strCopy ( rank, src.rank );

		strCopy ( suit, src.suit );

		strCopy ( location, src.location );

		cardValue = src.cardValue;

		}

	//return "this" card

	return (*this);

}

bool card::operator< (const card &target) const
{

	//check to see if card value of this card is less than or equal to target card

	if ( cardValue < target.cardValue )
		{

		//if so, return true

		return true;

		}

	//otherwise, return false

	else
		return false;


}

void card::setRank(const char* target)
{
	
	strCopy ( rank, target );

}

void card::setSuit(const char* target)
{
	
	strCopy ( suit, target );

}

void card::setLocation(const char* target)
{
	
	strCopy ( location, target );

}

void card::setCardValue(const int target)
{
	
	cardValue = target;

}

const char* card::getRank() const
{
	
	return rank;

}

const char* card::getSuit() const
{
	
	return suit;
	
}

const char* card::getLocation() const
{

	return location;

}

const int card::getCardValue() const
{
	
	return cardValue;

}

bool operator<= ( const card &a, const card &b )
{

	//if a has a lesser cardvalue than b, return true

	if ( a.cardValue <= b.cardValue )
		{

		return true;

		}

	//otherwise, return false

	else
		return false;

}

ostream &operator<< ( ostream &out, const card &src )
{

	//print the data member information

	out << "Rank: " << src.rank << " Suit: " << src.suit << " Location: " << src.location << " Card value: " << src.cardValue << endl;

	//return the ostream object

	return out;

}

istream &operator>> ( istream &in, card &target )
{

	//read in the information

	in >> target.suit >> target.rank >> target.cardValue;
	
	//return the istream object

	return in;

}

player::player()
{
	
	//initialize name

	name = new char [50];

	strCopy ( name, "name" );

	//initialize total

	total = 0;

	//initialize hand

	hand = new card [3];

}

player::~player()
{
	
	delete [] name;

	delete [] hand;

}

void player::setName(const char* target)
{
	
	strCopy ( name, target );

}

void player::setTotal(const int target)
{
	
	//add target int to the player's total
	
	total += target;

}

void player::resetTotal()
{
	
	//reset player's total to 0

	total = 0;

}

void player::setHand(card* target)
{
	
	hand = target;

}

const char* player::getName() const
{
	
	return name;

}

const int player::getTotal() const
{
	
	return total;

}

card* player::getHand() const
{
	
	return hand;

}

ostream &operator<< ( ostream &out, const player &src )
{

	int index;

	//print name and total

	out << "Name: " << src.name << " Total: " << src.total << endl;

	//print each card in the hand

	for ( index = 0; index < 3; index++ )
		{
	
		out << src.name << "'s hand card " << index + 1 << ":" << endl;

		out << src.hand[index];

		}

	//return ostream object

	return out;

}

istream &operator>> ( istream &in, player &target )
{

	//declare temps

	char* tempOne = new char [50];
	char* tempTwo = new char [50];	

	//read in temps

	in >> tempOne >> tempTwo;

	//combine temps

	strCat ( tempOne, tempTwo );

	//copy temps to player name

	strCopy ( target.name, tempOne );

	//return istream object

	return in;

}
