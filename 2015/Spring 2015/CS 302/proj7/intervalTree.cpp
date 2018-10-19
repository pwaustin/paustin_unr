/** CS 302 Project 7 - scheduling with red black trees, class implementation
@file intervalTree.cpp
@author Patrick Austin
@date 4/29/2015 */

#include "intervalTree.h"
#include <iostream>
using namespace std;

//binary node implementation

/** Binary node default constructor. Sets left/right/parent pointers to null and does not assign data. Node is red by default.
@pre None.
@post Object created with left/right/parent pointers set to null, color red.
@return None. */

BinaryNode::BinaryNode()
	{

	//no data, set pointers to null

	start = max = end = 0;

	setRed();

	leftChildPtr = nullptr;

	rightChildPtr = nullptr;

	parentPtr = nullptr;

	}

/** Binary node setStart function. Sets the data stored by the start member of the node to the specified value. 
@pre None.
@post Start data member holds target value
@param target The data start should contain.
@return None. */

void BinaryNode::setStart (const int& target)
	{

	start = target;

	}

/** Binary node getStart function. Returns the data stored in the node's start data member.
@pre None.
@post Data stored in start data member of the node returned. Node contents unchanged.
@return int The value stored in the node's start data member. */

int BinaryNode::getStart () const
	{

	return start;

	}

/** Binary node setEnd function. Sets the data stored by the end member of the node to the specified value. 
@pre None.
@post End data member holds target value
@param target The data end should contain.
@return None. */

void BinaryNode::setEnd (const int& target)
	{

	end = target;

	}

/** Binary node getEnd function. Returns the data stored in the node's end data member.
@pre None.
@post Data stored in end data member of the node returned. Node contents unchanged.
@return int The value stored in the node's end data member. */

int BinaryNode::getEnd () const
	{

	return end;

	}

/** Binary node setMax function. Sets the data stored by the max member of the node to the specified value. 
@pre None.
@post Max data member holds target value
@param target The data max should contain.
@return None. */

void BinaryNode::setMax (const int& target)
	{

	max = target;

	}

/** Binary node getMax function. Returns the data stored in the node's max data member.
@pre None.
@post Data stored in max data member of the node returned. Node contents unchanged.
@return int The value stored in the node's max data member. */

int BinaryNode::getMax () const
	{

	return max;

	}

/** Binary node isRed function. Returns whether the node is red or not.
@pre None. Nodes default to black when created.
@post Bool returned. Node contents unchanged.
@return bool Whether the node is red or not. */

bool BinaryNode::isRed () const
	{

	return ( !color );

	}

/** Binary node isBlack function. Returns whether the node is black or not.
@pre None. Nodes default to black when created.
@post Bool returned. Node contents unchanged.
@return bool Whether the node is black or not. */

bool BinaryNode::isBlack () const
	{

	return ( color );

	}

/** Binary node setRed function. Sets the color of the node to red.
@pre None. Nodes default to red when created.
@post Color value of the node set to red.
@return None. */

void BinaryNode::setRed ()
	{

	color = false;

	}

/** Binary node setBlack function. Sets the color of the node to black.
@pre None. Nodes default to black when created.
@post Color value of the node set to black.
@return None. */

void BinaryNode::setBlack ()
	{

	color = true;

	}

/** Binary node setLeftChildPtr function.
@pre None.
@post leftChildPtr of the node set to specified value.
@param leftPtr The pointer the left pointer value of the node should store. 
@return None. */

void BinaryNode::setLeftChildPtr (BinaryNode* leftPtr)
	{

	leftChildPtr = leftPtr;

	}

/** Binary node getLeftChildPtr function.
@pre None.
@post leftChildPtr of the node returned; node contents unchanged
@return BinaryNode* The left child pointer. */

BinaryNode* BinaryNode::getLeftChildPtr () const
	{

	return leftChildPtr;

	}

/** Binary node setRightChildPtr function.
@pre None.
@post rightChildPtr of the node set to specified value.
@param rightPtr The pointer the right pointer value of the node should store. 
@return None. */

void BinaryNode::setRightChildPtr (BinaryNode* rightPtr)
	{

	rightChildPtr = rightPtr;

	}

/** Binary node getRightChildPtr function.
@pre None.
@post rightChildPtr of the node returned; node contents unchanged
@return BinaryNode* The right child pointer. */

BinaryNode* BinaryNode::getRightChildPtr () const
	{

	return rightChildPtr;

	}

/** Binary node setParentPtr function.
@pre None.
@post parentPtr of the node set to specified value.
@param parentNodePtr The pointer the right pointer value of the node should store. 
@return None. */

void BinaryNode::setParentPtr (BinaryNode* parentNodePtr)
	{

	parentPtr = parentNodePtr;
	
	}

/** Binary node getParentPtr function.
@pre None.
@post getParentPtr of the node returned; node contents unchanged
@return BinaryNode* The parent child pointer. */

BinaryNode* BinaryNode::getParentPtr () const
	{

	return parentPtr;

	}

//end binary node implementation

//interval tree implementation

/**Interval tree insertInorder helper function. Called by add function to add nodes to the tree.
@pre Node z contains valid data (no duplicate start values allowed), has null children.
@post Node added to the interval tree with sorted property maintained and max values updated.
@param z The node to be added.
@return None. */

void IntervalTree::insertInorder( BinaryNode* z )
	{

	//y will be x's parent

	BinaryNode* y = nullptr;

	//x will start at the root

	BinaryNode* x = rootPtr;

	//continue until you hit null

	while ( x != nullptr )
		{

		// y = x

		y = x;

		//if key value of z < key value of x, x goes left

		if ( z->getStart() < x->getStart() )
			x = x->getLeftChildPtr();

		//otherwise, x goes right

		else
			x = x->getRightChildPtr();

		}

	//make y the parent of z

	z->setParentPtr(y);

	//if y is null, z is the root

	if ( y == nullptr )
		rootPtr = z;

	//if key value of z < key value of y, z is y's left child

	else if ( z->getStart() < y->getStart() )
		y->setLeftChildPtr(z);

	//otherwise, z is y's right child

	else
		y->setRightChildPtr(z);

	//z's will have null children and be red

	z->setLeftChildPtr(nullptr);

	z->setRightChildPtr(nullptr);

	z->setRed();

	//fix the tree to make sure it still satisfies red/black tree rules

	fixTree(z);

	//fix the max values of the nodes to account for the new value and any shuffling in the tree

	fixMax(rootPtr);

	}

/**Interval tree fixTree helper function. Called by insertInorder function to maintain red/black
tree properties after a new node has been added.
@pre Node z contains valid data and has just been added to a previously valid red/black tree.
@post Tree color and orientation potentially altered in order to maintain red/black tree rules.
@param z The node which has been added to the tree, from which the fixing of the tree will begin.
@return None. */

void IntervalTree::fixTree( BinaryNode* z )
	{

	BinaryNode* y;

	//continue the fixing process while z's parent is not null && it is red

	while ( z->getParentPtr() != nullptr && z->getParentPtr()->isRed() )
		{

		//if z's parent is the left child of z's grandparent...

		if ( z->getParentPtr() == z->getParentPtr()->getParentPtr()->getLeftChildPtr() )
			{

			//y is z's uncle

			y = z->getParentPtr()->getParentPtr()->getRightChildPtr();

			if ( y != nullptr && y->isRed() )
				{

				//case 1 - z's uncle is red

				z->getParentPtr()->setBlack();

				y->setBlack();

				z->getParentPtr()->getParentPtr()->setRed();

				z = z->getParentPtr()->getParentPtr();

				}

			else
				{

				if ( z == z->getParentPtr()->getRightChildPtr() )
					{

					//case 2 - z's uncle is black and z is a right child

					z = z->getParentPtr();

					rotateLeft(z);

					}

				//case 3 - z's uncle is black and z is a left child

				z->getParentPtr()->setBlack();

				z->getParentPtr()->getParentPtr()->setRed();

				rotateRight( z->getParentPtr()->getParentPtr() );

				}

			}

		//otherwise, z's parent is the right child of z's grandparent

		else
			{

			//y is z's uncle

			y = z->getParentPtr()->getParentPtr()->getLeftChildPtr();

			if ( y != nullptr && y->isRed() )
				{

				//case 1 - z's uncle is red

				z->getParentPtr()->setBlack();

				y->setBlack();

				z->getParentPtr()->getParentPtr()->setRed();

				z = z->getParentPtr()->getParentPtr();

				}

			else 
				{

				if ( z == z->getParentPtr()->getLeftChildPtr() )
					{

					//case 2 - z's uncle is black, z is a left child

					z = z->getParentPtr();

					rotateRight(z);

					}

				//case 3- z's uncle is black, z is a right child

				z->getParentPtr()->setBlack();

				z->getParentPtr()->getParentPtr()->setRed();

				rotateLeft( z->getParentPtr()->getParentPtr() );

				}

			}

		}

	//set root to black

	rootPtr->setBlack();

	}

/**Interval tree rotateLeft helper function. Used by fixTree function in some situations in order
to re-orient the tree so that red/black rules can be maintained.
@pre Node x is in the previously valid red/black tree.
@post x rotated left in the tree- data maintained, just re-oriented.
@param x The node to rotate left.
@return None. */

void IntervalTree::rotateLeft ( BinaryNode* x )
	{

	//set y to x's right child

	BinaryNode* y = x->getRightChildPtr();

	//set y's left child to x's right child

	x->setRightChildPtr( y->getLeftChildPtr() );

	//if y's left child is not null, set y's left child to have parent x

	if ( y->getLeftChildPtr() != nullptr )
		y->getLeftChildPtr()->setParentPtr(x);

	//set y's parent to x's parent

	y->setParentPtr( x->getParentPtr() );

	//if x's parent is null, set the rootPtr to y

	if ( x->getParentPtr() == nullptr )
		rootPtr = y;

	//if x is the left child of its parent, set the left child of x's parent to y

	else if ( x == x->getParentPtr()->getLeftChildPtr() )
		x->getParentPtr()->setLeftChildPtr(y);

	//otherwise, set the right child of x's parent to y

	else
		x->getParentPtr()->setRightChildPtr(y);

	//set the left child of y to x

	y->setLeftChildPtr(x);

	//make y the parent of x

	x->setParentPtr(y);

	}

/**Interval tree rotateRight helper function. Used by fixTree function in some situations in order
to re-orient the tree so that red/black rules can be maintained.
@pre Node x is in the previously valid red/black tree.
@post x rotated right in the tree- data maintained, just re-oriented.
@param x The node to rotate right.
@return None. */

void IntervalTree::rotateRight ( BinaryNode* x )
	{

	//set y to x's left child

	BinaryNode* y = x->getLeftChildPtr();

	//set x's left child to y's right child

	x->setLeftChildPtr( y->getRightChildPtr() );

	//if y's right child is not null, set y's right child to have parent x

	if ( y->getRightChildPtr() != nullptr )
		y->getRightChildPtr()->setParentPtr(x);

	//set y's parent to x's parent

	y->setParentPtr ( x->getParentPtr() );

	//if x's parent is null, set the rootPtr to y

	if ( x->getParentPtr() == nullptr )
		rootPtr = y;
	
	//if x is the right child of its parent, set the right child of x's parent to y

	else if ( x == x->getParentPtr()->getRightChildPtr() )
		x->getParentPtr()->setRightChildPtr(y);

	//otherwise, set the left child of x's parent to y

	else
		x->getParentPtr()->setLeftChildPtr(y);

	//set the right child of y to x

	y->setRightChildPtr(x);

	//make y the parent of x

	x->setParentPtr(y);

	}

/**Interval tree fixMax helper function. After a node has been added to the
tree and the tree has been re-oriented to maintain red/black rules, adjusts max
values in the nodes above it if necessary, denoting the larget value in the subtree.
Uses recursion.
@pre Node z has been added to the tree and the tree has been fixed to maintain
red/black rules.
@post Max values in the parent, grandparent, etc. nodes of this one adjusted if appropriate.
@param z The node that has been added.
@return None. */

void IntervalTree::fixMax( BinaryNode* z )
	{

	if ( z != nullptr )
		{

		//process the children first so any adjustments necessary to their maxes will bubble up

		fixMax(z->getLeftChildPtr() );
		fixMax(z->getRightChildPtr() );

		//get the max values of this node's children if it has children

		int leftMax = 0;
		int rightMax = 0;
		
		if ( z->getLeftChildPtr() != nullptr )
			leftMax = z->getLeftChildPtr()->getMax();

		if ( z->getRightChildPtr() != nullptr )
			rightMax = z->getRightChildPtr()->getMax();

		//get the max between the children

		int childrenMax = max( leftMax, rightMax );

		//set this node's max to whatever's larger: the max of the children or the end value of this node

		z->setMax( max( z->getEnd(), childrenMax ) );

		}

	}

/**Interval tree getHeight helper function. Used in preorder traversal to show the height of
the nodes in the tree. Uses recursion. Note that height for a non-null node is the taller of its subtrees
plus one. IE a node with height 3 can have a height 2 child and a height 1 child, etc.
@pre None.
@post Height of this subtree returned.
@param subTreePtr The subtree to check.
@return int The height of the subtree. */

int IntervalTree::getHeight ( BinaryNode* subTreePtr ) const
	{

	//if nullptr, subtree has height 0

	if ( subTreePtr == nullptr )
		return 0;

	//if not nullptr, this tree has height 1 plus the height of its tallest subtree

	else
		{

		return ( 1 + max( getHeight( subTreePtr->getLeftChildPtr() ), getHeight( subTreePtr->getRightChildPtr() ) ) );

		}

	}

/**Interval tree preorder helper function. Used by public preorder traversal function. Uses recursion.
Displays start, end, max, color, and height for each node in preorder order (root, left, right).
@pre None.
@post Tree contents unchanged; values of each node printed to console.
@param treePtr The tree to visit.
@return None. */

void IntervalTree::preorder ( BinaryNode* treePtr ) const
	{

	//visit root, then left, then right

	if (treePtr != nullptr)
		{

		//visit this node: display the three values in the node plus the node's color and height

		cout << "Start: " << treePtr->getStart() << " ";

		cout << "End: " << treePtr->getEnd() << " ";

		cout << "Max: " << treePtr->getMax() << " ";

		cout << "Color: ";

		if ( treePtr->isBlack() )
			cout << "Black ";

		else
			cout << "Red " ;

		cout << "Height: " << getHeight(treePtr) << endl;

		//visit left

		preorder (treePtr->getLeftChildPtr() );

		//visit right

		preorder (treePtr->getRightChildPtr() );

		}

	}

/**Interval tree clear helper function. Used by the destructor to deallocate
dynamic memory used in the tree. Uses recursion.
@pre None.
@post Dynamic memory deallocated, tree contents destroyed and returned to empty state.
@param treePtr The tree to visit.
@return None. */

void IntervalTree::clear ( BinaryNode* treePtr )
	{

	//if not nullptr, process any subtrees then destroy this node

	if ( treePtr != nullptr )
		{

		clear ( treePtr->getLeftChildPtr() );
		clear ( treePtr->getRightChildPtr() );
		delete treePtr;

		}

	treePtr = nullptr;

	}

/**Interval tree searchHelper helper function. Used by the public search method to
find a node that overlaps with the interval specified, if there is one.
@pre s <= e
@post Node returned if found; else nullptr returned; tree contents unchanged.
@param s The start of the interval to search for.
@param e The end of the interval to search for.
@return BinaryNode* The overlapping node that was found if found, null otherwise. */

BinaryNode* IntervalTree::searchHelper ( const int& s, const int& e ) const
	{

	//start at the root

	BinaryNode* x = rootPtr;

	//search until you hit null or an overlap

	while ( x != nullptr && ( e < x->getStart() || x->getEnd() < s ) )
		{

		//if not null and max >= s, go left

		if ( x->getLeftChildPtr() != nullptr && x->getLeftChildPtr()->getMax() >= s )
			x = x->getLeftChildPtr();

		//otherwise go right

		else
			x = x->getRightChildPtr();

		}

	//return x- will point to the overlapping node if found, or null if not found

	return x;

	}

/** Interval tree default constructor. Creates and sets tree to empty.
@pre None.
@post Empty tree created.
@return None. */

IntervalTree::IntervalTree()
	{

	//set root to null, denoting empty

	rootPtr = nullptr;

	}

/** Interval tree destructor. Uses clear helper function to deallocate dynamic
memory used for the tree.
@pre None.
@post Dynamic memory used in the tree freed.
@return None. */

IntervalTree::~IntervalTree()
	{

	//call clear helper function to destroy all nodes

	clear(rootPtr);

	}

/** Interval tree isEmpty function. Returns true if empty, false if not.
@pre None.
@post bool denoting emptiness returned; tree contents unchanged.
@return bool True if empty, false if not empty. */

bool IntervalTree::isEmpty() const
	{

	//tree is empty if root is null

	return ( rootPtr == nullptr );

	}

/** Interval tree add function. Adds an interval to the tree. Uses insertInorder,
fixTree, rotateLeft, rotateRight, fixMax helper functions to maintain sorted and red/black
properties in the tree and maintain correct max values in the nodes.
@pre s <= e
@post Interval added to the tree.
@param s The start of the interval to add.
@param e The end of the interval to add.
@return bool Returns true, denoting successful add. */

bool IntervalTree::add ( const int& s, const int& e )
	{

	//create a new node with start = s, end = e, max = e

	BinaryNode* newNodePtr = new BinaryNode();

		newNodePtr->setStart(s);

		newNodePtr->setEnd(e);

		newNodePtr->setMax(e);

	//insert the node into the interval tree

	insertInorder( newNodePtr );

	//return true

	return true;

	}

/** Interval tree search function. Searches for an interval overlapping with the
specified interval within the interval tree. Uses searchHelper helper function to find
an overlapping node if there is one.
@pre s <= e
@post If an overlapping interval has been found, returns true and updates foundS and
foundE variables to contain the start and end of the interval found. If no overlapping
interval found, returns false and does not update foundS and foundE from the provided
values. Tree contents are unchanged by search process.
@param s The start of the interval to search for.
@param e The end of the interval to search for.
@param foundS If the search is successful, this value will be updated to contain the start
of the found interval. If search is unsuccessful, this value is not updated.
@param foundE If the search is successful, this value will be updated to contain the end of
the found interval. If search is unsuccessful, this value is not updated.
@return bool True if an overlapping interval was found, false if not. */

bool IntervalTree::search( const int& s, const int& e, int& foundS, int& foundE )
	{

	//conduct the search using searchHelper

	BinaryNode* result = searchHelper(s, e);

	//if result was not null, an overlap was found - update foundS and foundE with start and end
	//values from the found node, return true

	if ( result != nullptr )
		{

		foundS = result->getStart();

		foundE = result->getEnd();

		return true;

		}

	//otherwise result was null - do not update foundS and foundE, return false

	else
		return false;

	}

/** Interval tree preorder traversal function. Uses preorder helper function. Visits the nodes in
the tree in preorder order (root, left, right) and prints the start, end, max, color, and height of
each node to console.
@pre None.
@post Values of the nodes printed to console; tree contents unchanged.
@return None. */

void IntervalTree::preorderTraverse() const
	{

	//call preorder helper function, starting at the root

	preorder(rootPtr);

	}
