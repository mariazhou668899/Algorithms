#include <string>
#include <iostream>
#include <fstream>
#include "nodedata.h"
using namespace std;

//-----------------------------------------------------------------------------------------------------------
//BinTree class : It defines a binary search tree.
//It includes these features :
//Public functions:
//    Constructors and destructor :
//    --A default constructor receives no values
//    -- A constructor receives one value
//    -- A deep - copy constructor
//    -- A destructor
//    Overload common operators : =, == , !=
//    Accessors :
//    --Overload operator<< (output a polynomial with correct format)
//	  --Function isEmpty() to see if a tree is empty or not
//    --Function getHeight(const NodeData&) to get a node's height
//    --Function displaySideways() to display the tree sideways
//    --Function retrieve(const NodeData&, NodeData*&) to get the NodeData* of a given object in the tree
//    Mutators :
//    --Function makeEmpty() to empty a tree
//    --Function insert(NodeData*) to insert a NodeData* into a tree
//    Others :
//    --Function bstreeToArray(NodeData* []) to fill an array of Nodedata* by using an inorder traversal of the tree
//    --Function arrayToBSTreeHelper(Node*&, NodeData* [], int, int) to build a balanced BinTree from a sorted array
//Private utility functions to help corresponding public functions to realize its functions:	
//    --Function void inorderHelper(Node*) const;
//    --Function void sideways(Node*, int) const;
//    --Function void makeEmptyHelper(Node*);
//    --Function bool equleHelper(Node*, Node*)const;
//    --Function NodeData* retrieveHelper(Node*, const NodeData&) const;
//    --Function int maxDepth(Node* root) const;
//    --Function void assignHelper(Node*, Node*&);
//    --Function void bstreeToArrayHelper(Node*, NodeData* [], int&);
//    --Function void arrayToBSTreeHelper(Node*&, NodeData* [], int, int);
// 
//Implementation and assumptions:
//    --Private structure Node combined with a NodeData* data, left Node and right Node
//    --A NodeData* data pointing a string
//    --NodeData is another class which have proper data struct, constructors and comparison operators
//    --When building a tree, smaller NodeData* data to go left, and bigger go right
//    --A tree doesn't have the repeat data

//-----------------------------------------------------------------------------------------------------------

class BinTree {				
	//overload operator<< display an object of BinTree class inorder
	friend ostream& operator<<(ostream& output, const BinTree& p);

public:
	// Member functions
	BinTree();								  // constructor
	BinTree(const BinTree&);	  // deep copy constructor
	~BinTree();								  // destructor, calls makeEmpty	
	
	// utility functions
	bool isEmpty() const;				// true if tree is empty, otherwise false
	void makeEmpty();						// make the tree empty so isEmpty returns true
	bool insert(NodeData*);
	bool retrieve(const NodeData&, NodeData*&) const; // get the NodeData* of a given object in the tree
	void displaySideways() const;			      // provided below, displays the tree sideways
	int getHeight(const NodeData&) const;   // get the height of a given value in the tree
	void bstreeToArray(NodeData* []);       // fill an array of Nodedata* by using an inorder traversal of the tree
	void arrayToBSTree(NodeData* []);       // build a balanced BinTree from a sorted array of NodeData* leaving the array filled with NULLs

	// overload operators
	BinTree& operator=(const BinTree&);     // current object = parameter with deep copy
	bool operator==(const BinTree&) const;  // is object == parameter?
	bool operator!=(const BinTree&) const;  // is object != parameter?

private:
	struct Node {
		NodeData* data;				// pointer to data object
		Node* left;						// left subtree pointer
		Node* right;					// right subtree pointer
	};
	Node* root;							// root of the tree

	// utility functions
	void inorderHelper(Node*) const;	    // helper for operator<<()
	void sideways(Node*, int) const;	    // helper for displaySideways()
	void makeEmptyHelper(Node*);	        // helper for makeEmpty()
	bool equleHelper(Node*, Node*)const;	// helper for operator==()
	NodeData* retrieveHelper(Node*, const NodeData&) const;	    // helper for retrieve()
	int maxDepth(Node* root) const;	      // help to realize getHeight()
	void assignHelper(Node*, Node*&);	    // helper for operator=()
	void bstreeToArrayHelper(Node*, NodeData* [], int&);	    // helper for bstreeToArray()
	void arrayToBSTreeHelper(Node*&, NodeData* [], int, int);	// helper for arrayToBSTree()
};

