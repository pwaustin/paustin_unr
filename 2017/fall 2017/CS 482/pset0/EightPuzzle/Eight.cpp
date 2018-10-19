#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>
#include <stdio.h>
using namespace std;


//global denoting how many tries to search for a solution before giving up
const int MAX_ITERATIONS = 1000;

//The 2D board for our 8-puzzle in format board[x][y]
int** board;

//The output logging file. Don't worry about this one
FILE* output;

//node data structure: a game board, the previous board, the number of moves so far, the manhattan distance to solution and the heuristic value
struct node
{

	int predBoard[3][3];
	int gameState[3][3];
	int moves;
	int manhattan;
	int heuristic;

};

//vectors of nodes: open and closed list for A* search

vector<node> openList;
vector<node> closedList;

//== comparison operator for nodes: for our purposes, a == b if they have the same board and a's heuristic is worse than or equal to b's

bool operator==(const node& a, const node& b)
{

	if ( a.gameState[0][0] == b.gameState[0][0] && a.gameState[0][1] == b.gameState[0][1] && a.gameState[0][2] == b.gameState[0][2] &&
		a.gameState[1][0] == b.gameState[1][0] && a.gameState[1][1] == b.gameState[1][1] && a.gameState[1][2] == b.gameState[1][2] &&
		a.gameState[2][0] == b.gameState[2][0] && a.gameState[2][1] == b.gameState[2][1] && a.gameState[2][1] == b.gameState[2][1] )
			{
				if (a.heuristic >= b.heuristic )
					return true; 
			}

	return false;

}

//!= comparison operator for nodes: nodes aren't equal if their boards aren't the same

bool operator!=(const node& a, const node& b)
{

if ( a.gameState[0][0] == b.gameState[0][0] && a.gameState[0][1] == b.gameState[0][1] && a.gameState[0][2] == b.gameState[0][2] &&
	a.gameState[1][0] == b.gameState[1][0] && a.gameState[1][1] == b.gameState[1][1] && a.gameState[1][2] == b.gameState[1][2] &&
	a.gameState[2][0] == b.gameState[2][0] && a.gameState[2][1] == b.gameState[2][1] && a.gameState[2][1] == b.gameState[2][1] )
		{

				return false; 
		}

	return true;

}

//comparison function for node sorting: sort by heuristic value, low to high

bool compareByHeuristic(const node& a, const node& b)
	{

	return a.heuristic < b.heuristic;

	}

//given a board, calculate its manhattan distance from the solution board. solution board will return 0

int calcDistance(int state[3][3])
{

	int manhattan = 0;
	int distX;
	int distY;

	for ( int x = 0; x < 3; x++ )
		{

		for ( int y = 0 ; y < 3; y++ )
			{

			if ( state[x][y] != 0 )
				{
		
				distX = x - ( state[x][y] ) / 3;
				distY = y - ( state[x][y] ) % 3;
				manhattan += abs(distX) + abs(distY);

				}

			}

		}

	return manhattan;

}

//provided functions:

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

//end provided functions

int main(int argc, char** argv)
{

//Setup: given
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

//My code here
	
	//declare variables

	stack<node> solutionList;
	node currentBoard;
	node originalBoard;
	node tempNode;
	bool found;
	int temp;
	int iterations;
	int xPos;
	int yPos;
	int i;
	int j;
	int k;

	//reconfigure original board to match file layout - swap at non-diagonals

	temp = board[0][1];
	board[0][1] = board[1][0];
	board[1][0] = temp;

	temp = board[0][2];
	board[0][2] = board[2][0];
	board[2][0] = temp;

	temp = board[1][2];
	board[1][2] = board[2][1];
	board[2][1] = temp;

	//prepare initial state node, push it to the open list

	for ( i = 0; i < 3; i++ )
		for ( j = 0; j < 3; j ++ )
			{
			currentBoard.gameState[i][j] = board[i][j];
			originalBoard.gameState[i][j] = board[i][j];
			}

	currentBoard.manhattan = calcDistance(currentBoard.gameState);
	originalBoard.manhattan = calcDistance(originalBoard.gameState);
	originalBoard.moves = 0;

	openList.push_back(currentBoard);

	iterations = 0;

	//until a board is found with 0 manhattan value, or we give up, loop

	while ( openList.front().manhattan != 0 && iterations < MAX_ITERATIONS )
		{

		//take the top of the open list, remove it, send it to the closed list

		currentBoard = openList.front();

		openList.erase(openList.begin());

		closedList.push_back(currentBoard);

		//get the location of 0 on this board

		for ( i = 0; i < 3; i++ )
			for ( j = 0; j < 3; j++ )
				{

				if ( currentBoard.gameState[i][j] == 0 )
					{
					xPos = i;
					yPos = j;
					}

				}

		//consider moves: up, if possible

		if ( xPos != 0 )
			{

			//calculate a node after moving up
 
			for ( i = 0; i < 3; i++ )
				for ( j = 0; j < 3; j++ )
					{
					tempNode.predBoard[i][j] = currentBoard.gameState[i][j];
					tempNode.gameState[i][j] = currentBoard.gameState[i][j];
					}

			temp = tempNode.gameState[xPos - 1][yPos];
			tempNode.gameState[xPos - 1][yPos] = tempNode.gameState[xPos][yPos];
			tempNode.gameState[xPos][yPos] = temp;

			tempNode.manhattan = calcDistance(tempNode.gameState);
			tempNode.moves = currentBoard.moves++;
			tempNode.heuristic = tempNode.manhattan + tempNode.moves;

			//search the open and closed lists for this node (same board w/ same or better heuristic). if not found, push to open list

			found = false;

			for ( k = 0; k < openList.size(); k++ )
				{
				
				if ( tempNode == openList[k] )
					found = true;

				}

			for ( k = 0; k < closedList.size(); k++ )
				{
				
				if ( tempNode == closedList[k] )
					found = true;

				}

			if ( found == false )
				openList.push_back(tempNode);

			}

		//consider down, left, right

		if ( xPos != 2 )
			{
			for ( i = 0; i < 3; i++ )
				for ( j = 0; j < 3; j++ )
					{
					tempNode.predBoard[i][j] = currentBoard.gameState[i][j];
					tempNode.gameState[i][j] = currentBoard.gameState[i][j];
					}


			temp = tempNode.gameState[xPos + 1][yPos];
			tempNode.gameState[xPos + 1][yPos] = tempNode.gameState[xPos][yPos];
			tempNode.gameState[xPos][yPos] = temp;

			tempNode.manhattan = calcDistance(tempNode.gameState);
			tempNode.moves = currentBoard.moves++;
			tempNode.heuristic = tempNode.manhattan + tempNode.moves;

			found = false;

			for ( k = 0; k < openList.size(); k++ )
				{
				
				if ( tempNode == openList[k] )
					found = true;

				}

			for ( k = 0; k < closedList.size(); k++ )
				{
				
				if ( tempNode == closedList[k] )
					found = true;

				}

			if ( found == false )
				openList.push_back(tempNode);

			}

		if ( yPos != 0 )
			{
			for ( i = 0; i < 3; i++ )
				for ( j = 0; j < 3; j++ )
					{
					tempNode.predBoard[i][j] = currentBoard.gameState[i][j];
					tempNode.gameState[i][j] = currentBoard.gameState[i][j];
					}


			temp = tempNode.gameState[xPos][yPos - 1];
			tempNode.gameState[xPos][yPos - 1] = tempNode.gameState[xPos][yPos];
			tempNode.gameState[xPos][yPos] = temp;

			tempNode.manhattan = calcDistance(tempNode.gameState);
			tempNode.moves = currentBoard.moves++;
			tempNode.heuristic = tempNode.manhattan + tempNode.moves;

			found = false;

			for ( k = 0; k < openList.size(); k++ )
				{
				
				if ( tempNode == openList[k] )
					found = true;

				}

			for ( k = 0; k < closedList.size(); k++ )
				{
				
				if ( tempNode == closedList[k] )
					found = true;

				}

			if ( found == false )
				openList.push_back(tempNode);

			}

		if ( yPos != 2 )
			{
			for ( i = 0; i < 3; i++ )
				for ( j = 0; j < 3; j++ )
					{
					tempNode.predBoard[i][j] = currentBoard.gameState[i][j];
					tempNode.gameState[i][j] = currentBoard.gameState[i][j];
					}

			
			temp = tempNode.gameState[xPos][yPos + 1];
			tempNode.gameState[xPos][yPos + 1] = tempNode.gameState[xPos][yPos];
			tempNode.gameState[xPos][yPos] = temp;

			tempNode.manhattan = calcDistance(tempNode.gameState);
			tempNode.moves = currentBoard.moves++;
			tempNode.heuristic = tempNode.manhattan + tempNode.moves;

			found = false;

			for ( k = 0; k < openList.size(); k++ )
				{
				
				if ( tempNode == openList[k] )
					found = true;

				}

			for ( k = 0; k < closedList.size(); k++ )
				{
				
				if ( tempNode == closedList[k] )
					found = true;

				}

			if ( found == false )
				openList.push_back(tempNode);

			}

		//sort the open list for the lowest heuristic value- that one will be considered next. If the solution was found the final board will be at the front of the open list

		if ( !openList.empty() )
			{
			sort( openList.begin(), openList.end(), compareByHeuristic );
			}

		iterations++;

		}

	//if successful, backtrack through the closed list for matching predecessors until you find the original board. add each to a stack- original board will be on top, final on bottom

	if ( iterations < MAX_ITERATIONS )
		{

		solutionList.push(openList.front());

		while ( solutionList.top() != originalBoard )
			{

			for ( k = 0; k!= closedList.size(); k++ )
				{
		
				if ( solutionList.top().predBoard[0][0] == closedList[k].gameState[0][0] && solutionList.top().predBoard[0][1] == closedList[k].gameState[0][1] &&
					solutionList.top().predBoard[0][2] == closedList[k].gameState[0][2] && solutionList.top().predBoard[1][0] == closedList[k].gameState[1][0] &&
					solutionList.top().predBoard[1][1] == closedList[k].gameState[1][1] && solutionList.top().predBoard[1][2] == closedList[k].gameState[1][2] &&
					solutionList.top().predBoard[2][0] == closedList[k].gameState[2][0] && solutionList.top().predBoard[2][1] == closedList[k].gameState[2][1] &&
					solutionList.top().predBoard[2][2] == closedList[k].gameState[2][2] )
						{

						solutionList.push(closedList[k]);

						}

				}

			}

		//now, print each move 0 makes on the board using the stack- will start from the first move
		//loop while stack not empty

		int curXPos;
		int curYPos;
		int sucXPos;
		int sucYPos;

		while ( !solutionList.empty() )
			{

			for ( i = 0; i < 3; i++ )
				for ( j = 0; j < 3; j++ )
					{
					if ( solutionList.top().gameState[i][j] == 0 )
						{
						curXPos = i;
						curYPos = j;
						}
					} 

			solutionList.pop();

			//take 0 location of new top

			if ( !solutionList.empty() )
				{

				for ( i = 0; i < 3; i++ )
					for ( j = 0; j < 3; j++ )
						{
						if ( solutionList.top().gameState[i][j] == 0 )
							{
							sucXPos = i;
							sucYPos = j;
							}
						} 
				}

				//compare current/successor 0 positions, output the move

				if ( curXPos == sucXPos + 1 )
					cout << "UP" << endl;

				else if ( curXPos == sucXPos - 1 )
					cout << "DOWN" << endl;

				else if ( curYPos == sucYPos + 1 )
					cout << "LEFT" << endl;

				else if ( curYPos == sucYPos - 1 )
					cout << "RIGHT" << endl;

				}			

					
		}

	else //otherwise, failure
		{
		}
	


//Cleanup
	//-------------------------------------
	EndLogging();
	getchar();
	//-------------------------------------
	return 0;
}


