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
	//int heuristic(Node *current, Node *target);
	bool search(Node* n, std::vector<Node*> path);
public:
	Graph();
	Graph(int s);

	void setObstacle(int x, int y);
	std::string findShortestPathAstar(int start_x, int start_y, int finish_x, int finish_y);
	void printGraph();
	void printPath(std::vector<Node*> path, Node* start, Node* finish);
};