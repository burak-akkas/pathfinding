#ifndef GRAPH_INCLUDE
#define GRAPH_INCLUDE
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include "Node.h"

class Graph {
private:
	int size;
	std::vector< std::vector<Node*> > grid;
	void initGrid();
	bool search(Node* n, std::vector<Node*> path);
public:
	Graph();
	Graph(int s);
	~Graph();

	void setObstacle(int x, int y);
	void resetObstacle(int x, int y);
	bool isObstacle(int x, int y);
	void resetNodes();
	std::vector<int> findShortestPathAstar(int start_x, int start_y, int finish_x, int finish_y, std::vector<Node*> *path);
	void printGraph();
	std::vector<int> printPath(std::vector<Node*> *path, Node* start, Node* finish);
	std::vector<int> emptyPath();
};

#endif