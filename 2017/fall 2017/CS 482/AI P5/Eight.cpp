#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <vector>
using namespace std;

//The 2D board for our 8-puzzle in format board[x][y]
int** board;
//The output logging file. Don't worry about this one
FILE* output;

//node struct: hold a 3x3 int array board and a manhattan value

struct node
{

int gameBoard[3][3];
int manhattan;

};

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

//calculate total manhattan distance on a board, ie the sum of moves required to put each piece in its proper place on an empty board
//assuming only u/d/l/r movement possible.

int calcDistance()
{

	int manhattan = 0;
	int distX;
	int distY;

	for ( int x = 0; x < 3; x++ )
		{

		for ( int y = 0 ; y < 3; y++ )
			{

			if ( board[x][y] != 0 )
				{
		
				distX = x - ( board[x][y] ) / 3;
				distY = y - ( board[x][y] ) % 3;
				manhattan += abs(distX) + abs(distY);

				}

			}

		}

return manhattan;

}

int calcUp(int xPos, int yPos)
{

	int manhattan;
	int temp;

	//move 0 up on the board
	
	temp = board[xPos - 1][yPos];
	board[xPos - 1][yPos] = board[xPos][yPos];
	board[xPos][yPos] = temp;

	//calculate the manhattan value for the modified board

	manhattan = calcDistance();

	//restore the board

	temp = board[xPos - 1][yPos];
	board[xPos - 1][yPos] = board[xPos][yPos];
	board[xPos][yPos] = temp;

	//return the manhattan value

	return manhattan;

}

int calcDown(int xPos, int yPos)
{

	int manhattan;
	int temp;

	//move 0 down on the board
	
	temp = board[xPos + 1][yPos];
	board[xPos + 1][yPos] = board[xPos][yPos];
	board[xPos][yPos] = temp;

	//calculate the manhattan value for the modified board

	manhattan = calcDistance();

	//restore the board

	temp = board[xPos + 1][yPos];
	board[xPos + 1][yPos] = board[xPos][yPos];
	board[xPos][yPos] = temp;

	//return the manhattan value

	return manhattan;

}

int calcLeft(int xPos, int yPos)
{

	int manhattan;
	int temp;

	//move 0 left on the board
	
	temp = board[xPos][yPos - 1];
	board[xPos][yPos - 1] = board[xPos][yPos];
	board[xPos][yPos] = temp;

	//calculate the manhattan value for the modified board

	manhattan = calcDistance();

	//restore the board

	temp = board[xPos][yPos - 1];
	board[xPos][yPos - 1] = board[xPos][yPos];
	board[xPos][yPos] = temp;

	//return the manhattan value

	return manhattan;

}

int calcRight(int xPos, int yPos)
{

	int manhattan;
	int temp;

	//move 0 left on the board
	
	temp = board[xPos][yPos + 1];
	board[xPos][yPos + 1] = board[xPos][yPos];
	board[xPos][yPos] = temp;

	//calculate the manhattan value for the modified board

	manhattan = calcDistance();

	//restore the board

	temp = board[xPos][yPos + 1];
	board[xPos][yPos + 1] = board[xPos][yPos];
	board[xPos][yPos] = temp;

	//return the manhattan value

	return manhattan;

}

//comparator for sorting the open list

bool compareByManhattan(const node& a, const node& b)
	{

	return a.manhattan < b.manhattan;

	}

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

//my code here

	//declare variables

	int i;
	int j;
	int k;
	int temp;
	int upVal;
	int downVal;
	int leftVal;
	int rightVal;
	int xPos;
	int yPos;
	bool found;
	vector<node> openList;
	vector<node> closedList;
	node copy;
	node searchNode;
	int currentManhattan;
	int iterations = 0; 

	//create initial node in open list with starting board pos and its manhattan value

	for ( i = 0; i < 3; i++ )
		for ( j = 0; j < 3; j++ )
			copy.gameBoard[i][j] = board[i][j];

	copy.manhattan = calcDistance();

	openList.push_back(copy);

	//on each loop...

	while ( openList.front().manhattan != 0 && iterations < 1000 )
		{

		//move bestnode from open to closed list

			//copy bestnode's data

			for ( i = 0; i < 3; i++ )
				{
				for ( j = 0; j < 3; j++ )
					{
					copy.gameBoard[i][j] = openList.front().gameBoard[i][j];
					}
				}

			copy.manhattan = openList.front().manhattan;

			//copy the data to the closed list			

			closedList.push_back(copy);

			//erase bestnode from the open list

			openList.erase( openList.begin() );

		//expand bestnode- determine better moves and add them to open list

			//copy out bestnode's values to work on

			for ( i = 0; i < 3; i++ )
				for ( j = 0; j < 3; j++ )
					board[i][j] = copy.gameBoard[i][j];

			currentManhattan = copy.manhattan;

			//determine 0 position on the current board

			for ( i = 0; i < 3; i++ )
				{
					for ( j = 0; j < 3; j++ )
					{
					if ( board[i][j] == 0 )
						{
						xPos = i;
						yPos = j;
						}
					}
				}

			//log this cell

			LogCell(xPos, yPos);

for ( i = 0; i < 3; i++ )
{

for ( j = 0; j < 3; j++ )
{
cout << board[i][j] << '\t';
}

cout << endl;

}
cout << "iteration " << iterations << " with mhv " << currentManhattan << endl;

			//calculate manhattan values for possible moves
	
			//up

			if ( xPos != 0 )
				{
				
				//calculate heuristic

				upVal = calcUp (xPos, yPos);

				temp = board[xPos - 1][yPos];
				board[xPos - 1][yPos] = board[xPos][yPos];
				board[xPos][yPos] = temp;

				//if this board is not on the open or closed list, or on them but with a lower manhattan value, add it to the open list

				found = false;

				if ( !openList.empty() )
					{

					for ( k = 0; k!= openList.size(); k++ )
						if ( openList[k].gameBoard[0][0] == board[0][0] && openList[k].gameBoard[0][1] == board[0][1] &&
						openList[k].gameBoard[0][2] == board[0][2] && openList[k].gameBoard[1][0] == board[1][0] &&
						openList[k].gameBoard[1][1] == board[1][1] && openList[k].gameBoard[1][2] == board[1][2] &&
						openList[k].gameBoard[2][0] == board[2][0] && openList[k].gameBoard[2][1] == board[2][1] &&
						openList[k].gameBoard[2][2] == board[2][2] )
							{
							
							if ( openList[k].manhattan >= upVal )
								{
								found = true;
								}

							}
					}

				if ( !closedList.empty() )
					{

					for ( k = 0; k!= closedList.size(); k++ )
						if ( closedList[k].gameBoard[0][0] == board[0][0] && closedList[k].gameBoard[0][1] == board[0][1] &&
						closedList[k].gameBoard[0][2] == board[0][2] && closedList[k].gameBoard[1][0] == board[1][0] &&
						closedList[k].gameBoard[1][1] == board[1][1] && closedList[k].gameBoard[1][2] == board[1][2] &&
						closedList[k].gameBoard[2][0] == board[2][0] && closedList[k].gameBoard[2][1] == board[2][1] &&
						closedList[k].gameBoard[2][2] == board[2][2] )
							{

							if ( closedList[k].manhattan >= upVal )
								{
								found = true;
								}
							}
					}

				//if this node passed the search, add it to the open list

				if ( found == false )
					{

					for ( i = 0; i < 3; i++ )
						for ( j = 0; j < 3; j++ )
							copy.gameBoard[i][j] = board[i][j];

					copy.manhattan = upVal;

					openList.push_back(copy);

					}

				//replace board

				temp = board[xPos - 1][yPos];
				board[xPos - 1][yPos] = board[xPos][yPos];
				board[xPos][yPos] = temp;

				}

			if ( xPos != 2 )
				{
	
				//calculate heuristic

				downVal = calcDown (xPos, yPos);

				temp = board[xPos + 1][yPos];
				board[xPos + 1][yPos] = board[xPos][yPos];
				board[xPos][yPos] = temp;

				//if this board is not on the open or closed list, or on them but with a lower manhattan value, add it to the open list

				found = false;

				if ( !openList.empty() )
					{

					for ( k = 0; k!= openList.size(); k++ )
						if ( openList[k].gameBoard[0][0] == board[0][0] && openList[k].gameBoard[0][1] == board[0][1] &&
						     openList[k].gameBoard[0][2] == board[0][2] && openList[k].gameBoard[1][0] == board[1][0] &&
						     openList[k].gameBoard[1][1] == board[1][1] && openList[k].gameBoard[1][2] == board[1][2] &&
						     openList[k].gameBoard[2][0] == board[2][0] && openList[k].gameBoard[2][1] == board[2][1] &&
						     openList[k].gameBoard[2][2] == board[2][2] )
							{
							
							if ( openList[k].manhattan >= upVal )
								{
								found = true;
								}

							}
					}

				if ( !closedList.empty() )
					{

					for ( k = 0; k!= closedList.size(); k++ )
						if ( closedList[k].gameBoard[0][0] == board[0][0] && closedList[k].gameBoard[0][1] == board[0][1] &&
						     closedList[k].gameBoard[0][2] == board[0][2] && closedList[k].gameBoard[1][0] == board[1][0] &&
						     closedList[k].gameBoard[1][1] == board[1][1] && closedList[k].gameBoard[1][2] == board[1][2] &&
						     closedList[k].gameBoard[2][0] == board[2][0] && closedList[k].gameBoard[2][1] == board[2][1] &&
						     closedList[k].gameBoard[2][2] == board[2][2] )
							{

							if ( closedList[k].manhattan >= upVal )
								{
								found = true;
								}

							}
					}

				//if this node passed the search, add it to the open list

				if ( found == false )
					{

					for ( i = 0; i < 3; i++ )
						for ( j = 0; j < 3; j++ )
							copy.gameBoard[i][j] = board[i][j];

					copy.manhattan = downVal;

					openList.push_back(copy);

					}

				//replace board

				temp = board[xPos + 1][yPos];
				board[xPos + 1][yPos] = board[xPos][yPos];
				board[xPos][yPos] = temp;

				}

			if ( yPos != 0 )
				{

				//calculate heuristic

				leftVal = calcLeft (xPos, yPos);

				temp = board[xPos][yPos - 1];
				board[xPos][yPos - 1] = board[xPos][yPos];
				board[xPos][yPos] = temp;

				//if this board is not on the open or closed list, or on them but with a lower manhattan value, add it to the open list

				found = false;

				if ( !openList.empty() )
					{

					for ( k = 0; k!= openList.size(); k++ )
						if ( openList[k].gameBoard[0][0] == board[0][0] && openList[k].gameBoard[0][1] == board[0][1] &&
						openList[k].gameBoard[0][2] == board[0][2] && openList[k].gameBoard[1][0] == board[1][0] &&
						openList[k].gameBoard[1][1] == board[1][1] && openList[k].gameBoard[1][2] == board[1][2] &&
						openList[k].gameBoard[2][0] == board[2][0] && openList[k].gameBoard[2][1] == board[2][1] &&
						openList[k].gameBoard[2][2] == board[2][2] )
							{
							
							if ( openList[k].manhattan >= upVal )
								{
								found = true;
								}

							}
					}

				if ( !closedList.empty() )
					{

					for ( k = 0; k!= closedList.size(); k++ )
						if ( closedList[k].gameBoard[0][0] == board[0][0] && closedList[k].gameBoard[0][1] == board[0][1] &&
						closedList[k].gameBoard[0][2] == board[0][2] && closedList[k].gameBoard[1][0] == board[1][0] &&
						closedList[k].gameBoard[1][1] == board[1][1] && closedList[k].gameBoard[1][2] == board[1][2] &&
						closedList[k].gameBoard[2][0] == board[2][0] && closedList[k].gameBoard[2][1] == board[2][1] &&
						closedList[k].gameBoard[2][2] == board[2][2] )
							{

							if ( closedList[k].manhattan >= upVal )
								{
								found = true;
								}
							}
					}

				//if this node passed the search, add it to the open list

				if ( found == false )
					{

					for ( i = 0; i < 3; i++ )
						for ( j = 0; j < 3; j++ )
							copy.gameBoard[i][j] = board[i][j];

					copy.manhattan = leftVal;

					openList.push_back(copy);

					}

				//replace board

				temp = board[xPos][yPos - 1];
				board[xPos][yPos - 1] = board[xPos][yPos];
				board[xPos][yPos] = temp;

				}

			if ( yPos != 2 )
				{
				//calculate heuristic

				rightVal = calcRight (xPos, yPos);

				temp = board[xPos][yPos + 1];
				board[xPos][yPos + 1] = board[xPos][yPos];
				board[xPos][yPos] = temp;

				//if this board is not on the open or closed list, or on them but with a lower manhattan value, add it to the open list

				found = false;

				if ( !openList.empty() )
					{

					for ( k = 0; k!= openList.size(); k++ )
						if ( openList[k].gameBoard[0][0] == board[0][0] && openList[k].gameBoard[0][1] == board[0][1] &&
						openList[k].gameBoard[0][2] == board[0][2] && openList[k].gameBoard[1][0] == board[1][0] &&
						openList[k].gameBoard[1][1] == board[1][1] && openList[k].gameBoard[1][2] == board[1][2] &&
						openList[k].gameBoard[2][0] == board[2][0] && openList[k].gameBoard[2][1] == board[2][1] &&
						openList[k].gameBoard[2][2] == board[2][2] )
							{
							
							if ( openList[k].manhattan >= upVal )
								{
								found = true;
								}

							}
					}

				if ( !closedList.empty() )
					{

					for ( k = 0; k!= closedList.size(); k++ )
						if ( closedList[k].gameBoard[0][0] == board[0][0] && closedList[k].gameBoard[0][1] == board[0][1] &&
						closedList[k].gameBoard[0][2] == board[0][2] && closedList[k].gameBoard[1][0] == board[1][0] &&
						closedList[k].gameBoard[1][1] == board[1][1] && closedList[k].gameBoard[1][2] == board[1][2] &&
						closedList[k].gameBoard[2][0] == board[2][0] && closedList[k].gameBoard[2][1] == board[2][1] &&
						closedList[k].gameBoard[2][2] == board[2][2] )
							{

							if ( closedList[k].manhattan >= upVal )
								{
								found = true;
								}
							}
					}

				//if this node passed the search, add it to the open list

				if ( found == false )
					{

					for ( i = 0; i < 3; i++ )
						for ( j = 0; j < 3; j++ )
							copy.gameBoard[i][j] = board[i][j];

					copy.manhattan = rightVal;

					openList.push_back(copy);

					}

				//replace board

				temp = board[xPos][yPos + 1];
				board[xPos][yPos + 1] = board[xPos][yPos];
				board[xPos][yPos] = temp;

				}

		//sort the open list so the lowest manhattan value is at the head

		if ( !openList.empty() )
			{
			sort( openList.begin(), openList.end(), compareByManhattan );
			}

		//iterate ++, to move towards exit if no solution

		iterations++;

	}


if ( iterations < 100 )
cout << "success?" << endl;

else
cout << "an epic fail..." << endl;



	//Cleanup
	//-------------------------------------
	EndLogging();
	getchar();
	//-------------------------------------
	return 0;
}
