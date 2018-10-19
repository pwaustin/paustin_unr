/** CS 302 Project 3 Question 12 - header for classes
@file myclass12.h
@author Patrick Austin
@date 2/21/2015 */

#include <cassert>
#include <fstream>
#include <iostream>
using namespace std;

/**
@var MAX_STACK Max number of items for the stack class.
*/

const int MAX_STACK = 100;

/**
@var MAX_REQUESTS Max number of requested flight paths to check.
*/

const int MAX_REQUESTS = 20;

/**
@var MAX_CITIES Max number of cities that can be input into the flight map.
*/

const int MAX_CITIES = 20;

	class node;

	/**
	Templated stack class. Used in implementation of map::isPath function. Adapted 
	from implementation in class textbook, "Data Abstraction & Problem Solving with C++, sixth ed".
	Supports maximum MAX_STACK number of items.
	*/

	template < class ItemType > class stack
		{

		public:

		stack();
		bool isEmpty() const;
		bool push(const ItemType& newEntry);
		bool pop();
		ItemType peek() const;

		private:

		ItemType items[MAX_STACK];
		int top;

		};

	/**
	City class. Heavily involved in map class operations.
	*/

	class city
		{

		public:

		city();
		void setName (const string);
		string getName() const;
		void setVisited (const bool);
		bool isVisited() const;

		private:

		string name;
		bool visited;

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
	Format the datafiles as specified to insure proper operation; the user will be prompted for them
	when a map class object is created. MAX_CITIES number of total cities in the flight map and 
	MAX_REQUESTS number of requests allowed.

	Modified from problem 11 to feature an array of try-next pointers designed to make getAdjacentCity
	operation more efficient in some situations.
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
		namePair requests[MAX_REQUESTS];
		int numRequests;

		void clearTryNext();
		void markAllUnvisited();
		void markVisited( const city );
		city getAdjacentCity ( const city );
		void readCityFile();
		void readFlightFile();
		void readRequestFile();

		};

	/**
	Node class. Used in map class flight map operations.
	*/

	class node
		{

		private:

		node(const string, node*);
		city data;
		node* next;
		friend class map;

		};

	/**
	Readin class. As specified by the prompt, used to simplify some file I/O processes.
	*/

	class readin
		{

		public:
		string getName(ifstream&);
		namePair getNamePair(ifstream&);

		};

