#include <list>
#include <iomanip>
#include <iostream>
#include <string>
#include "limits.h"
#include "graphm.h"

//------------------------- constructor ---------------------------------
// Default constructor, initialize a GraphM 
GraphM::GraphM() {
	for (int i = 1; i < MAXNODES;i++) {
		data[i] = NodeData();
		for (int j = 1; j < MAXNODES; j++) {
			C[i][j] = INT_MAX;			
			T[i][j].dist = INT_MAX;
			T[i][j].visited = false;
			T[i][j].path = 0;
		}
	}
	size = 0;

}

//------------------------- buildGraph ---------------------------------
// Build up graph node information and adjacency matrix of edges between each node
GraphM GraphM::buildGraph(ifstream& file){
	string input;
	int from=0,to=0,weight=0;
	getline(file, input);

	if (input == "") {
		file.close();
		return *this;
	}

	size = stoi(input);
	for (int i = 1; i <= size;i++) {
		getline(file, input);
		data[i] = input;
	}
	while (true) {
		file >> from;
		if (from == 0) {
			getline(file, input);
			break;
		}
		else {
			file>> to >> weight;
		}
		insertEdge(from,to,weight);
	}
	return *this;

}

//------------------------- insertEdge ---------------------------------
// Insert an edge into graph between two given nodes
bool GraphM::insertEdge(const int& from, const int& to, const int& weight) {
	if (from > MAXNODES || to > MAXNODES || from < 1 || to < 1) {
		return false;
	}
	else {
		C[from][to] = weight;
		return true;
	}

}

//------------------------- removeEdge ---------------------------------
// Remove an edge between two given nodes
bool GraphM::removeEdge(const int& from, const int& to) {
	if (from > MAXNODES || to > MAXNODES || from < 1 || to < 1) {
		return false;
	}
	else {
		if (C[from][to] >= 0) {
			C[from][to] = INT_MAX;
			return true;
		}
		else {
			return false;
		}
	}

}

//------------------------- findShortestPath ---------------------------------
// Find the shortest path between every node to every other node
void GraphM::findShortestPath() {
	for (int source = 1; source <= size; source++) {
		T[source][source].dist = 0;

		for (int i = 1; i <= size; i++) {
			int v = 0;
			int minDist = INT_MAX;
			int j = 1;
			//find the shortest distance of not visited points
			for (j; j <= size; j++) {
				if (T[source][j].visited != true) {
					if (T[source][j].dist < minDist) {
						minDist = T[source][j].dist;
						v = j;

					}
				}
			}
			// if can't find v, end the loop
			if (v == 0) {
				break;
			}

			T[source][v].visited = true;
			for (int m = 1; m <= size; m++) {
				if (T[source][m].visited != true) {
					if ((float)T[source][m].dist >(float) T[source][v].dist + C[v][m]) {
						T[source][m].dist = T[source][v].dist + C[v][m];
						T[source][m].path = v;
					}
				}
			}
		}
	}
}


//------------------------- displayAll ---------------------------------
// Display all the shoretest paths between every node to every other node
void GraphM::displayAll() const {
	list<int> con; // used to store path nodes
	int prePoint;
	cout << right << setw(25) << "Description" << right << setw(4) << "  " << left << setw(15) << "From Node" << left << setw(15) << "To Node" << left << setw(15) << "Dijkstra's" << left << setw(15) << "Path" << endl;
	for (int i = 1; i <= this->size; i++) {
		cout << right << setw(25) << this->data[i] << right << setw(4) << "  " << endl;
		for (int j = 1; j <= this->size; j++) {
			if (this->T[i][j].dist != 0) {
				if (this->T[i][j].dist != INT_MAX) {
					cout << left << setw(29) << " ";
					cout << left << setw(15) << i;
					cout << left << setw(15) << j;
					cout << left << setw(15) << this->T[i][j].dist;
					con.clear();
					con.push_back(j);
					prePoint = T[i][j].path;
					while (prePoint != i) {
						con.push_back(prePoint);
						prePoint = this->T[i][prePoint].path;
					}
					con.push_back(i);
					con.reverse();
					for (list<int>::iterator index = con.begin(); index != con.end(); index++)
					{
						cout << left << setw(2) << *index << " ";
					}
					cout << endl;
				}
				else {
					cout << left << setw(29) << " ";
					cout << left << setw(15) << i;
					cout << left << setw(15) << j;
					cout << left << setw(15) << "----" << endl;
				}
			}
		}
	}
	cout << endl;
}

//------------------------- display ---------------------------------
// Display the shortest distance with path info between the fromNode to toNode
void GraphM::display(const int& fromNode, const int& toNode) const {
	list<int> con; // used to store path nodes
	int prePoint;
	if (T[fromNode][toNode].dist != INT_MAX) {
		cout << right << setw(8) << fromNode;
		cout << right << setw(8) << toNode;
		cout << right << setw(8) << T[fromNode][toNode].dist;
		cout << "            ";
		con.clear();
		con.push_back(toNode);
		prePoint = T[fromNode][toNode].path;
		while (prePoint != fromNode) {
			con.push_back(prePoint);
			prePoint = T[fromNode][prePoint].path;
		}
		con.push_back(fromNode);
		con.reverse();
		for (list<int>::iterator index = con.begin(); index != con.end(); index++) {
			cout << right << setw(2) << *index;
		}
		cout << endl;
		for (list<int>::iterator index = con.begin(); index != con.end(); index++) {

			cout << left << setw(4) << data[*index] << endl;
		}
		cout << endl;
	}
	else {
		cout << right << setw(8) << fromNode;
		cout << right << setw(8) << toNode;
		cout << "     " << "----" << endl;
		cout << endl;
	}

}



