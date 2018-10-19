/** CS 302 Project 3 Question 13 - header for classes
@file myclass13.h
@author Patrick Austin
@date 2/21/2015 */

#include <cassert>
#include <fstream>
#include <iostream>
using namespace std;

const int MAX_STACK = 100;
const int MAX_REQUESTS = 20;
const int MAX_CITIES = 20;

	class node;

	/**
	Templated stack class. Used in implementation of map::isPath function. Adapted 
	from implementation in class textbook, "Data Abstraction & Problem Solving with C++, sixth ed".
	Supports maximum MAX_STACK number of items.

	Modified from problem 11/12 implementations to be traversable from the bottom up, as specified in
	the prompt. User can traverse from the bottom of the stack up, one item at a time, peeking at the values,
	using the cursor functions.
	*/

	template < class ItemType > class stack
		{

		private:

		ItemType items[MAX_STACK];
		int top;	
		int cursor;

		public:

		stack();
		bool isEmpty() const;
		bool push(const ItemType& newEntry);
		bool pop();
		ItemType peekAtTop() const;
		void initCursor();
		bool traverseToNext();
		ItemType peekAtCursor() const;

		};

	/**
	City class. Heavily involved in map class operations.

	Modified from problem 11/12 implementations to include flight number and flight cost data members,
	used in additional flight map operations, and set/gets for them.
	*/

	class city
		{

		public:

		city();
		void setName (const string);
		string getName() const;
		void setVisited (const bool);
		bool isVisited() const;
		void setFlightNumber ( const int );
		int getFlightNumber();
		void setFlightCost ( const int );
		int getFlightCost();

		private:

		string name;
		bool visited;
		int flightNumber;
		int flightCost;

		};

	/**
	namePair class. Contains origin and destination city; used in map operations.
	*/

	class namePair
		{

		private:
		city origin;
		city dest;

		public:

		void setOrigin(const city);
		city getOrigin() const;
		void setDest(const city);
		city getDest() const;

		};

	/**
	Map class. Conducts operations derived from user datafiles to determine if certain flights between
	cities are possible. Contains a flight map of linked nodes that represents the valid flights that
	are possible from a given city, and an array of paired requests for origin and destination cities.
	Format the datafiles as specified to insure proper operation. MAX_CITIES number of total cities in
	the flight map and MAX_CITIES number of requests allowed.

	Modified from problem 11 to feature an array of try-next pointers designed to make getAdjacentCity
	operation more efficient in some situations.

	Modified from problem 12 to support a flight map that includes flight numbers and flight costs. Has
	new function, printItinerary, which will put this information in the console should a flight path
	be found.
	*/

	class map
		{

		public:
	
		map();
		~map();
		bool isPath(const city origin, const city destination);
		bool isValidRequest(const int);
		bool isServicedCity( const city ) const;
		city getRequestOrigin(const int) const;
		city getRequestDestination(const int) const;
		int getNumRequests() const;

		private:

		node* adjacencyMap[MAX_CITIES];
		node* tryNext[MAX_CITIES];
		int numCities;
		stack<city>* path;
		namePair requests[MAX_REQUESTS];
		int numRequests;

		void clearTryNext();
		void markAllUnvisited();
		void markVisited( const city );
		city getAdjacentCity ( const city );
		void printItinerary();
		void readCityFile();
		void readFlightFile();
		void readRequestFile();

		};

	/**
	Node class. Used in map class flight map operations.

	Modified from problem 11/12 implementation to support the new data members of the city class, flight number and flight cost.
	*/

	class node
		{

		private:

		node(const string, const int, const int, node*);
		city data;
		node* next;
		friend class map;

		};

	/**
	Readin class. As specified by the prompt, used to simplify some file I/O processes.

	Modified from problem 11/12 implementation to support the new datafile format specified for flightFile.txt and the new data
	members of the city class, flight number and flight cost.
	*/

	class readin
		{

		public:
		string getName(ifstream&);
		namePair getNamePair(ifstream&);
		namePair getNamePairFlightFile(ifstream&);

		};

