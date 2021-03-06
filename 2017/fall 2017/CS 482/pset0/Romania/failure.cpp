#include <stdio.h>
#include <cstdlib>
#include <queue>
#include <stack>
#include <iostream>
#include <fstream>
using namespace std;

//The number of vertices stored in our graph
int vertexCount = 0;
//A 2D array of edges in the format graph[vertexA][vertexB] = distance between vertexA and vertexB
int** graph;
//The output logging file. Don't worry about this one
FILE* output;

/*
AddEdge: Add an edge to the graph from vertex u to vertex v.
Arugments:
	int u: One of the vertices that form the edge
	int v: The other vertice that forms the edge
	int dist: The distance between u and v
Adds an edge to the graph from vertex u to vertex v with the given distance dist.
The graph is represented a a 2D array of integers, where each integer is a distance.
When an edge is added from u to v an edge from v to u is also saved in memory.
Returns void: No value returned
*/
void AddEdge(int u, int v, int dist)
{
	graph[u][v] = dist;
	graph[v][u] = dist;
}

/*
ReadGraphFile: Read graph data in from a file to populate our graph structure.
Arguments:
	char* fname: The name of the file to read
Reads graph data in from a file to populate our graph structure. The format of the file
defines a number of vertices at the top of the file, and edges for the graph for each
line afterwards in the format (U, V, DIST).
Returns bool: Returns true if the file was opened and read successfuly, and false if the file could not be read
*/
bool ReadGraphFile(char* fname)
{
	FILE* file = fopen(fname, "r");

	if (file)
	{
		rewind(file);
		int a, b, d;
		
		fscanf(file, "%d", &vertexCount);
		//fscanf_s(file, "%d", &vertexCount);

		graph = new int*[vertexCount];
		for (int u = 0; u < vertexCount; u++)
		{
			graph[u] = new int[vertexCount];

			for (int v = 0; v < vertexCount; v++)
			{
				graph[u][v] = 0;
			}
		}

		while (fscanf(file, "%d %d %d", &a, &b, &d) != EOF)
//		while (fscanf_s(file, "%d %d %d", &a, &b, &d) != EOF)
		{
			AddEdge(a, b, d);
		}

		fclose(file);

		return true;
	}
	else
	{
		printf("Failed to read file...\n");
		return false;
	}
}

/*
LogVertex: Prints the current vertex traveled to and saves the output to a file
Arguments:
	int vert: The vertex that you are currently visiting
In order for us to grade you, you must print the vertex you are travelling to in your algorithm.
This function makes it easier for you to print the proper data. It also saves the data to a file.
Returns void: No values returned
*/
void LogVertex(int vert)
{
	printf("%d\n", vert);
	fprintf(output, "%d\n", vert);
}

/*
StartLogging: Opens the logging file for later writing
Arguments:
	None
Pretty much just a wrapper for fopen so that we make sure you are writing your logging data to the right file.
Returns void: No values returned
*/
void StartLogging()
{
	output = fopen("log.txt", "w");
}

/*
EndLogging: Closes the logging file properly
Arguments:
	None
Pretty much just a wrapper for fclose so that we make sure you close the right file.
Returns void: No values returned
*/
void EndLogging()
{
	fclose(output);
}

int dfs(int start, int dest, int costSoFar)
{
cout << "new call" << endl;
	int next;
	int proposedCost;
	int bestCost;
	bool* isVisited = new bool[vertexCount];
	queue<int> frontier;

cout << "adding to log: ";
	LogVertex(start);

	if (start == dest)
		{
		cout << "path found, exiting search" << endl;
		return 0;
		}

	else
		{

		for (int i = 0; i < vertexCount; i++ )
			{

			if ( graph[start][i] > 0 )
				{
cout << "pushing path from " << start << "to " << i << endl;
				frontier.push_back(i);
				}

			}

		if ( frontier.empty() )
			{
cout << "can't find path, return 10k" << endl;
			return 10000;
			}

		else
			{

			next = frontier.front();

			frontier.pop_front();

			bestCost = dfs(next, dest, costSoFar + graph[start][next]);
cout << "first pop: best cost estimate is " << bestCost << endl;
			}

		while ( !frontier.empty() )
			{
			next = frontier.front();

			frontier.pop_front();

			proposedCost = dfs(next, dest, costSoFar + graph[start][next]);

			if ( proposedCost < bestCost )
				bestCost = proposedCost;

			}

		return bestCost;

		}
}

int main(int argc, char** argv)
{

	//declare variables

	int startCity;
	int endCity;
	int currentCity;
	int searchType;
	int success;
	//Setup
	//-----------------------------------
	if (argc == 5)
	{
		if (!ReadGraphFile(argv[1]))
			return 2;
	}
	else
	{
		printf("No file argument given...\n");
		return 1;
	}
	StartLogging();
	//-------------------------------------

	//take start city, end city, search type from argv

	startCity = atoi(argv[2]);
	endCity = atoi(argv[3]);
	searchType = atoi(argv[4]);

	//do dfs

	if ( searchType == 1 )
		{
		success = dfs(startCity, endCity, 0);				
if ( success == 10000 )
	cout << "traversal bad" << endl;
else
	cout << "traversal good, shortest path is " << success << endl;
		}
	//do bfs

	//do ids


	//Cleanup
	//-------------------------------------
	EndLogging();
	getchar();
	//-------------------------------------

	return 0;
}

