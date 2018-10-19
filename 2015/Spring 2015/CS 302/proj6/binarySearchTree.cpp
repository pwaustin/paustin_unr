/** CS 302 Project 6 - binary tree class implementations
@file binarySearchTree.cpp
@author Patrick Austin
@date 4/13/2015 */

#include "binarySearchTree.h"
#include <iostream>
using namespace std;

//binary node implementation

/** Binary node default constructor. Sets left and right pointers to null and does not assign data.
@pre None.
@post Object created with left and right pointers set to null.
@return None. */

template < class ItemType > 
BinaryNode<ItemType>::BinaryNode()
	{

	//no data, set left and right to null

	leftChildPtr = nullptr;

	rightChildPtr = nullptr;

	}

/** Binary node parameterized constructor. Sets left and right pointers to null and assigns data to the node.
@pre None.
@post Object created with specified data, left and right pointers set to null.
@param anItem The data the node should contain. 
@return None. */

template < class ItemType > 
BinaryNode<ItemType>::BinaryNode ( const ItemType& anItem )
	{

	//data assigned, set left and right to null

	item = anItem;

	leftChildPtr = nullptr;

	rightChildPtr = nullptr;

	}

/** Binary node parameterized constructor. Sets left and right pointers to specified trees and assigns data to the node.
@pre None.
@post Object created with specified data, left and right pointers pointing to specified subtrees.
@param anItem The data the node should contain.
@param leftPtr The subtree the node's left pointer should point to.
@param rightPtr The subtree the node's right pointer should point to.
@return None. */

template < class ItemType > 
BinaryNode<ItemType>::BinaryNode (const ItemType & anItem, BinaryNode<ItemType>* leftPtr, BinaryNode<ItemType>* rightPtr)
	{

	//data assigned, set left and right pointers to specified trees

	item = anItem;
	
	leftChildPtr = leftPtr;

	rightChildPtr = rightPtr;

	}

/** Binary node setItem function. Sets the data stored by the node to the specified value.
@pre None.
@post Item data member holds anItem.
@param anItem The data the node should contain.
@return None. */

template < class ItemType >
void BinaryNode<ItemType>::setItem (const ItemType & anItem)
	{

	item = anItem;

	}

/** Binary node getItem function. Returns the data stored in the node's item data member. Caveat emptor when calling this function
with a node that has not yet had data assigned to it, likely to return garbage.
@pre None, but caveat emptor when calling on a node where data has not been assigned.
@post Data stored in item data member of the node returned. Node contents unchanged.
@return ItemType The object stored in the node's item data member. */

template < class ItemType >
ItemType BinaryNode<ItemType>::getItem () const
	{

	return item;

	}

/** Binary node isLeaf function. Checks to see if the node is a leaf (ie if both left and right pointers point to null, ie no children). 
@pre None.
@post Returns true if the node is a leaf and false if not; node contents unchanged.
@return bool Whether the node is a leaf or not. */

template < class ItemType >
bool BinaryNode<ItemType>::isLeaf () const
	{

	//if left and right are both null, it's a leaf

	return ( leftChildPtr == nullptr && rightChildPtr == nullptr );

	}

/** Binary node getLeftChildPtr function.
@pre None.
@post leftChildPtr of the node returned; node contents unchanged
@return BinaryNode<ItemType>* The left child pointer. */

template < class ItemType >
BinaryNode<ItemType>* BinaryNode<ItemType>::getLeftChildPtr () const
	{

	return leftChildPtr;

	}

/** Binary node getRightChildPtr function.
@pre None.
@post rightChildPtr of the node returned; node contents unchanged
@return BinaryNode<ItemType>* The right child pointer. */

template < class ItemType >
BinaryNode<ItemType>* BinaryNode<ItemType>::getRightChildPtr () const
	{

	return rightChildPtr;

	}

/** Binary node setLeftChildPtr function.
@pre None.
@post leftChildPtr of the node set to specified value.
@param leftPtr The pointer the left pointer value of the node should store. 
@return None. */

template < class ItemType >
void BinaryNode<ItemType>::setLeftChildPtr (BinaryNode<ItemType>* leftPtr)
	{

	leftChildPtr = leftPtr;

	}

/** Binary node setRightChildPtr function.
@pre None.
@post rightChildPtr of the node set to specified value.
@param rightPtr The pointer the right pointer value of the node should store. 
@return None. */

template < class ItemType >
void BinaryNode<ItemType>::setRightChildPtr (BinaryNode<ItemType>* rightPtr)
	{

	rightChildPtr = rightPtr;

	}

template class BinaryNode<int>;

//end binary node implementation

//binary tree implementation

/** Binary tree getHeightHelper function. Called by getHeight to determine the height of the tree. Uses recursion to find total height.
@pre None.
@post Height of subTreePtr returned; tree contents unchanged.
@param subTreePtr the subtree whose height is to be found.
@return int The height of the tree. */

template < class ItemType >  
int BinaryNodeTree<ItemType>::getHeightHelper (BinaryNode<ItemType>* subTreePtr) const
	{

	//if nullptr, subtree has height 0

	if ( subTreePtr == nullptr )
		return 0;

	//if not nullptr, this tree has height 1 plus the height of its tallest subtree

	else
		{

		return ( 1 + max( getHeightHelper( subTreePtr->getLeftChildPtr() ), getHeightHelper( subTreePtr->getRightChildPtr() ) ) );

		}

	}

/** Binary tree getNumberOfNodesHelper function. Called by getNumberOfNodes to determine the number of nodes in the tree. Uses recursion to find 
total number of nodes.
@pre None.
@post Number of nodes in subTreePtr returned; tree contents unchanged.
@param subTreePtr the subtree whose number of nodes is to be found.
@return int The number of nodes in the tree. */

template < class ItemType >  
int BinaryNodeTree<ItemType>::getNumberOfNodesHelper (BinaryNode<ItemType>* subTreePtr) const
	{

	//if nullptr, there is no node here

	if ( subTreePtr == nullptr )
		return 0;

	//if not nullptr, the number of nodes is this one plus the number of child nodes
	
	else
		{

		return ( 1 + getNumberOfNodesHelper( subTreePtr->getLeftChildPtr() ) + getNumberOfNodesHelper( subTreePtr->getRightChildPtr() ) );

		}

	}

/** Binary tree destroy function. Called by clear function and destructor to deallocate all dynamic memory for nodes in the tree. 
Uses recursion to visit all nodes.
@pre None.
@post All nodes of the tree pointed to by subTreePtr deallocated and data lost.
@param subTreePtr the subtree whose nodes are to be destroyed.
@return None. */

template < class ItemType >  
void BinaryNodeTree<ItemType>::destroyTree (BinaryNode<ItemType>* subTreePtr)
	{

	//if not nullptr, process any subtrees then destroy this node

	if ( subTreePtr != nullptr )
		{

		destroyTree ( subTreePtr->getLeftChildPtr() );
		destroyTree ( subTreePtr->getRightChildPtr() );
		delete subTreePtr;

		}

	}

/** Binary tree balancedAdd function. Called by public add function. Adds a value to the binary tree in a way that maintains the balance of 
the tree. This tree is not sorted, so the value will not be placed in any sorted order. Uses recursion to find the proper place to add the node.
@pre None.
@post Value added to tree while maintaining the tree's balance.
@param subTreePtr The tree to which the value should be added.
@param newNodePtr The node to be added to the tree.
@return BinaryNode<ItemType>* A pointer to the tree once the new value has been added. */

template < class ItemType >  
BinaryNode<ItemType>* BinaryNodeTree<ItemType>::balancedAdd (BinaryNode<ItemType>* subTreePtr, BinaryNode<ItemType>* newNodePtr)
	{

	//if nullptr, return the node- it will be the first node in the subtree

	if ( subTreePtr == nullptr )
		return newNodePtr;

	//if not nullptr, add to the shorter child subtree (prefer left if both trees are equal)

	else
		{

		BinaryNode<ItemType>* leftPtr = subTreePtr->getLeftChildPtr();
		BinaryNode<ItemType>* rightPtr = subTreePtr->getRightChildPtr();

		if ( getHeightHelper(leftPtr) > getHeightHelper(rightPtr) )
			{

			rightPtr = balancedAdd( rightPtr, newNodePtr );
			subTreePtr->setRightChildPtr(rightPtr);

			}

		else
			{

			leftPtr = balancedAdd( leftPtr, newNodePtr );
			subTreePtr->setLeftChildPtr(leftPtr);

			}

		return subTreePtr;

		}	

	}

/** Binary tree removeValue function. Called by public remove function. Attempts to remove target value from the binary tree; will update success
variable to true if operation is able to remove.  Uses recursion to search the tree for the target value.
@pre None.
@post Value removed from the tree if found and values shifted as necessary; success variable updated to state whether the removal was successful.
@param subTreePtr The subtree to search for the value that should be removed.
@param target The target value that is to be removed from the tree.
@param success Bool denoting whether the value was found or not; updated to true if a removal is carried out.
@return BinaryNode<ItemType>* A pointer to the tree once the operation has been carried out. */

template < class ItemType >
BinaryNode<ItemType>* BinaryNodeTree<ItemType>::removeValue (BinaryNode<ItemType>* subTreePtr, const ItemType target, bool &success)
	{

	//if nullptr, value was not found
	
	if ( subTreePtr == nullptr )
		
		{

		success = false;

		return nullptr;

		}

	//if node's item == target, value was found, remove nodes as necessary

	else if ( subTreePtr->getItem() == target )
		{

		subTreePtr = moveValuesUpTree( subTreePtr );

		success = true;

		return subTreePtr;

		}

	//otherwise, look for the target in the left and right subtrees, return null if it wasn't found

	else
		{

		BinaryNode<ItemType>* temp1 = removeValue ( subTreePtr->getLeftChildPtr(), target, success );

		BinaryNode<ItemType>* temp2 = removeValue ( subTreePtr->getRightChildPtr(), target, success );
		
		if ( temp1 != nullptr )
			return temp1;

		else
			return temp2;

		}

	}

/** Binary tree moveValuesUpTree function. Shifts nodes after the removal of a value to maintain the integrity of the pointers in the tree and not lose data.
Uses recursion to loop through subtree values as necessary. Since this tree is not sorted, values are moved without any element of comparison.
@pre Called by removeValue function for target node that is to be removed.
@post After all recursion, the tree will be 'fixed' to account for the removed node. 
@param subTreePtr Pointer to the node that is to be removed.
@return BinaryNode<ItemType>* A pointer to the tree once the operation has been carried out. */

template < class ItemType >
BinaryNode<ItemType>* BinaryNodeTree<ItemType>::moveValuesUpTree (BinaryNode<ItemType>* subTreePtr)
	{

	BinaryNode<ItemType>* tempPtr;

	//if the node is a leaf, just delete it

	if ( subTreePtr->isLeaf() )
		{

		delete subTreePtr;

		subTreePtr = nullptr;

		return nullptr;

		}

	//if the node has one child, replace this node with the child

	else if ( subTreePtr->getLeftChildPtr() != nullptr && subTreePtr->getRightChildPtr() == nullptr )
		{

		tempPtr = subTreePtr->getLeftChildPtr();

		delete subTreePtr;

		subTreePtr = nullptr;

		return tempPtr;

		}

	else if ( subTreePtr->getRightChildPtr() != nullptr && subTreePtr->getLeftChildPtr() == nullptr )
		{

		tempPtr = subTreePtr->getRightChildPtr();

		delete subTreePtr;

		subTreePtr = nullptr;

		return tempPtr;

		}

	//if the node has two children, replace the value in this node with the one in the left child 
	//then call the function again for the left child to handle any additional nodes

	else
		{

		tempPtr = subTreePtr->getLeftChildPtr();

		subTreePtr->setItem( tempPtr->getItem() );

		moveValuesUpTree( tempPtr );

		}

	}

/** Binary tree findNode function. Called by public getEntry and contains functions. Searches the tree for a node containing target value. 
Uses recursion to search the entire tree.
@pre None.
@post Tree contents unchanged; success variable updated to true if node found, pointer to the node containing the value returned if found.
@param subTreePtr The subtree to search for the value.
@param target The target value that is to be found.
@param success Bool denoting whether the value was found or not; updated to true if found.
@return BinaryNode<ItemType>* A pointer to the node containing the value. */

template < class ItemType >  
BinaryNode<ItemType>* BinaryNodeTree<ItemType>::findNode (BinaryNode<ItemType>* treePtr, const ItemType& target, bool& success) const
	{

	//if nullptr, do nothing

	if ( treePtr != nullptr )
		{

		//if not nullptr and target found, set true and return this node

		if ( treePtr->getItem() == target )
			{		

			success = true;

			return treePtr;

			}

		//if not nullptr and target not found, try to find it in the children

		else 
			{

			findNode( treePtr->getLeftChildPtr(), target, success );
			findNode( treePtr->getRightChildPtr(), target, success );

			}

		}

	}


/** Binary tree copyTree function. Called by copy constructor and = operator. Uses recursion to visit the entire
target tree.
@pre None.
@post Tree contents unchanged; tree contents copied to new tree.
@param treePtr The tree to be copied.
@return BinaryNode<ItemType>* A pointer to the new tree that has been created. */

template < class ItemType >  
BinaryNode<ItemType>* BinaryNodeTree<ItemType>::copyTree (const BinaryNode<ItemType>* treePtr) const
	{

	BinaryNode<ItemType>* newTree = nullptr;

	//if target tree is null, just return nullptr

	if ( treePtr != nullptr )
		{

		//if not null, copy this node and then copy its children

		newTree = new BinaryNode<ItemType> ( treePtr->getItem() );
		
		newTree->setLeftChildPtr( copyTree( treePtr->getLeftChildPtr() ) );

		newTree->setRightChildPtr( copyTree ( treePtr->getRightChildPtr() ) );

		}

	//return the finished tree

	return newTree;

	}

/** Binary tree preorder traversal function. Visits root, then left, then right, performing an action specified in the user
provided visit function. Uses recursion to visit the entire tree.
@pre None.
@post Tree contents unchanged; visit performed for each value in the tree in specified order.
@param visit The user provided visit function, which will perform some action at each node.
@param treePtr The tree to be traversed.
@return None. */

template < class ItemType >  
void BinaryNodeTree<ItemType>::preorder (void visit (ItemType&), BinaryNode<ItemType>* treePtr) const
	{

	//visit root, then left, then right

	if (treePtr != nullptr)
		{

		ItemType theItem = treePtr->getItem ();

		visit (theItem);

		preorder (visit, treePtr->getLeftChildPtr ());

		preorder (visit, treePtr->getRightChildPtr ());

		}

	}

/** Binary tree inorder traversal function. Visits left, then root, then right, performing an action specified in the user
provided visit function. Uses recursion to visit the entire tree.
@pre None.
@post Tree contents unchanged; visit performed for each value in the tree in specified order.
@param visit The user provided visit function, which will perform some action at each node.
@param treePtr The tree to be traversed.
@return None. */

template < class ItemType >  
void BinaryNodeTree<ItemType>::inorder (void visit (ItemType&), BinaryNode<ItemType>* treePtr) const
	{

	//visit left, then root, then right

	if (treePtr != nullptr)
		{

		inorder (visit, treePtr->getLeftChildPtr ());

		ItemType theItem = treePtr->getItem ();

		visit (theItem);

		inorder (visit, treePtr->getRightChildPtr ());
		
		}

	}

/** Binary tree postorder traversal function. Visits left, then right, then root, performing an action specified in the user
provided visit function. Uses recursion to visit the entire tree.
@pre None.
@post Tree contents unchanged; visit performed for each value in the tree in specified order.
@param visit The user provided visit function, which will perform some action at each node.
@param treePtr The tree to be traversed.
@return None. */

template < class ItemType >  
void BinaryNodeTree<ItemType>::postorder (void visit (ItemType&), BinaryNode<ItemType>* treePtr) const
	{

	//visit left, then right, then root

	if (treePtr != nullptr)
		{

		postorder (visit, treePtr->getLeftChildPtr ());

		postorder (visit, treePtr->getRightChildPtr ());

		ItemType theItem = treePtr->getItem ();

		visit (theItem);

		}

	}

/** Binary tree default constructor. Tree contains no nodes, so points to null.
@pre None.
@post Object created with root pointing to null.
@return None. */

template < class ItemType >  
BinaryNodeTree<ItemType>::BinaryNodeTree ()
	{

	rootPtr = nullptr;

	}

/** Binary tree parameterized constructor. Creates root node with specified data.
@pre None.
@post Object created with a root node containing rootItem.
@param rootItem The data the root node is to contain.
@return None. */

template < class ItemType >  
BinaryNodeTree<ItemType>::BinaryNodeTree ( const ItemType& rootItem )
	{

	rootPtr = new BinaryNode<ItemType>(rootItem);

	}

/** Binary tree parameterized constructor. Creates root node with specified data, with subtrees that are copies of the left and right
subtrees provided.
@pre None.
@post Object created with a root node containing rootItem and child pointers that point to copies of the subtrees provided.
@param rootItem The data the root node is to contain.
@param leftTreePtr The subtree that is to be copied for the tree's left child.
@param rightTreePtr The subtree that is to be copied for the tree's right child.
@return None. */

template < class ItemType >  
BinaryNodeTree<ItemType>::BinaryNodeTree (const ItemType& rootItem, const BinaryNodeTree<ItemType>* leftTreePtr,
			    const BinaryNodeTree<ItemType>* rightTreePtr)
	{

	rootPtr = new BinaryNode<ItemType>(rootItem, copyTree(leftTreePtr->rootPtr), copyTree(rightTreePtr->rootPtr) );

	}

/** Binary tree copy constructor. Creates a new tree which is a copy of the tree provided.
@pre None.
@post Binary tree created which is a copy of tree provided.
@param tree The tree that this object is to copy.
@return None. */

template < class ItemType >  
BinaryNodeTree<ItemType>::BinaryNodeTree (const BinaryNodeTree<ItemType>& tree)
	{

	rootPtr = copyTree( tree.rootPtr );

	}

/** Binary tree destructor. Deallocates any dynamic memory for nodes in this tree using destroyTree function.
@pre None.
@post All dynamic memory for nodes in this tree deallocated.
@return None. */

template < class ItemType >  
BinaryNodeTree<ItemType>::~BinaryNodeTree()
	{

	destroyTree(rootPtr);	

	}

/** Binary tree isEmpty function. Checks to see if there are any nodes in the binary tree.
@pre None.
@post Tree contents unchanged; bool returned.
@return bool True if the tree is empty, false if it is not empty. */

template < class ItemType >  
bool BinaryNodeTree<ItemType>::isEmpty() const
	{

	return ( rootPtr == nullptr );

	}

/** Binary tree getHeight function. Uses getHeightHelper function to determine the height of the tree.
@pre None.
@post Tree contents unchanged; height returned.
@return int The height of the binary tree (0 if empty). */

template < class ItemType >  
int BinaryNodeTree<ItemType>::getHeight() const
	{

	return ( getHeightHelper(rootPtr) );

	}

/** Binary tree getNumberOfNodes function. Uses getNumberOfNodesHelper function to determine the number of nodes in the tree.
@pre None.
@post Tree contents unchanged; number of nodes returned.
@return int The number of nodes in the binary tree (0 if empty). */

template < class ItemType >  
int BinaryNodeTree<ItemType>::getNumberOfNodes() const
	{

	return ( getNumberOfNodesHelper(rootPtr) );

	}

/** Binary tree getRootData function. Binary tree must contain some data. Returns item stored in the root node of the tree. 
Caveat emptor using this function on an empty binary tree (!!!).
@pre The binary tree contains at least one value.
@post Tree contents unchanged; value stored in root node returned.
@return ItemType The item stored in the root node. */

template < class ItemType >  
ItemType BinaryNodeTree<ItemType>::getRootData() const
	{

	return ( rootPtr->getItem() );

	}

/** Binary tree setRootData function. Sets the item in the root node of the binary tree to the user specified one. For an empty
tree, creates the root node and stores the value in it.
@pre None.
@post Root node contains specified value.
@return None. */

template < class ItemType >  
void BinaryNodeTree<ItemType>::setRootData (const ItemType& newData)
	{

	if ( isEmpty() )
		rootPtr = new BinaryNode<ItemType>(newData);
	
	else
		rootPtr->setItem(newData);

	}

/** Binary tree add function. Adds specified value to the binary tree as a new node. Uses balancedAdd helper function to try to
maintain balance in the tree after the add.
@pre None.
@post Value added to the tree; balance maintained.
@return bool Returns true, signifying successful add. */

template < class ItemType >  
bool BinaryNodeTree<ItemType>::add (const ItemType& newData)
	{

  	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newData);

  	rootPtr = balancedAdd (rootPtr, newNodePtr);

	return true;

	}

/** Binary tree remove function. Attempts to remove specified value from the binary tree using removeValue helper function.
@pre None.
@post If the value was found in the tree, it was removed and nodes were shifted if necessary to maintain integrity of the data.
@param data The value to be removed from the tree.
@return bool True if a value was removed, false if not. */

template < class ItemType >  
bool BinaryNodeTree<ItemType>::remove (const ItemType& data)
	{

	bool success = false;

	rootPtr = removeValue( rootPtr, data, success );

	return success;

	}

/** Binary tree clear function. Deallocates all nodes in the tree, discarding all data, and restores tree to an empty state. Uses
destroyTree helper function.
@pre None.
@post All nodes deallocated and all data lost; tree is returned to an empty state.
@return None. */

template < class ItemType >  
void BinaryNodeTree<ItemType>::clear()
	{

	destroyTree(rootPtr);

	rootPtr = nullptr;

	}

/** Binary tree getEntry function. Searches binary tree for target value. Returns the value if found, otherwise prints an error 
message to console. Uses findNode helper function.
@pre None.
@post Tree contents unchanged; value returned if found, otherwise error written to console.
@param anEntry The value to be found in the binary tree.
@return ItemType The value found in the binary tree, if the search was successful. */

template < class ItemType >
ItemType BinaryNodeTree<ItemType>::getEntry (const ItemType& anEntry) const
	{

	bool success;

	BinaryNode<ItemType>* tempPtr = findNode( rootPtr, anEntry, success );

	if ( tempPtr != nullptr )
		return tempPtr->getItem();

	else
		cout << "ERROR: Item not found!" << endl;

	}

/** Binary tree contains function. Searches binary tree for target value. Returns true if value is found, false if not. Uses
findNode helper function.
@pre None.
@post Tree contents unchanged; bool signifying whether the value was found returned.
@param anEntry The value to be found in the binary tree.
@return bool True if the value is in the tree, false if not. */

template < class ItemType >  
bool BinaryNodeTree<ItemType>::contains (const ItemType& anEntry) const
	{

	bool success = false;

	findNode( rootPtr, anEntry, success);

	return success;

	}

/** Binary tree preorder traversal function. Visits root, then left, then right, performing an action specified in the user
provided visit function. Uses preorder helper function.
@pre None.
@post Tree contents unchanged; visit performed for each value in the tree in specified order.
@param visit The user provided visit function, which will perform some action at each node.
@return None. */

template < class ItemType >  
void BinaryNodeTree<ItemType>::preorderTraverse (void visit (ItemType &)) const
	{

	preorder( visit, rootPtr );

	}

/** Binary tree inorder traversal function. Visits left, then root, then right, performing an action specified in the user
provided visit function. Uses preorder helper function.
@pre None.
@post Tree contents unchanged; visit performed for each value in the tree in specified order.
@param visit The user provided visit function, which will perform some action at each node.
@return None. */

template < class ItemType >  
void BinaryNodeTree<ItemType>::inorderTraverse (void visit (ItemType &)) const
	{

	inorder( visit, rootPtr );

	}

/** Binary tree postorder traversal function. Visits left, then right, then root, performing an action specified in the user
provided visit function. Uses postorder helper function.
@pre None.
@post Tree contents unchanged; visit performed for each value in the tree in specified order.
@param visit The user provided visit function, which will perform some action at each node.
@return None. */

template < class ItemType >  
void BinaryNodeTree<ItemType>::postorderTraverse (void visit (ItemType &)) const
	{

	postorder( visit, rootPtr );

	}

/** Binary tree overloaded = operator. Sets left hand tree to be a copy of right hand tree using copyTree helper function.
@pre None.
@post Left hand tree is now a copy of right hand tree. Any nodes contained in the left hand tree before the copy deallocated
and data lost.
@param rightHandSide The tree that is to be copied from.
@return BinaryNodeTree<ItemType> The tree that now contains the copy of the right hand side tree. */
	  
template < class ItemType >  
BinaryNodeTree<ItemType>& BinaryNodeTree<ItemType>::operator= (const BinaryNodeTree & rightHandSide)
	{

	if ( !isEmpty() )
		clear();

	rootPtr = copyTree(rightHandSide.rootPtr);

	return *this;

	}

template class BinaryNodeTree<int>;

//end binary tree implementation

//binary search tree implementation

/** BST insertInorder function. Called by public add function. Adds a value to the BST in a way that maintains its sorted property.
Uses recursion to find the appropriate location in the tree.
@pre None.
@post Value added to tree while maintaining the tree's sortedness.
@param subTreePtr The tree to which the value should be added.
@param newNodePtr The node to be added to the tree.
@return BinaryNode<ItemType>* A pointer to the tree once the new value has been added. */

template < class ItemType >
BinaryNode<ItemType>* BinarySearchTree<ItemType>::insertInorder (BinaryNode<ItemType>* subTreePtr, 
		                                  BinaryNode<ItemType>* newNodePtr)
	{

	BinaryNode<ItemType>* tempPtr;

	//if empty tree, just add the new node

	if ( subTreePtr == nullptr )
		return newNodePtr;

	//if tree value at this node > item to be added, go left

	else if ( subTreePtr->getItem() > newNodePtr->getItem() )
		{

		tempPtr = insertInorder(subTreePtr->getLeftChildPtr(), newNodePtr );
		subTreePtr->setLeftChildPtr(tempPtr);

		}

	//otherwise, go right

	else
		{

		tempPtr = insertInorder(subTreePtr->getRightChildPtr(), newNodePtr );
		subTreePtr->setRightChildPtr(tempPtr); 

		}

	//return the BST

	return subTreePtr;

	}

/** BST removeValue function. Called by public remove function. Attempts to remove target value from the BST while retaining sorted property and data
integrity; will update success variable to true if operation finds value to remove.  Uses recursion to search the tree for the target value.
@pre None.
@post Value removed from the tree if found and values shifted as necessary; success variable updated to state whether the removal was successful.
@param subTreePtr The subtree to search for the value that should be removed.
@param target The target value that is to be removed from the tree.
@param success Bool denoting whether the value was found or not; updated to true if a removal is carried out.
@return BinaryNode<ItemType>* A pointer to the tree once the operation has been carried out. */


template < class ItemType >  
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeValue (BinaryNode<ItemType>* subTreePtr, 
		                                const ItemType target, bool & success)
	{

	BinaryNode<ItemType>* tempPtr;

	//if empty subtree, the value was not found- return null, success = false

	if ( subTreePtr == nullptr )
		{
			
		success = false;

		return nullptr;

		}

	//if value at this node equals target, found it- remove the node, set success to true, return this node

	else if ( subTreePtr->getItem() == target )
		{

		subTreePtr = removeNode( subTreePtr );

		success = true;

		return subTreePtr;

		}

	//if tree value at this node > target value, search left

	else if ( subTreePtr->getItem() > target )
		{

		tempPtr = removeValue ( subTreePtr->getLeftChildPtr(), target, success );
		subTreePtr->setLeftChildPtr(tempPtr);
		return subTreePtr;

		}

	//otherwise, search right

	else
		{

		tempPtr = removeValue ( subTreePtr->getRightChildPtr(), target, success );
		subTreePtr->setRightChildPtr(tempPtr);
		return subTreePtr;

		}

	}

/** BST removeNode function. Shifts nodes once a value to be removed has been found to maintain the integrity of the data in the tree and the tree's
sortedness.
@pre Called by removeValue function for target node that is to be removed.
@post After all recursion, the tree will be 'fixed' to account for the removed node and sortedness maintained. 
@param nodePtr Pointer to the node that is to be removed.
@return BinaryNode<ItemType>* A pointer to the tree once the operation has been carried out. */

template < class ItemType >  
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeNode (BinaryNode<ItemType>* nodePtr)
	{

	BinaryNode<ItemType>* nodeToConnectPtr;

	//if node to be deleted is a leaf, just delete it

	if ( nodePtr->isLeaf() )
		{

		delete nodePtr;
		nodePtr = nullptr;
		return nodePtr;

		}

	//if node to be deleted has no left child, replace this node with the right child node

	else if ( nodePtr->getLeftChildPtr() == nullptr )
		{
		
		nodeToConnectPtr = nodePtr->getRightChildPtr();
		delete nodePtr;
		nodePtr = nullptr;
		return nodeToConnectPtr;

		}

	//if node to be deleted has no right child, replace this node with the left child node

	else if	( nodePtr->getRightChildPtr() == nullptr )
		{

		nodeToConnectPtr = nodePtr->getLeftChildPtr();
		delete nodePtr;
		nodePtr = nullptr;
		return nodeToConnectPtr;

		}

	//if node to be deleted has two children, find the inorder successor of this node, delete it, and put its value in this node

	else
		{

		BinaryNode<ItemType>* tempPtr;
		ItemType newNodeValue;

		tempPtr = removeLeftmostNode( nodePtr->getRightChildPtr(), newNodeValue);
		nodePtr->setRightChildPtr( tempPtr );
		nodePtr->setItem( newNodeValue );
		return nodePtr;

		}

	}

/** BST removeLeftmostNode helper function. Deletes the leftmost node of the left child of target tree and sets its value to 
the inorderSuccessor variable. Called by removeNode function.
@pre Called by removeNode function in appropriate circumstance to maintain sortedness of the BST.
@post LeftmostNode deleted from the BST, inorderSuccessor value set to its data.
@param nodePtr The pointer from which the leftmost node should be deleted.
@param inorderSuccessor Will store the value of the leftmost node after it is deleted for use in further operations.
@return BinaryNode<ItemType>* A pointer to the tree after the operation has been conducted. */

template < class ItemType >  
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode (BinaryNode<ItemType>* nodePtr, 
		                                       ItemType & inorderSuccessor)
	{

	//There is no left child, so get the value of this node and then remove it

	if ( nodePtr->getLeftChildPtr() == nullptr )
		{

		inorderSuccessor = nodePtr->getItem();
		
		return removeNode(nodePtr);

		}

	//Otherwise, search the left child of this node for the leftmost value

	else
		{

		BinaryNode<ItemType>* tempPtr;

		tempPtr = removeLeftmostNode(nodePtr->getLeftChildPtr(), inorderSuccessor);

		nodePtr->setLeftChildPtr(tempPtr);

		return nodePtr;

		}

	}

/** BST findNode function. Called by public getEntry and contains functions. Searches the tree for a node containing target value. 
Uses recursion to search the entire tree. Performs binary search so should have O(logn) property.
@pre None.
@post Tree contents unchanged; node containing value returned if found, nullpointer returned if value not found.
@param treePtr the tree to be searched.
@param target The target value that is to be found.
@return BinaryNode<ItemType>* A pointer to the node containing the value if found, nullpointer if not found. */

template < class ItemType >  
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode (BinaryNode<ItemType>* treePtr, 
		                             const ItemType & target) const
	{

	//if null, value not found

	if ( treePtr == nullptr )
		return nullptr;

	//if node value == target, item found - return this node

	else if ( treePtr->getItem() == target )
		return treePtr;

	//if node value > target, search left

	else if ( treePtr->getItem() > target )
		return findNode( treePtr->getLeftChildPtr(), target );

	//if node value < target, search right

	else
		return findNode( treePtr->getRightChildPtr(), target);

	}

/** BST default constructor. Tree contains no nodes, so points to null.
@pre None.
@post Object created with root pointing to null.
@return None. */

template < class ItemType >  
BinarySearchTree<ItemType>::BinarySearchTree()
	{

	rootPtr = nullptr;

	}

/** BST parameterized constructor. Creates root node with specified data.
@pre None.
@post Object created with a root node containing rootItem.
@param rootItem The data the root node is to contain.
@return None. */

template < class ItemType >  
BinarySearchTree<ItemType>::BinarySearchTree (const ItemType & rootItem)
	{

	rootPtr = new BinaryNode<ItemType>(rootItem);

	}

/** BST copy constructor. Creates a new tree which is a copy of the tree provided.
@pre None.
@post BST created which is a copy of tree provided.
@param tree The tree that this object is to copy.
@return None. */

template < class ItemType >  
BinarySearchTree<ItemType>::BinarySearchTree (const BinarySearchTree<ItemType>& tree)
	{

	rootPtr = this->copyTree( tree.rootPtr );

	}

/** BST destructor. Deallocates any dynamic memory for nodes in this tree using destroyTree function.
@pre None.
@post All dynamic memory for nodes in this tree deallocated.
@return None. */

template < class ItemType >  
BinarySearchTree<ItemType>::~BinarySearchTree ()
	{

	this->destroyTree(rootPtr);

	}

/** BST isEmpty function. Checks to see if there are any nodes in the binary tree.
@pre None.
@post Tree contents unchanged; bool returned.
@return bool True if the tree is empty, false if it is not empty. */

template < class ItemType >  
bool BinarySearchTree<ItemType>::isEmpty () const
	{

	return ( rootPtr == nullptr );

	}

/** BST getHeight function. Uses getHeightHelper function to determine the height of the tree.
@pre None.
@post Tree contents unchanged; height returned.
@return int The height of the binary tree (0 if empty). */

template < class ItemType >  
int BinarySearchTree<ItemType>::getHeight () const
	{

	return ( this->getHeightHelper(rootPtr) );

	}

/** BST getNumberOfNodes function. Uses getNumberOfNodesHelper function to determine the number of nodes in the tree.
@pre None.
@post Tree contents unchanged; number of nodes returned.
@return int The number of nodes in the binary tree (0 if empty). */

template < class ItemType >  
int BinarySearchTree<ItemType>::getNumberOfNodes () const
	{

	return ( this->getNumberOfNodesHelper(rootPtr) );

	}

/** BST getRootData function. Binary tree must contain some data. Returns item stored in the root node of the tree. 
Caveat emptor using this function on an empty BST (!!!).
@pre The binary tree contains at least one value.
@post Tree contents unchanged; value stored in root node returned.
@return ItemType The item stored in the root node. */

template < class ItemType >  
ItemType BinarySearchTree<ItemType>::getRootData () const
	{

	return ( rootPtr->getItem() );

	}

/** BST setRootData function. If the BST is empty, creates a new node with root value. Otherwise does nothing, for fear
of destroying the sorted property of the BST. Use the add function to insert the value into the tree inorder.
@pre None.
@post Root node contains specified value.
@return None. */

template < class ItemType >  
void BinarySearchTree<ItemType>::setRootData (const ItemType& newData)
	{

	if ( isEmpty() )
		rootPtr = new BinaryNode<ItemType>(newData);

	}
/** BST add function. Adds specified value to the BST as a new node in a location that will maintain the sorted property
of the BST. Uses insertInorder helper function.
@pre None.
@post Value added to the tree; sorted property maintained.
@return bool Returns true, signifying successful add. */

template < class ItemType >  
bool BinarySearchTree<ItemType>::add (const ItemType& newEntry)
	{

	BinaryNode<ItemType>* temp = new BinaryNode<ItemType>(newEntry);

	rootPtr = insertInorder( rootPtr, temp );

	return true;

	}

/** BST remove function. Attempts to remove specified value from the binary tree using removeValue helper function while maintaining
the sorted property of the BST.
@pre None.
@post If the value was found in the tree, it was removed and nodes were shifted if necessary to maintain integrity of the data and
sortedness.
@param anEntry The value to be removed from the tree. 
@return bool True if a value was removed, false if not. */

template < class ItemType >  
bool BinarySearchTree<ItemType>::remove (const ItemType& anEntry)
	{

	bool success = false;

	rootPtr = removeValue( rootPtr, anEntry, success );

	return success;

	}

/** BST clear function. Deallocates all nodes in the tree, discarding all data, and restores tree to an empty state. Uses
destroyTree helper function.
@pre None.
@post All nodes deallocated and all data lost; tree is returned to an empty state.
@return None. */

template < class ItemType >  
void BinarySearchTree<ItemType>::clear ()
	{

	this->destroyTree(rootPtr);

	rootPtr = nullptr;

	}

/** BST getEntry function. Searches binary tree for target value. Returns the value if found, otherwise prints an error 
message to console. Uses findNode helper function.
@pre None.
@post Tree contents unchanged; value returned if found, otherwise error written to console.
@param anEntry The value to be found in the binary tree.
@return ItemType The value found in the binary tree, if the search was successful. */

template < class ItemType >  
ItemType BinarySearchTree<ItemType>::getEntry (const ItemType & anEntry) const
	{

	BinaryNode<ItemType>* itemLoc = findNode(rootPtr, anEntry);

	if ( itemLoc != nullptr )
		return itemLoc->getItem();

	else
		cout << "ERROR: Item not found!" << endl;

	}

/** BST contains function. Searches BST for target value. Returns true if value is found, false if not. Uses
findNode helper function. Search should have O(logn) binary search property.
@pre None.
@post Tree contents unchanged; bool signifying whether the value was found returned.
@param anEntry The value to be found in the binary tree.
@return bool True if the value is in the tree, false if not. */

template < class ItemType >  
bool BinarySearchTree<ItemType>::contains (const ItemType & anEntry) const
	{

	BinaryNode<ItemType>* itemLoc = findNode(rootPtr, anEntry);

	if ( itemLoc == nullptr )
		return false;

	else
		return true;

	}

/** BST preorder traversal function. Visits root, then left, then right, performing an action specified in the user
provided visit function. Uses preorder helper function.
@pre None.
@post Tree contents unchanged; visit performed for each value in the tree in specified order.
@param visit The user provided visit function, which will perform some action at each node.
@return None. */

template < class ItemType >  
void BinarySearchTree<ItemType>::preorderTraverse (void visit (ItemType&)) const
	{

	this->preorder( visit, rootPtr );

	}

/** BST inorder traversal function. Visits left, then root, then right, performing an action specified in the user
provided visit function. Uses preorder helper function.
@pre None.
@post Tree contents unchanged; visit performed for each value in the tree in specified order.
@param visit The user provided visit function, which will perform some action at each node.
@return None. */

template < class ItemType >  
void BinarySearchTree<ItemType>::inorderTraverse (void visit (ItemType&)) const
	{

	this->inorder( visit, rootPtr );

	}

/** BST postorder traversal function. Visits left, then right, then root, performing an action specified in the user
provided visit function. Uses postorder helper function.
@pre None.
@post Tree contents unchanged; visit performed for each value in the tree in specified order.
@param visit The user provided visit function, which will perform some action at each node.
@return None. */

template < class ItemType >  
void BinarySearchTree<ItemType>::postorderTraverse (void visit (ItemType&)) const
	{

	this->postorder( visit, rootPtr );

	}

/** BST overloaded = operator. Sets left hand BST to be a copy of right hand BST using copyTree helper function.
@pre None.
@post Left hand BST is now a copy of right hand BST. Any nodes contained in the left hand BST before the copy deallocated
and data lost.
@param rightHandSide The BST that is to be copied from.
@return BinarySearchTree<ItemType> The tree that now contains the copy of the right hand side tree. */

template < class ItemType >  
BinarySearchTree<ItemType>& BinarySearchTree<ItemType>::operator= (const BinarySearchTree<ItemType>& rightHandSide)
	{

	if ( !isEmpty() )
		clear();

	rootPtr = this->copyTree(rightHandSide.rootPtr);

	return *this;

	}

template class BinarySearchTree<int>;

//end binary search tree implementation
