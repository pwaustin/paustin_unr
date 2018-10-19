#include <cmath>
#include <algorithm>
#include <iostream>
#include <stdio.h>
using namespace std;

//The 2D board for our 8-puzzle in format board[x][y]
int** board;
//The output logging file. Don't worry about this one
FILE* output;

/*
ReadBoardFile: Read board data in from a file to populate our board structure.
Arguments:
char* fname: The name of the file to read
This just reads a simple file format of a b c each line. There should be three lines.
Each of the 9 entries should go from 0-8 inclusive. If you spot a problem let us know.
Returns bool: Returns true if the file was opened and read successfuly, and false if the file could not be read
*/
bool ReadBoardFile(char* fname)
{
	FILE* file = fopen(fname, "r");
	if (file)
	{
		rewind(file);
		int a, b, c;

		board = new int*[3];
		for (int u = 0; u < 3; u++)
		{
			board[u] = new int[3];

			for (int v = 0; v < 3; v++)
			{
				board[u][v] = 0;
			}
		}

		int i = 0;
		//while (fscanf_s(file, "%d %d %d", &a, &b, &c) != EOF)
		while (fscanf(file, "%d %d %d", &a, &b, &c) != EOF)
		{
			board[0][i] = a;
			board[1][i] = b;
			board[2][i] = c;
			i++;
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
LogCell: Prints the current cell traveled to and its value and saves the output to a file
Arguments:
int x: The x of the cell you are visiting
int y: The y of the cell you are visiting
In order for us to grade you, you must print the cell you are travelling to in your algorithm.
This function makes it easier for you to print the proper data. It also saves the data to a file.
Returns void: No values returned
*/
void LogCell(int x, int y)
{
	printf("(%d, %d): %d\n", x, y, board[x][y]);
	fprintf(output, "(%d, %d): %d\n", x, y, board[x][y]);
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

int calcDistance()
{}
int calcUp()
{}
int calcDown()
{}
int calcLeft()
{}
int calcRight()
{}

int main(int argc, char** argv)
{
	//Setup
	//-----------------------------------
	if (argc == 2)
	{
		if (!ReadBoardFile(argv[1]))
			return 2;
	}
	else
	{
		printf("No file argument given...\n");
		return 1;
	}
	StartLogging();
	//-------------------------------------

	//declare vars

	int manhattan;
	int prev = 0;
	int iterations = 0;
	int target [3][3] = { {0, 1, 2} , {3, 4, 5} , {6, 7, 8} };
	int upVal;
	int downVal;
	int leftVal;
	int rightVal;
	int xPos;
	int yPos;

	//get initial location of 0
	for ( int i = 0; i < 3; i++ )
		{
		for ( int j = 0; j < 3; j++ )
			{
			cout << board[i][j] << '\t';
			}
cout << endl;
		}


	//get initial manhattan distance for the board that was read in

	manhattan = calcDistance();

	//loop until manhattan distance to the solution board is zero, meaning success, or -1, meaning we gave up

	while ( manhattan > 0 )
		{

		upVal = 100000;
		downVal = 100000;
		leftVal = 100000;
		rightVal = 100000;

		}
	

	

	//Cleanup
	//-------------------------------------
	EndLogging();
	getchar();
	//-------------------------------------
	return 0;
}
