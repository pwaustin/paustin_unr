#include <iostream>
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

void card::print() const
{
	
	cout << "Rank: " << rank << " Suit: " << suit << " Location: " << location << " Card value: " << cardValue << endl;

}

void card::copy(const card &src)
{

	//copy rank from source card to dest card

	strCopy( rank, src.rank );

	//copy suit from source card to dest card

	strCopy( suit, src.suit );

	//copy location from source card to dest card

	strCopy( location, src.location);

	//copy cardValue from source card to dest card

	cardValue = src.cardValue;

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

void player::print() const
{
	
	int index;

	//print name and total

	cout << "Name: " << name << " Total: " << total << endl;

	//print each card in the hand

	for ( index = 0; index < 3; index++ )
		{
	
		cout << name << "'s hand card " << index + 1 << ":" << endl;

		hand[index].print();

		}

}
