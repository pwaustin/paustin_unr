/** CS 302 Project 3 Question 12 - class implementations
@file myclass12.cpp
@author Patrick Austin
@date 2/21/2015 */

#include "myclass12.h"
#include <cassert>
#include <fstream>
using namespace std;

	/** Stack constructor.
	@pre None.
	@post Stack is created and ready for first entry.
	@return None. */

	template <class ItemType> stack <ItemType>::stack()
		{

		top = -1;

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

	/** Stack peek function.
	@pre None.
	@post Top value returned, if there was one. Data in the stack unchanged.
	@return The item at the top of the stack, if there was one. */

	template <class ItemType> ItemType stack <ItemType>::peek() const
		{

		assert ( !isEmpty() );

		return items[top];

		}

	/** City constructor. Initializes 'visited' value for the city to false.
	@pre None.
	@post City object created with visited value equal to false.
	@return None. */

	city::city()
		{

		visited = false;

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
		Filenames MUST be formatted correctly to ensure successful operation.
	@pre None, but the functions called by this one will prompt user for valid and correctly formatted data files, as per the prompt. MAX_CITIES number of cities supported
		allowed for flight map; MAX_REQUESTS number of flight requests supported.
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
	@param origin The city one is attempting to depart from.
	@param destination The city one is attempting to reach.
	@pre None, but correctly read-in data from the constructor is needed for correct results.
	@post Flight map may have had a number of cities within it marked visited and a number of tryNext pointers may have been created (these are reset to unvisited 
		and NULL respectively if this function is called again).
	@return bool - True if a path was found, false if no path was found.. */

	bool map::isPath( const city origin , const city destination )
		{

		//make a new stack of cities

		stack<city> path;

		//reset the marks on all cities

		markAllUnvisited();

		//reset the try-next pointers

		clearTryNext();

		//mark origin as visited and push it onto the stack

		path.push(origin);
		markVisited(origin);

		//proceed until the stack is empty, or the top of the stack is the destination city

		while ( !path.isEmpty() && ( path.peek().getName() != destination.getName() ) )
			{

			//get an unmarked city adjacent to the city at the top of the stack, if possible

			city temp = getAdjacentCity( path.peek() );

			//if no city was found, pop the city at the top currently

			if ( temp.getName() == "NO_CITY" )
				{

				path.pop();

				}

			//if a city was found, mark it as visited and push it onto the stack

			else
				{

				path.push(temp);
				markVisited(temp);

				}

			}

		//after the loop, either the stack is either empty, indicating no path was found, or the destination is at the top, and a path was found. return appropriately

		if ( path.isEmpty() )
			return false;

		else
			return true;

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

	/** City getAdjacentCity function. For target city, reads the flight map to determine if there is an unvisited city that one can fly directly to.
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

			adjacencyMap[numCities] = new node (temp.getName(),NULL);

			//increment numCities for each value added to the flight map

			numCities++;

			temp.setName( read.getName(fin) );

			}

		//close file

		fin.close();

		delete [] filename;

		}

	/** Map readFlightFile function. Reads user specified datafile as formatted in the prompt's "flightFile.txt" to initialize the flight map.
	@pre Specified file must be formatted correctly, as per prompt.
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

		namePair temp = read.getNamePair(fin);

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

					tempPtr->next = new node (temp.getDest().getName(),NULL);

					matched = true;

					}

				else
					{

					index++;

					}

				}

			temp = read.getNamePair(fin);

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
	@param c The name of the city that will be stored in the node.
	@param n The pointer that the next component of the node will store.
	@pre Enough available memory for a new node to be created.
	@post Node created with specified values
	@return None. */

	node::node(const string c, node* n)
		{

		data.setName(c);

		data.setVisited(false);

		next = n;

		}

	/** readin getName function. Reads in and returns a string from the datafile being handled by the fstream object fin.
	@param fin The fstream object for the file currently being handled.
	@pre A datafile must be opened by the fin object.
	@post Object read in as per fstream specifications.
	@return string - The string read out of the datafile. */

	string readin::getName(ifstream& fin)
		{

		string temp;

		fin >> temp;

		return temp; 

		}

	/** readin getNamePair function. Reads in and returns the data for a namePair object from the datafile being handled by the fstream object fin.
	@param fin The fstream object for the file currently being handled.
	@pre A datafile must be opened by the fin object. The file must be formatted as specified in "flightFile.txt" and "requestFile.txt" as per the prompt.
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
