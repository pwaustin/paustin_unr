#include <iostream>
#include "my_strings.h"
#include "my_scat.h"
using namespace std;

card::card()
{

	//initialize rank

	rank = new char [50];

	strCopy( rank, "rank" );

	//initialize suit

	suit = new char [50];

	strCopy ( suit, "suit" );

	//initialize location

	location = new char [50];

	strCopy ( location, "location" );

	//initialize cardvalue

	cardValue = 0;

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

void card::setRank(char* target)
{
	
	strCopy ( rank, target );

}

void card::setSuit(char* target)
{
	
	strCopy ( suit, target );

}

void card::setLocation(char* target)
{
	
	strCopy ( location, target );

}

void card::setCardValue(int target)
{
	
	cardValue = target;

}

char* card::getRank()
{
	
	return rank;

}

char* card::getSuit()
{
	
	return suit;
	
}

char* card::getLocation()
{

	return location;

}

int card::getCardValue()
{
	
	return cardValue;

}

void card::print()
{
	
	cout << "Rank: " << rank << " Suit: " << suit << " Location: " << location << " Card value: " << cardValue << endl;

}

void card::copy(card* src)
{

	//copy rank from source card to dest card

	strCopy( rank, (*src).rank );

	//copy suit from source card to dest card

	strCopy( suit, (*src).suit );

	//copy location from source card to dest card

	strCopy( location, (*src).location);

	//copy cardValue from source card to dest card

	cardValue = (*src).cardValue;

}

player::player( int target )
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

void player::setName(char* target)
{
	
	strCopy ( name, target );

}

void player::setTotal(int target)
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

char* player::getName()
{
	
	return name;

}

int player::getTotal()
{
	
	return total;

}

card* player::getHand()
{
	
	return hand;

}

void player::print()
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
