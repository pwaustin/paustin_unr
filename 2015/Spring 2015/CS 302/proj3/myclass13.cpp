/** CS 302 Project 3 Question 13 - class implementations
@file myclass13.cpp
@author Patrick Austin
@date 2/21/2015 */

#include "myclass13.h"
#include <cassert>
#include <fstream>
#include <iostream>
using namespace std;

	/** Stack constructor.
	@pre None.
	@post Stack is created and ready for first entry.
	@return None. */

	template <class ItemType> stack <ItemType>::stack()
		{

		top = -1;
		cursor = -1;

		} 

	/** Stack isEmpty function.
	@pre None.
	@post Bool returned; stack data unchanged.
	@return bool - True if empty, false if not. */

	template <class ItemType> bool stack <ItemType>::isEmpty() const
		{

		return top < 0;

		}

	/** Stack push function.
	@param newValue The Item to be added to the stack.
	@pre None.
	@post Bool returned; if the stack was not full, the value has been pushed onto the stack.
	@return bool - True if the value was added, false if it could nto be added because the stack was full. */

	template <class ItemType> bool stack <ItemType>::push( const ItemType &newValue )
		{

		bool result = false;

		if ( top < MAX_STACK - 1 )
			{

			top++;
			items[top] = newValue;
			result = true;

			}	

		return result;

		}

	/** Stack pop function.
	@pre None.
	@post Bool returned; if the stack was not empty, the value at the top of the stack has been removed.
	@return bool - True if pop was successful, false if not. */

	template <class ItemType> bool stack <ItemType>::pop()
		{

		bool result = false;

		if ( !isEmpty() )
			{

			top--;
			result = true;

			}

		return result;

		}

	/** Stack peekAtTop function.
	@pre None.
	@post Top value returned, if there was one. Data in the stack unchanged.
	@return The item at the top of the stack, if there was one. */

	template <class ItemType> ItemType stack <ItemType>::peekAtTop() const
		{

		assert ( !isEmpty() );

		return items[top];

		}

	/** Stack initCursor function.
	@pre None.
	@post Cursor is set (or reset) to the bottom of the stack. Caveat emptor: use before any cursor operations, as cursor is initailized at -1,
		but make sure the stack is not empty first.
	@return None. */

	template <class ItemType> void stack <ItemType>::initCursor()
		{

		cursor = 0;

		}

	/** Stack traverseToNext function.
	@pre None.
	@post Cursor incremented by 1 if not at the top of the stack already.
	@return bool - True if cursor could be incremented, false if not. */

	template <class ItemType> bool stack <ItemType>::traverseToNext()
		{

		bool result = false;

		if ( cursor < top )
			{

			cursor++;
			result = true;

			}

		return result;

		}

	/** Stack peekAtCursor function.
	@pre None.
	@post Value at cursor returned, if there was one.
	@return The item located at cursor, if there was one. */

	template <class ItemType> ItemType stack <ItemType>::peekAtCursor() const
		{

		assert ( cursor > -1 );

		return items[cursor];

		}


	/** City constructor. Initializes 'visited' value for the city to false and flight number and cost to 0.
	@pre None.
	@post City object created with visited value equal to false and flight number and flight cost to 0.
	@return None. */

	city::city()
		{

		visited = false;

		flightNumber = 0;

		flightCost = 0;

		}

	/** City setName function.
	@param value The string desired for the city's name value.
	@pre None.
	@post The city's name has been set to that of the value parameter.
	@return None. */

	void city::setName ( const string value )
		{

		name = value;

		}

	/** City getName function.
	@pre None, but caveat emptor that this will return garbage if the city's name was not set elsewhere.
	@post City name returned; data in city object unchanged.
	@return string - The name of the city object. */

	string city::getName() const
		{

		return name;

		}

	/** City setVisited function.
	@param value The bool desired for the city's visited value.
	@pre None.
	@post City visited value set to the one specified in the value parameter.
	@return None. */

	void city::setVisited ( const bool value )
		{

		visited = value;

		}

	/** City isVisited function.
	@pre None.
	@post City visited value returned; data in city object unchanged.
	@return bool - The visited value of the city object. */

	bool city::isVisited() const
		{

		return visited;
		
		}

	/** City setFlightNumber function.
	@param value The flight number desired for the city's flight number value.
	@pre None.
	@post City flight number set to the one specified in the value parameter.
	@return None. */

	void city::setFlightNumber ( const int value ) 
		{

		flightNumber = value;
		
		}

	/** City getFlightNumber function.
	@pre None.
	@post City flight number returned; data in city object unchanged.
	@return int - The flight number value of the city object. */

	int city::getFlightNumber()
		{

		return flightNumber;

		}

	/** City setFlightCost function.
	@param value The flight cost desired for the city's flight cost value.
	@pre None.
	@post City flight cost set to the one specified in the value parameter.
	@return None. */

	void city::setFlightCost ( const int value )
		{

		flightCost = value;

		}

	/** City getFlightCost function.
	@pre None.
	@post City flight cost returned; data in city object unchanged.
	@return int - The flight cost of the city object. */

	int city::getFlightCost()
		{

		return flightCost;

		}

	/** namePair setOrigin function. Sets the origin of a namePair object to specified city.
	@param c The city that will be stored as the pair's origin.
	@pre None.
	@post namePair object's origin set to specified value.
	@return None. */

	void namePair::setOrigin(const city c)
		{

		origin = c;

		}

	/** namePair getOrigin function. Returns the origin city of a namePair object.
	@pre None.
	@post namePair object's origin returned; object itself unchanged.
	@return city - The origin city of the pair. */

	city namePair::getOrigin() const
		{

		return origin;

		}

	/** namePair setDest function. Sets the destination of a namePair object to specified city.
	@param d The city that will be stored as the pair's destination.
	@pre None.
	@post namePair object's destination set to specified value.
	@return None. */

	void namePair::setDest(const city d)
		{

		dest = d;

		}

	/** namePair getDest function. Returns the destination city of a namePair object.
	@pre None.
	@post namePair object's destination returned; object itself unchanged.
	@return city - The destination city of the pair. */

	city namePair::getDest() const
		{

		return dest;

		}

	/** Map object constructor. Conducts the creation, through file readin, of the node-based flightmap and array of flight requests that will be used in later operations.
		Also initailizes the tryNext pointers for use in getAdjacentCity to NULL. Will call readin functions, which will prompt user for appropriate filenames.
		Filenames MUST be formatted correctly to ensure successful operation. Remember, flightFile.txt is formatted differently for this problem!
	@pre None, but the functions called by this one will prompt user for valid and correctly formatted data files, as per the prompt. MAX_CITIES number of cities supported
		allowed for flight map; MAX_REQUESTS number of flight requests supported. Remember, flightFile.txt is formatted differently for this problem!
	@post Map object created with flight map and requested flights as specified in the data files. Relevant values in tryNext array set to NULL.
	@return None. */

	map::map()
		{

		//get data from city file

		readCityFile();

		//get data from flight pairs file

		readFlightFile();

		//get data from requests file

		readRequestFile();

		//set pointers in the tryNext array to NULL

		for ( int index = 0; index < numCities; index++ )
			{

			tryNext[index] = NULL;

			}

		}

	/** Map object destructor. Deallocates the nodes in the flight map so as to avoid memory leak.
	@pre None.
	@post Map object destroyed; nodes for the flight map, if any, deallocated.
	@return None. */

	map::~map()
		{

		//loop over each node chain, deallocating all the nodes

		for ( int index = 0; index > numCities; index++ )
			{
			
			node* temp2;
			node* temp1 = adjacencyMap[index];

			while ( temp1->next != NULL )
				{

				temp2 = temp1;

				temp1 = temp1->next;

				delete temp2;

				}

			delete temp1;

			}

		}

	/** City isPath function. Determines if it is possible to fly from the specified origin city to the specified destination city. Implemented using stack class.

		Modified from Project 11/12 implementations to call a function which will report the itinerary to the console if a path is found. This implementation also uses
		a pointer to the stack used for flight map operations as a data member, so the itinerary function can access the data in the stack easily.
	@param origin The city one is attempting to depart from.
	@param destination The city one is attempting to reach.
	@pre None, but correctly read-in data from the constructor is needed for correct results.
	@post Flight map may have had a number of cities within it marked visited and a number of tryNext pointers may have been created (these are reset to unvisited 
		and NULL respectively if this function is called again).
	@return bool - True if a path was found, false if no path was found.. */

	bool map::isPath( const city origin , const city destination )
		{

		//make a new stack of cities

		path = new stack<city>;

		//reset the marks on all cities

		markAllUnvisited();

		//reset the try-next pointers

		clearTryNext();

		//mark origin as visited and push it onto the stack

		path->push(origin);

		markVisited(origin);

		//proceed until the stack is empty, or the top of the stack is the destination city

		while ( !path->isEmpty() && ( path->peekAtTop().getName() != destination.getName() ) )
			{

			//get an unmarked city adjacent to the city at the top of the stack, if possible

			city temp = getAdjacentCity( path->peekAtTop() );

			//if no city was found, pop the city at the top currently

			if ( temp.getName() == "NO_CITY" )
				{

				path->pop();

				}

			//if a city was found, mark it as visited and push it onto the stack

			else
				{

				path->push(temp);
				markVisited(temp);

				}

			}

		//after the loop, either the stack is either empty, indicating no path was found, or the destination is at the top, and a path was found. return appropriately

		if ( path->isEmpty() )
			{

			//deallocate the stack

			delete path;

			return false;

			}

		else
			{

			//print a flight itinerary, as per prompt

			printItinerary();

			//deallocate the stack

			delete path;

			return true;

			}

		}

	/** Map isValidRequest function. Determines if a read-in flight request has an origin and a destination that exist in the flight map.
	@param index The index location of the request that is to be tested to see if it is valid.
	@pre NIndex must be less than numFlightRequests. Correctly read-in data from the constructor is needed.
	@post Bool returned; flight map and request unchanged.
	@return bool - True if the request is valid, false if it is not. */

	bool map::isValidRequest(const int index)
		{
		
		bool result = true;

		if ( !isServicedCity( requests[index].getOrigin() ) )
			{

			result = false;

			}

		else if ( !isServicedCity( requests[index].getDest() ) )
			{

			result = false;

			}

		return result;

		}

	/** Map isServicedCity function. Determines if target city is one within the flight map (ie, if it is serviced by the airline).
	@param target The city that is to be looked for within the flight map.
	@pre Correctly read-in data from the constructor is needed.
	@post Value returned; flight map and requests unchanged.
	@return bool - True if city is contained in the flight map, false if not. */

	bool map::isServicedCity( const city target ) const
		{

		//visit each city in the flight map and see if its name matches the target. return true as soon as one is found; false if none are found

		for ( int index = 0; index < numCities; index++ )
			{

			node* tempPtr = adjacencyMap[index];

			if ( tempPtr->data.getName() == target.getName() )
				{

				return true;

				}

			while ( tempPtr->next != NULL )
				{

				tempPtr = tempPtr->next;
			
				if ( tempPtr->data.getName() == target.getName() )
					{

					return true;

					}

				}

			}

		//if the end of the loop was reached, the city was not found - return false

		return false;
		
		}

	/** Map getRequestOrigin function. Returns the origin city for a read-in flight request.
	@param index The index location of the request whose origin is to be returned.
	@pre Index must be less than numFlightRequests. Correctly read-in data from the constructor is needed.
	@post Value returned; flight map and requests unchanged.
	@return city - The origin city of the specified request. */

	city map::getRequestOrigin(const int index) const
		{

		return requests[index].getOrigin();

		}

	/** Map getRequestDestination function. Returns the destination city for a read-in flight request.
	@param index The index location of the request whose destination is to be returned.
	@pre Index must be less than numFlightRequests. Correctly read-in data from the constructor is needed.
	@post Value returned; flight map and requests unchanged.
	@return city - The destination city of the specified request. */

	city map::getRequestDestination(const int index) const
		{

		return requests[index].getDest();

		}

	/** Map getNumRequests function.
	@pre Correctly read-in data from the constructor is needed.
	@post Value returned; flight map and requests unchanged.
	@return int - The number of flight requests from read-in. */
		
	int map::getNumRequests() const
		{

		return numRequests;

		}


	/** Map clearTryNext function. Resets all pointers in the tryNext array to NULL. Used in flight map operations.
	@pre None.
	@post All used ( < numCities) values in the array reset to NULL.
	@return None. */

	void map::clearTryNext()
		{

		//reset each tryNext pointer to NULL

		for ( int index = 0; index < numCities; index++ )
			{

			tryNext[index] = NULL;

			}

		}


	/** City markAllUnvisited function. Visits each city in the node-based flightmap and sets its 'visited' data member to false.
	@pre None. Correctly read-in data from the constructor is needed for anything of use to be accomplished, though.
	@post All cities in the flight map marked as unvisited.
	@return None. */

	void map::markAllUnvisited()
		{

		//loop over each node chain, setting all cities to unvisited

		for ( int index = 0; index < numCities; index++ )
			{

			node* tempPtr = adjacencyMap[index];

			tempPtr->data.setVisited(false);

			while ( tempPtr->next != NULL )
				{

				tempPtr = tempPtr->next;
			
				tempPtr->data.setVisited(false);

				}

			}

		}

	/** City markVisited function. Visits all instances of specified city within the flightmap and sets their 'visited' value to true.
	@param target The city that will be marked as visited within the flight map.
	@pre None, but correctly read-in data from the constructor is needed for anything of use to be accomplished, though.
	@post All instances of specified city within the flightmap have their visited value set to true.
	@return None. */

	void map::markVisited( const city target )
		{

		//visit each node and mark it visited

		for ( int index = 0; index < numCities; index++ )
			{

			node* tempPtr = adjacencyMap[index];

			if ( tempPtr->data.getName() == target.getName() )
				{

				tempPtr->data.setVisited(true);

				}

			while ( tempPtr->next != NULL )
				{

				tempPtr = tempPtr->next;
			
				if ( tempPtr->data.getName() == target.getName() )
					{

					tempPtr->data.setVisited(true);

					}

				}

			}
		}

	/** Map getAdjacentCity function. For target city, reads the flight map to determine if there is an unvisited city that one can fly directly to.
		Returns that city if one is found; if not, returns a city with "NO_NAME" as its name value to indicate that no subsequent unvisited cities can be reached.

		Modified from problem 11 to utilize an array of try-next pointers designed to reduce unnecessary traversal of the linked-node chain. Due to the addition
		of the try-next this function can no longer be const, as it was in problem 11.
	@param source - City for which the function will attempt to find an adjacent unvisited city.
	@pre Correctly read-in data from the constructor is needed.
	@post City returned; flight map is unchanged. A try-next value may or may not have been added to the try-next array.
	@return city - The result of the search. An adjacent city if one was found, a city with "NO_NAME" as its name value if one was not found. */

	city map::getAdjacentCity ( const city source )
		{

		int index = 0;

		//create a temp city with name "NO_CITY" to return if needed

		city temp;

		temp.setName("NO_CITY");

		//find the index of the node chain with the source city as its origin

		while ( adjacencyMap[index]->data.getName() != source.getName() )
			{

			index++;

			}

		//create a temp pointer for node traversing

		node* tempPtr;

		//if there is a try-next pointer for this city, go straight to that to skip unnecessary traversing

		if ( tryNext[index] != NULL )
			{

			tempPtr = tryNext[index];

			}

		//otherwise, set a pointer to the first destination from that city

		tempPtr = adjacencyMap[index]->next;

		//if that pointer is null there are no unvisited destinations from that city, return a temp city with the name "NO_CITY"

		if ( tempPtr == NULL )
			{

			return temp;

			}

		//see if the initial destination is unvisited

		if ( !tempPtr->data.isVisited() )
			{

			//if it was unvisited, set the tryNext to the city after this one

			tryNext[index] = tempPtr->next;

			//then return this city

			return tempPtr->data;
		
			}

		//otherwise, there is at least one additional destination. see if it, or any subsequent destinations, are unvisited

		while ( tempPtr->next != NULL )
			{

			tempPtr = tempPtr->next;

			//if an unvisited city is found...

			if ( !tempPtr->data.isVisited() )
				{

				//set the tryNext to the city after this one

				tryNext[index] = tempPtr->next;

				//then return this city

				return tempPtr->data;

				}

			}

		//if no unvisited destinations were found, return the temp city with name "NO_NAME"

		return temp;

		}

	/** Map printItinerary function. Prints to console astep by step flight map, including individual cost, flight numbers, and total cost, 
		for a stack of flights for which a path has been successfully found (ie when isPath operation is returning true). Only looks at
		the contents of this stack, does not modify them. Uses the traverse operations of the stack unique to problem 13.
	@pre Stack of cities must be the one created by the isPath operation returning true.
	@post Itinerary information printed to console.
	@return None. */

	void map::printItinerary()
		{

		//initalize total cost to 0
		
		int totalCost = 0;

		//initialize the cursor

		path->initCursor();

		//print first line, indicating that a path was found

		cout << "CSAir flies from " << path->peekAtCursor().getName() << 
		" to " << path->peekAtTop().getName() << "." << endl;

		//get the city at the bottom of the stack

		city temp1 = path->peekAtCursor();

		//continue until you have reached the top of the stack

		while ( path->traverseToNext() )
			{

			//get the next city

			city temp2 = path->peekAtCursor();

			//print a line of the itinerary

			cout << "Flight #" << temp2.getFlightNumber() << " from " << temp1.getName() << 
			" to " << temp2.getName() << " Cost: $" << temp2.getFlightCost() << endl;

			//update the cost so far

			totalCost += temp2.getFlightCost();

			//the destination of this flight will be the origin of the next one

			temp1 = temp2;

			}
		
		//print the total cost of the flight

		cout << "Total Cost ................. $" << totalCost << endl << endl;

		}

	/** Map readCityFile function. Reads user specified datafile as formatted in the prompt's "cityFile.txt" to initialize the flight map.
	@pre Specified file must be formatted correctly, as per prompt.
	@post File's data read into the flightmap.
	@return None. */

	void map::readCityFile()
		{

		//open file

		ifstream fin;
		readin read;
		char* filename = new char [50];

		cout << "Enter city file: ";

		cin >> filename;

		fin.open(filename);

		numCities = 0;

		//read in a value

		city temp;

		temp.setName( read.getName(fin) );

		//continue reading in values until the end of the file. Each value will be the initial node of a row of the flight map.

		while ( fin.good() )
			{

			adjacencyMap[numCities] = new node (temp.getName(), 0, 0, NULL);

			//increment numCities for each value added to the flight map

			numCities++;

			temp.setName( read.getName(fin) );

			}

		//close file

		delete [] filename;

		fin.close();

		}

	/** Map readFlightFile function. Reads user specified datafile as formatted in the prompt's "flightFile.txt" to initialize the flight map.
		Note that the format of this file has changed for problem 13, as per the prompt.
	@pre Specified file must be formatted correctly, as per prompt. Note that this formatting has changed for problem 13.
	@post File's data read into the flightmap.
	@return None. */

	void map::readFlightFile()
		{

		//open file

		ifstream fin;
		readin read;
		char* filename = new char [50];

		cout << "Enter flight file: ";

		cin >> filename;

		fin.open(filename);

		//read in first pair of flights

		namePair temp = read.getNamePairFlightFile(fin);

		//continue processing values until the end of the file

		while ( fin.good() )
			{

			int index = 0;

			bool matched = false;

			while (!matched)
				{

				//find the row of the flight map that matches the origin

				if ( adjacencyMap[index]->data.getName() == temp.getOrigin().getName() )
					{

					node* tempPtr = adjacencyMap[index];

					while ( tempPtr->next != NULL )
						{

						tempPtr = tempPtr->next;

						}

					//create a new node with the destination

					tempPtr->next = new node (temp.getDest().getName(), temp.getDest().getFlightNumber(), temp.getDest().getFlightCost(), NULL);

					matched = true;

					}

				else
					{

					index++;

					}

				}

			temp = read.getNamePairFlightFile(fin);

			}

		//close file

		delete [] filename;

		fin.close();

		}

	/** Map readRequestFile function. Reads user specified datafile as formatted in the prompt's "requestFile.txt" to initialize the flight map.
	@pre Specified file must be formatted correctly, as per prompt.
	@post File's data read into the array of flight requests.
	@return None. */

	void map::readRequestFile()
		{

		//open file

		ifstream fin;
		readin read;
		char* filename = new char [50];

		numRequests = 0;

		cout << "Enter request file: ";

		cin >> filename;

		fin.open(filename);

		//read first value

		namePair temp = read.getNamePair(fin);

		//continue processing values until the end of the file

		while ( fin.good() )
			{

			requests[numRequests].setOrigin( temp.getOrigin() );

			requests[numRequests].setDest( temp.getDest() );

			//increment numRequests with each request processsed

			numRequests++;

			temp = read.getNamePair(fin);

			}

		//close file

		delete [] filename;

		fin.close();

		}

	/** Node constructor. Sets city name and pointer to next node as specified by parameters. Sets visited status of the node's city to false.

	Modified from problem 11/12 implementation to also specify the flight number and cost of a flight to the city, for use in the flight map.
	@param c The name of the city that will be stored in the node.
	@param num The flight number of the flight to the city that will be stored in the node.
	@param cost The cost of the flight to the city that will be stored in the node.
	@param n The pointer that the next component of the node will store.
	@pre Enough available memory for a new node to be created.
	@post Node created with specified values
	@return None. */

	node::node(const string c, const int num, const int cost, node* n)
		{

		data.setName(c);

		data.setFlightNumber(num);

		data.setFlightCost(cost);

		data.setVisited(false);

		next = n;

		}

	/** readin getName function. Reads in and returns a string from the datafile being handled by the fstream object fin.
	@param fin The fstream object for the file currently being handled.
	@pre A datafile must be opened by the fin object. This is designed for use in a correctly formatted "cityFile.txt" as specified, but will take any string in practice.
	@post Object read in as per fstream specifications.
	@return string - The string read out of the datafile. */

	string readin::getName(ifstream& fin)
		{

		string temp;

		fin >> temp;

		return temp; 

		}

	/** readin getNamePair function. Reads in and returns the data for a namePair object from the datafile being handled by the fstream object fin.

	Contra problem 11, this function now only matches the formatting for "requestFile.txt". getNamePairFlightMap function has been added to handle
		"flightFile.txt".
	@param fin The fstream object for the file currently being handled.
	@pre A datafile must be opened by the fin object. The file must be formatted as specified in "requestFile.txt" as per the prompt.
	@post Object read in as per fstream specifications.
	@return namePair - The namePair read out of the datafile. */

	namePair readin::getNamePair(ifstream& fin)
		{

		//declare temps

		namePair tempN;

		char* dummy = new char [20];

		char* tempS = new char [20];

		city tempC;

		//get the origin

			//get a string up to a ','

			fin.getline( tempS, 1000, ',' );

			//read in the tab char

			fin.getline( dummy, 1000, '\t');

			//make the string the name of a city

			tempC.setName(tempS);

			//make the city the origin of a pair

			tempN.setOrigin(tempC);

		//get the destination

			//get a string up to the endline char

			fin.getline( tempS, 1000, '\n' );

			//make the string the name of a city

			tempC.setName(tempS);

			//make the city the destination of a pair

			tempN.setDest(tempC);

		//deallocate dynamic memory

		delete [] tempS;
		delete [] dummy;

		//return the pair

		return tempN;

		}

	/** readin getNamePairFlightMap function. Reads in and returns the data for a namePair object from the datafile being handled by the fstream object fin.
	@param fin The fstream object for the file currently being handled.
	@pre A datafile must be opened by the fin object. The file must be formatted as specified in "flightFile.txt" as per the prompt.
	@post Object read in as per fstream specifications.
	@return namePair - The namePair read out of the datafile. */

	namePair readin::getNamePairFlightFile(ifstream& fin)
		{

		//declare temps

		namePair tempN;

		int tempInt1;

		int tempInt2;

		char dummy2;

		char* dummy = new char [20];

		char* tempS = new char [20];

		city tempC;

		//get the origin

			//get a string up to a ','

			fin.getline( tempS, 1000, ',' );

			//read in the tab

			fin.getline( dummy, 1000, '\t');

			//make the string the name of a city

			tempC.setName(tempS);

			//make the city the origin of a pair

			tempN.setOrigin(tempC);

		//get the destination

			//get a string up to the tab char

			fin.getline( tempS, 1000, '\t' );

			//read in the flight number

			fin >> tempInt1;

			//read in the flight cost

			fin >> tempInt2;

			//assign these values to a city

			tempC.setName(tempS);

			tempC.setFlightNumber(tempInt1);

			tempC.setFlightCost(tempInt2);

			//make the city the destination of a pair

			tempN.setDest(tempC);

			//get a string up to the endline char

			fin.getline( tempS, 1000, '\n' );

		//deallocate dynamic memory

		delete [] tempS;
		delete [] dummy;

		//return the pair

		return tempN;

		}
