#include <string>
#include <iostream>
#include <fstream>
#include "nodedata.h"
using namespace std;

//-----------------------------------------------------------------------------------------------------------
//GraphL class : It implement a graph by adjacency list, display the graph information and implement depth-first by adjacency list
//It includes these features :
//Public functions:
//    Constructors and destructor :
//    --A default constructor receives no values
//    --A destructor
//    Accessors :
//    --Function depthFirstSearch() to get DFS
//    --Function displayGraph() const to show every node and its edges
//    Mutators :
//    --Function buildGraph(ifstream&) to build a Graph by adjacency list
//    --Function insertEdge(const int&, const int&, const int&) to insert a new edge
//Private utility functions to help corresponding public functions to realize its functions:	
//    --Function dfs(GraphNode&) to help depthFirstSearch() to realize its function
// 
//Implementation and assumptions:
//    --Private structure GraphNode combined with a EdgeNode* edgeHead, a NodeData* data and a bool visited
//    --Private structure EdgeNode combined with a int adjGraphNode, a NodeData* data and a EdgeNode* nextEdge
//    --A NodeData* data pointing a string which is the location name
//    --NodeData is another class which have proper data struct, constructors and comparison operators
//    --In the input data, the first line tells the number of nodes, say n, followed by a text description of 
//      each of the 1 through n nodes, one description per line(50 chars max length).After that, each line 
//      consists of 2 integers representing fromNode and toNode. If the first integer is zero, it means the 
//      end of the data for that one graph
//    --There may be several graphs, each having at most 100 nodes

//-----------------------------------------------------------------------------------------------------------

const int MAXSIZE = 101;       // max size of the array for storing nodes names 
class GraphL
{

	public:
		// Member functions
		GraphL();				   // constructor
		~GraphL();				   // destructor

		// Utility functions
		void buildGraph(ifstream&);// build a Graph by adjacency list
		bool insertEdge(const int&, const int&);// insert a new edge
		void depthFirstSearch();   // get DFS
		void displayGraph() const; // show every node and its edges

	private:
		struct EdgeNode;           // forward reference for the compiler
		struct GraphNode {         // structs used for simplicity, use classes if desired
			EdgeNode* edgeHead;    // head of the list of edges
			NodeData* data;        // data information about each node
			bool visited;
		};
		struct EdgeNode {
		int adjGraphNode;          // subscript of the adjacent graph node
		EdgeNode* nextEdge;
		};

		GraphNode array[MAXSIZE];  // static array for storing nodes names
		int size;                  // number of nodes in the graph

		// Utility functions helpers
		void dfs(GraphNode&);      // helper for depthFirstSearch()
};

