#include "graphl.h"
#include <list>
#include <iomanip>
#include <iostream>
#include <string>
#include <climits>

//------------------------- constructor ---------------------------------
// Default constructor, initialize a GraphL 
GraphL::GraphL() {
	for (int i = 1; i <= MAXSIZE-1;i++) {
		array[i].data = NULL;
		array[i].edgeHead = NULL;
		array[i].visited = false;
	}
	size = 0;

}

//------------------------- destructor ---------------------------------
// Destructor for class GraphL
GraphL::~GraphL() {
	for (int i = 1; i <= size; i++) {
		//delete NodeData
		delete array[i].data;
		array[i].data = NULL;
		
		if (array[i].edgeHead != NULL) {
			//delete dummy header-edgeHead 
			EdgeNode* cur= array[i].edgeHead->nextEdge;
			delete array[i].edgeHead;
			array[i].edgeHead = NULL;

			//delete edges
			while (cur != NULL) {
				EdgeNode* temp = cur;
				cur = cur->nextEdge;
				delete temp;
				temp = NULL;
			}
		}
	}
}

//------------------------- buildGraph ---------------------------------
// Build a Graph by adjacency list 
void GraphL::buildGraph(ifstream & file) {
	string input;
	int edgeFrom = 0, edgeTo = 0;
	getline(file, input);

	if (input == "") {
		file.close();
		return;
	}

	size = stoi(input);

	for (int i = 1; i <= size; i++) {
		getline(file, input);
		array[i].data = new NodeData(input);
		//creat a dummy header-edgeHead to store node's corresponding number
		array[i].edgeHead = new EdgeNode;
		array[i].edgeHead->adjGraphNode = i;
		array[i].edgeHead->nextEdge = NULL;
	}
	while (true) {
		file >> edgeFrom;
		if (edgeFrom == 0) {
			getline(file, input);
			break;
		}
		else {
			file >> edgeTo;
		}
		insertEdge(edgeFrom, edgeTo);
	}

}

//------------------------- insertEdge ---------------------------------
// Insert a new edge 
bool GraphL::insertEdge(const int& from, const int& to) {
	if (from > size || to > size || from < 1 || to < 1) {
		return false;
	}
	else {
		EdgeNode* newEdge = new EdgeNode;
		newEdge->adjGraphNode = to;
		newEdge->nextEdge = NULL;

		if (array[from].edgeHead->nextEdge == NULL) {
			array[from].edgeHead->nextEdge = newEdge;
		}
		else {
			newEdge->nextEdge = array[from].edgeHead->nextEdge;
			array[from].edgeHead->nextEdge = newEdge;
		}
	}
	return true;

}

//------------------------- depthFirstSearch ---------------------------------
// Get DFS 
void GraphL::depthFirstSearch() {
	cout << "Depth - fisrt ordering :";
	for (int i = 1; i <= size; i++) {
		if (array[i].visited != true) {
			dfs(array[i]);
		}
	}
	cout << endl;

}

//------------------------- dfs ---------------------------------
// Help depthFirstSearch() to realize its function 
void GraphL::dfs(GraphNode& vertex) {
	vertex.visited = true;
	cout << vertex.edgeHead->adjGraphNode << "  ";
	list<int> con;
	if (vertex.edgeHead->nextEdge != NULL) {
		EdgeNode* cur = vertex.edgeHead->nextEdge;
		while (cur != NULL) {
			con.push_back(cur->adjGraphNode);
			cur = cur->nextEdge;
		}
	}
	for (list<int>::iterator index = con.begin(); index != con.end(); index++) {
		if (array[*index].visited != true) {
			dfs(array[*index]);
		}
	}

}

//------------------------- displayGraph ---------------------------------
// Show every node and its edges 
void GraphL::displayGraph() const {
	cout << "Graph:" << endl;
	for (int i = 1; i <= size; i++) {
		cout << left << setw(3) << "Node" << i << "       " << *array[i].data << endl;
		EdgeNode* cur = array[i].edgeHead->nextEdge;
		while (cur != NULL) {
			cout << left << setw(3) << "edge  " << i << "  " << cur->adjGraphNode << endl;
			cur = cur->nextEdge;
		}
		cout << endl;

	}
}



