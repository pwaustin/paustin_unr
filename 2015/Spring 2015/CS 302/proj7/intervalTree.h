/** CS 302 Project 7 - scheduling with red black trees, class specification
@file intervalTree.h
@author Patrick Austin
@date 4/29/2015 */

/**

Binary node class for use in an interval tree. Uses a bool to store red/blackness, 
convention is black == true and red == false. Nodes default to red when created.

*/

class BinaryNode {

	private:

	  int start;

	  int end;

	  int max;

	  bool color;

	  BinaryNode* parentPtr;

	  BinaryNode* leftChildPtr;

	  BinaryNode* rightChildPtr;

	public:

	//constructors and destructors

	  BinaryNode ();

	//public operations

	  void setStart (const int& target);

	  int getStart () const ;

	  void setEnd (const int& target);

	  int getEnd () const ;

	  void setMax (const int& target);

	  int getMax () const ;

	  bool isRed () const;

	  bool isBlack () const;

          void setRed ();

          void setBlack ();

	  void setLeftChildPtr (BinaryNode* leftPtr);

	  BinaryNode* getLeftChildPtr () const;

	  void setRightChildPtr (BinaryNode* rightPtr);

	  BinaryNode* getRightChildPtr () const;

	  void setParentPtr (BinaryNode* parentNodePtr);

	  BinaryNode* getParentPtr () const;

	};

/**

Interval tree class. Only add, search, and preorder traversal operations supported. 
Duplicate start values for intervals not supported. Caveat emptor.

*/

class IntervalTree {

	private:

	  BinaryNode* rootPtr;

	protected:
	
	//helper functions

	  void insertInorder( BinaryNode* z ); 

	  void fixTree( BinaryNode* z );

	  void rotateLeft ( BinaryNode* x ); 

	  void rotateRight ( BinaryNode* x );

	  void fixMax( BinaryNode* z );

	  int getHeight ( BinaryNode* subTreePtr ) const;

	  void preorder ( BinaryNode* treePtr ) const;

	  void clear ( BinaryNode* treePtr );

	  BinaryNode* searchHelper ( const int& s, const int& e ) const;

	public:

	//constructors and destructors

	  IntervalTree();

	  ~IntervalTree();

	//public operations

	  bool isEmpty() const;

	  bool add ( const int& s, const int& e );

	  bool search( const int& s, const int& e, int& foundS, int& foundE );

	  void preorderTraverse() const;

	};

