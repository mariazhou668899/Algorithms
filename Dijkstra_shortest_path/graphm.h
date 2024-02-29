#include <string>
#include <iostream>
#include <fstream>
#include "nodedata.h"
using namespace std;

//-----------------------------------------------------------------------------------------------------------
//GraphM class : It implement a graph by adjacency matrix and implement Dijkstra's  shortest  path algorithm
//It includes these features :
//Public functions:
//    Constructors :
//    --A default constructor receives no values
//    Accessors :
//    --Function findShortestPath( ) to find the shortest path between every node to every other node
//    --Function displayAll( ) const to display all the shoretest paths between every node to every other node
//    --Function display(const int&, const int&) const to display the shortest distance with path info between the fromNode to toNode
//    Mutators :
//    --Function buildGraph(ifstream&) to build up graph node information and adjacency matrix of edges between each node
//    --Function insertEdge(const int&, const int&, const int&) to insert an edge into graph between two given nodes
//    --Function removeEdge(const int&, const int&) to remove an edge between two given nodes
// 
//Implementation and assumptions:
//    --Private structure TableType combined with a bool visited, a int dist and a int path
//    --A NodeData* data pointing a string which is the location name
//    --NodeData is another class which have proper data struct, constructors and comparison operators
//    --In the input data, the first line tells the number of nodes, say n, followed by a text description of 
//      each of the 1 through n nodes, one description per line(50 chars max length).After that, each line 
//      consists of 3 integers representing an edge.If there is an edge from node 1 to node 2 with a label of 10, 
//      the data is : 1 2 10. If the first integer is zero, it means the end of the data for that one graph
//    --There may be several graphs, each having at most 100 nodes
//    --If there is no edge between 2 nodes, the weight is INT_MAX

//-----------------------------------------------------------------------------------------------------------

const int MAXNODES = 101;
class GraphM{

	public:
		// Member functions
		GraphM();								   // constructor	

		// Utility functions
		GraphM buildGraph(ifstream&);			   // build up graph node information and adjacency matrix of edges between each node
		bool insertEdge(const int&, const int&, const int&); //insert an edge into graph between two given nodes 
		bool removeEdge(const int&, const int&) ;  // remove an edge between two given nodes
		void findShortestPath( );                  // find the shortest path between every node to every other node
		void displayAll( ) const;                  // display all the shoretest paths between every node to every other node
		void display(const int&, const int&) const;// display the shortest distance with path info between the fromNode to toNode

	private:
		struct TableType {
			bool visited;                         // whether node has been visited
			int dist;                             // shortest distance from source known so far
			int path;                             // previous node in path of min dist
		};			

		NodeData data[MAXNODES];                  // data for graph nodes 
		int C[MAXNODES][MAXNODES];                // Cost array, the adjacency matrix
		int size;                                 // number of nodes in the graph
		TableType T[MAXNODES][MAXNODES];          // stores visited, distance, path
};

