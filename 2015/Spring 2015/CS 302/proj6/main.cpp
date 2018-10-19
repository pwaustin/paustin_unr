/** CS 302 Project 6 - binary search tree test program
@file main.cpp
@author Patrick Austin
@date 4/13/2015 */

#include "binarySearchTree.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

/** Visit function for use with inorder/preorder/postorder traversals of the BSTs.
@pre None.
@post Visited value will be printed to console.
@param val The value of the visited item in the BST.
@return None. */

template <class ItemType>
void my_visit(ItemType& val);

/** As per prompt, this program will...

    Randomly generate 100 unique values in the range of [1-200] and insert them into a binary search tree (BST1). Print height and inorder output of the BST1 tree.
    Randomly generate 10 unique values in the range of [1-200] where there is an overlap with the previous values and insert them into another binary search tree (BST2). 
	Print preorder, inorder, and postorder output of the BST2 tree.
    Find and remove any values of BST2 from BST1. Print height, number of nodes, and inorder output of the modified BST1 tree.
    Clear the binary search trees. Print whether trees are empty before and after clear operation.

*/

int main()
	{

	//seed random number generator, allocate arrays, declare variables

	srand( time(NULL) );

	int tree1Values[100];

	int tree2Values[10];

	int index;

	int index2;

	int temp;

	bool unique;

	bool overlap;

	//print title

	cout << endl << "CS 302 Project 6: Binary Search Tree Testing Program" << endl << endl;

	//generate 100 random values, put them in tree1Values array

	cout << "Generating 100 unique random values from range 1 - 200 ..." << endl;

	cout << "The values are:" << endl;

	for ( index = 1; index <= 100; index++ )
		{

		//generate a unique value

		unique = false;

		while ( !unique )
			{

			unique = true;

			temp = 1 + ( rand() % 200 );

			for ( index2 = 0; index2 < index - 1; index2++ )
				{

				if ( temp == tree1Values[index2] )
					unique = false;

				}

			}

		//add the unique value to the array

		tree1Values[index-1] = temp;

		//display the value

		cout << tree1Values[index - 1] << '\t';

		if ( index % 10 == 0 )
			cout << endl;

		}

	cout << endl;

	//create BST 1 and add the values from the tree1Values array

	cout << "Adding the values to BST 1 ..." << endl << endl;

	BinarySearchTree<int> test1;

	for ( index = 0; index < 100; index++ )
		test1.add( tree1Values[index] );

	//print the height of the tree

	cout << "BST 1 height = " << test1.getHeight() << endl << endl;

	//print the inorder output of BST1

	cout << "BST 1 print (inorder): " << endl; 

	test1.inorderTraverse(my_visit);

	cout << endl << endl;

	//generate 10 random values, put them in tree2Values array

	cout << "Generating 10 unique random values from range 1 - 200, where at least one value is also in BST 1 ..." << endl;

	cout << "The values are:" << endl;

	overlap = false;

	while ( !overlap )
		{

		for ( index = 1; index <= 10; index++ )
			{

			//generate a unique value

			unique = false;

			while ( !unique )
				{

				unique = true;

				temp = 1 + ( rand() % 200 );

				for ( index2 = 0; index2 < index - 1; index2++ )
					{

					if ( temp == tree2Values[index2] )
						unique = false;

					}

				}

			//add the unique value to the array

			tree2Values[index-1] = temp;

			//see if there is overlap

			if ( !overlap )
				{

				for ( index2 = 0; index2 < 100 ; index2++ )
					{

					if ( temp == tree1Values[index2] )
						overlap = true;
					
					}

				}

			}

		}

	//display the values

	for ( index = 0; index < 10; index++ )
		cout << tree2Values[index] << '\t';

	cout << endl << endl;

	//add the values to BST 2

	cout << "Adding the values to BST 2 ..." << endl << endl;

	BinarySearchTree<int> test2;

	for ( index = 0; index < 10; index++ )
		test2.add( tree2Values[index] );

	//print the preorder, inorder, and postorder outputs of BST2

	cout << "BST 2 print (preorder): " << endl; 

	test2.preorderTraverse(my_visit);

	cout << endl << endl;

	cout << "BST 2 print (inorder): " << endl; 

	test2.inorderTraverse(my_visit);

	cout << endl << endl;

	cout << "BST 2 print (postorder): " << endl; 

	test2.postorderTraverse(my_visit);

	cout << endl << endl;

	//remove the values in BST2 from BST1

	cout << "Removing values contained in BST 2 from BST 1 ..." << endl << endl;

	for ( index = 0; index < 10; index++ )
		test1.remove( tree2Values[index] );

	//print info about BST1 after removals

	cout << "After removal(s), BST 1 height = " << test1.getHeight() << endl << endl;

	cout << "After removal(s), BST 1 number of nodes = " << test1.getNumberOfNodes() << endl << endl;

	cout << "After removal(s), BST 1 print (inorder): " << endl;

	test1.inorderTraverse(my_visit);

	cout << endl << endl;

	//see if trees are empty

	cout << "Is BST 1 empty? ";

		if ( test1.isEmpty() )
			cout << "Yes." << endl;

		else
			cout << "No." << endl;

		cout << "Is BST 2 empty? ";

		if ( test2.isEmpty() )
			cout << "Yes." << endl;

		else
			cout << "No." << endl;

	cout << endl;

	//clear the trees

	cout << "Clearing BST 1 ... " << endl;
		
	test1.clear();

	cout << "Clearing BST 2 ... " << endl << endl;

	test2.clear();

	//see if trees are empty

	cout << "Is BST 1 empty? ";

		if ( test1.isEmpty() )
			cout << "Yes." << endl;

		else
			cout << "No." << endl;

		cout << "Is BST 2 empty? ";

		if ( test2.isEmpty() )
			cout << "Yes." << endl;

		else
			cout << "No." << endl;

	cout << endl;

	//end program

	cout << "Ending Binary Search Tree Testing Program ..." << endl << endl;

	return 0;

	}

template <class ItemType>
void my_visit(ItemType& val)
	{
	cout << val << ' ';
	}
