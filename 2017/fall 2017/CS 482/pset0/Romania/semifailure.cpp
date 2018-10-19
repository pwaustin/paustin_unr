#include <stdio.h>
#include <stack>
#include <queue>
#include <cstdlib>
#include <iostream>
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
SetartLogging: Opens the logging file for later writing
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

int dfs(int start, int end)
{

	int current;
	int relax;
	bool empty = false;
	int* dist = new int[vertexCount];
	int* pred = new int[vertexCount];
	bool* seen = new bool[vertexCount];
	stack<int> frontier;

	for ( int i = 0; i != vertexCount; i++ )
		{
		dist[i] = 10000;
		pred[i] = -1;
		seen[i] = false;
		}

	dist[start] = 0;
	frontier.push(start);

	while ( !empty )
		{

		current	= frontier.top();
		frontier.pop();
		seen[current] = true;

		for ( int m = 0; m != vertexCount; m++ )
			{

			if ( graph[current][m] > 0 && seen[m] == false )
				frontier.push(m);
			}

		for ( int k = 0; k != vertexCount; k++ )
			{
		
			if ( graph[current][k] > 0 )
				{
				relax = dist[current] + graph[current][k];
				if ( relax < dist[k] )
					{
					cout << "relaxed " << k << " from " << dist[k] << " to " << relax << endl;
					dist[k] = relax;			
					pred[k] = current;
					}
				}

			}

for ( int l = 0; l != vertexCount; l++ )
cout << dist[l] << '\t';

cout << endl;

		empty = true;
		for ( int j = 0; j < vertexCount; j++ )
			{
			if ( seen[j] == false )
				empty = false;
			}

		}

for ( int n = 0; n != vertexCount; n++ )
	{

	for ( int o = 0; o != vertexCount; o++ )
		{
			if ( graph[o][n] > 0 )
				{
				relax = dist[o] + graph[o][n];
				if ( relax < dist[n] )
					{
					cout << "relaxed " << n << " from " << dist[n] << " to " << relax << endl;
					dist[n] = relax;			
					pred[n] = current;
					}
				}
		}

	}

for ( int p = 0; p != vertexCount; p++ )
cout << dist[p] << '\t';

cout << endl;

return dist[end];


}




int main(int argc, char** argv)
{
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

	//Your code

	int startCity = atoi(argv[2]);
	int endCity = atoi(argv[3]);
	int searchType = atoi(argv[4]);

	cout << "DFS SSSP: " << dfs(startCity, endCity) << endl;

for (int i = 0; i < vertexCount; i++ )
	{
	for ( int j = 0; j < vertexCount; j++ )
		cout << graph[i][j] << '\t';
	cout << endl;
	}


	//Cleanup
	//-------------------------------------
	EndLogging();
	getchar();
	//-------------------------------------

	return 0;
}
