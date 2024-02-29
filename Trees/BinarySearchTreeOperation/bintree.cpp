#include <string>
#include <iostream>
#include <fstream>
#include "nodedata.h"
#include "bintree.h"
using namespace std;

//------------------------- constructor ---------------------------------
// Default constructor, initialize a BinTree's root as NULL
BinTree::BinTree() {
	this->root = NULL;

}

//------------------------- constructor ---------------------------------
// Deep copy constructor
BinTree::BinTree(const BinTree& another) {
	this->assignHelper(another.root, this->root);

}

//------------------------- destructor --------------------------------- 
// Destructor for class BinTree
BinTree::~BinTree() {
	this->makeEmptyHelper(this->root);

}

//------------------------- isEmpty --------------------------------- 
// Check if a BinTree is empty, if empty return true, otherwise return false
bool BinTree::isEmpty() const {
	if (this->root == NULL) {
		return true;
	}
	else {
		return false;
	}

}

//------------------------- makeEmpty --------------------------------- 
// Empty a BinTree
void BinTree::makeEmpty() {
	if (this->root!=NULL) {
		this->makeEmptyHelper(this->root);
	}
}

//------------------------- makeEmptyHelper --------------------------------- 
// Help makeEmpty() to empty a tree, including clear Node and NodeData
void BinTree::makeEmptyHelper(Node* cur) {
	if (cur != NULL) {
		makeEmptyHelper(cur->left);
		makeEmptyHelper(cur->right);

		//delete NodeData*
		delete cur->data;
		cur->data = NULL;
		//delete Node*
		delete cur;
		cur = NULL;
	}
	root = NULL;

}

//------------------------- insert --------------------------------- 
// Insert a NodeData* item into a BinTree, discard the already existed item
bool BinTree::insert(NodeData* item) {
	Node* newNode = new Node;
	newNode->data = item;
	newNode->left = NULL;
	newNode->right = NULL;

	if (this->root == NULL) {
		this->root = newNode;
		return true;
	}
	else {
		Node* cur = this->root;
		while (true) {
			if (*newNode->data == *cur->data) {//if already existing, discard this newNode and delete it
				delete newNode;
				newNode = NULL;
				return false;
			}
			else if (*newNode->data < *cur->data) {
				if (cur->left == NULL) {
					cur->left = newNode;
					return true;
				}
				else {
					cur = cur->left;
				}
			}
			else {
				if (cur->right == NULL) {
					cur->right = newNode;
					return true;
				}
				else {
					cur = cur->right;
				}
			}

		}
	}
	return true;

}

//------------------------- retrieve --------------------------------- 
//Get the NodeData* of a given object in the tree
//If findingItem is exsiting in the tree, return true and record the NodeData* 
//   item of a given object in the tree, otherwise return false
bool BinTree::retrieve(const NodeData& findingItem, NodeData*& record) const {
	Node* cur = root;
	if (cur == NULL) {
		record = NULL;
		return false;
	}
	else {
		record = retrieveHelper(cur, findingItem);
		if (record != NULL) {
			return true;
		}
		else {
			return false;
		}
	}

}

//------------------------- retrieveHelper --------------------------------- 
// Help retrieve() to realize its function
NodeData* BinTree::retrieveHelper(Node* cur, const NodeData& findingItem) const {
	if (cur == NULL) {
		return NULL;
	}
	else if (findingItem == *cur->data) {
		return cur->data;
	}
	else if (findingItem < *cur->data) {
		return retrieveHelper(cur->left, findingItem);
	}
	else {
		return retrieveHelper(cur->right, findingItem);
	}
}

//------------------------- displaySideways ---------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
void BinTree::displaySideways() const {
	sideways(root, 0);
}

//---------------------------- Sideways -------------------------------------
// Helper method for displaySideways
void BinTree::sideways(Node* current, int level) const {
	if (current != NULL) {
		level++;
		sideways(current->right, level);

		// indent for readability, 4 spaces per depth level 
		for (int i = level; i >= 0; i--) {
			cout << "    ";
		}

		cout << *current->data << endl;        // display information of object
		sideways(current->left, level);
	}
}

//------------------------- getHeight --------------------------------- 
// Get the height of a given item in the tree
// If the item is not exist in the tree, the height is 0, return 0
int BinTree::getHeight(const NodeData& findingItem)const {
	Node* cur = this->root;
	NodeData* record;
	int height = 0;
	bool exist = this->retrieve(findingItem, record);

	if (!exist) {
		height = 0;
	}
	else {
		while (true) {//move cur to the already exsiting node
			if (findingItem == *cur->data) {
				break;
			}
			else if (findingItem < *cur->data) {
				if (findingItem == *cur->data) {
					break;
				}
				else {
					cur = cur->left;
				}
			}
			else {
				if (findingItem == *cur->data) {
					break;
				}
				else {
					cur = cur->right;
				}
			}
		}
		height = this->maxDepth(cur); //get the height of the already exsiting node
	}
	return height;
}

//------------------------- maxDepth --------------------------------- 
// Help to realize getHeight() function
int BinTree::maxDepth(Node* cur)const {
	if (cur == nullptr) {
		return 0;
	}
	else {
		int leftDepth = maxDepth(cur->left);
		int rightDepth = maxDepth(cur->right);
		if (leftDepth > rightDepth)
			return ++leftDepth;
		else
			return ++rightDepth;
	}

}

//------------------------- bstreeToArray --------------------------------- 
// Fill an array of Nodedata* by using an inorder traversal of a BinTree
// After tranferring, empty the BinTree
void BinTree::bstreeToArray(NodeData* bsTreeToArray[]) {
	if (this->root != NULL) {
		int index = 0;
		bstreeToArrayHelper(this->root, bsTreeToArray, index);
		this->makeEmpty();
	}
	else {
		return;
	}

}

//------------------------- bstreeToArrayHelper --------------------------------- 
// Help to realize bstreeToArray() function
void BinTree::bstreeToArrayHelper(Node* cur, NodeData* bsTreeToArray[], int& i) {
	if (cur != NULL) {
		bstreeToArrayHelper(cur->left, bsTreeToArray, i);
		bsTreeToArray[i] = cur->data;
		cur->data = NULL;
		i++;
		bstreeToArrayHelper(cur->right, bsTreeToArray, i);
	}

}

//------------------------- arrayToBSTree --------------------------------- 
// Build a balanced BinTree from a sorted array of NodeData* leaving the array filled with NULLs
void BinTree::arrayToBSTree(NodeData* bsTreeArray[]) {
	this->makeEmptyHelper(this->root);

	int endIndex = 0;
	for (int i = 0; i < 100; i++) { // get the length of bsTreeToArray
		if (bsTreeArray[i] != NULL) {
			endIndex++;
		}
	}
	this->arrayToBSTreeHelper(this->root, bsTreeArray, 0, endIndex - 1);

}

//------------------------- arrayToBSTreeHelper --------------------------------- 
// Help to realize arrayToBSTreeHelper() function
void BinTree::arrayToBSTreeHelper(Node*& cur, NodeData* bsTreeArray[], int beginIndex, int endIndex) {
	if (beginIndex > endIndex) {
		cur = NULL;
	}
	else {
		this->insert(bsTreeArray[(beginIndex + endIndex) / 2]);
		bsTreeArray[(beginIndex + endIndex) / 2] = NULL;
		arrayToBSTreeHelper(cur->left, bsTreeArray, beginIndex, (beginIndex + endIndex) / 2 - 1);
		arrayToBSTreeHelper(cur->right, bsTreeArray, (beginIndex + endIndex) / 2 + 1, endIndex);
	}

}

//------------------------- operator= --------------------------------- 
// Current object = parameter with deep copy
BinTree& BinTree::operator=(const BinTree& rightTree) {
	if (*this != rightTree) {
		if (!this->isEmpty()) {
			this->makeEmptyHelper(this->root);
		}
		this->assignHelper(rightTree.root,this->root);
	}
	return *this;

}

//------------------------- assignHelper --------------------------------- 
// Help to realize operator=() function
void BinTree::assignHelper(Node* right, Node*& left) {
	if (right != NULL) {
		left = new Node(); // create a new Node
		NodeData* newData = new NodeData(*right->data); // creat a new NodeData*
		left->data = newData;

		assignHelper(right->left, left->left);
		assignHelper(right->right, left->right);
	}
	else {
		left = NULL;
	}
}

//------------------------- operator== --------------------------------- 
// Is object == parameter? 
// If ==, return true, otherwise return false
bool BinTree::operator==(const BinTree& another) const {
	Node* leftNode = this->root;
	Node* rightNode = another.root;
	return equleHelper(leftNode, rightNode);

}

//------------------------- equleHelper --------------------------------- 
// Help to realize operator==() function
bool BinTree::equleHelper(Node* leftNode, Node* rightNode) const {
	if (leftNode == NULL && rightNode != NULL) {
		return false;
	}
	else if (leftNode != NULL && rightNode == NULL) {
		return false;
	}
	else if (leftNode == NULL && rightNode == NULL) {
		return true;
	}
	else {
		if (*leftNode->data != *rightNode->data) {
			return false;
		}
		equleHelper(leftNode->left, rightNode->left);
		equleHelper(leftNode->right, rightNode->right);
	}
	return true;

}

//------------------------- operator!= --------------------------------- 
// Is object != parameter? 
// If !=, return true, otherwise return false
bool BinTree::operator!=(const BinTree& another) const {
	return *this == another ? false : true;
}

//------------------------- operator<< --------------------------------- 
// overload operator<< display an object of BinTree class inorder
ostream& operator<<(ostream& output, const BinTree& p) {
	if (p.isEmpty()) {
		output << "Tree is empty!" << endl;
	}
	else {
		p.inorderHelper(p.root);
		output << endl;
	}
	return output;

}

//------------------------- destructor --------------------------------- 
// Help to realize operator<<() function
void BinTree::inorderHelper(Node* cur) const {
	if (cur != NULL) {
		inorderHelper(cur->left);
		cout << *cur->data << " ";
		inorderHelper(cur->right);
	}
}
