#ifndef GRAPH_INCLUDE
#define GRAPH_INCLUDE
#include <iostream>
#include <fstream> // text read /temporary
#include <vector>
#include <list>
#include <SFML\System\Clock.hpp>
#include <SFML\System\Time.hpp>
#include "Node.h"

class Graph {
private:
	int size, bound;
	sf::Time execTime;
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
	std::vector<int> Graph::findShortestPathDijkstra(int start_x, int start_y, int finish_x, int finish_y, std::vector<Node*> *path);
	std::vector<int> Graph::findShortestPathBFS(int start_x, int start_y, int finish_x, int finish_y, std::vector<Node*> *path);
	sf::Time getExecTime();
	void printGraph();
	std::vector<int> printPath(std::vector<Node*> *path, Node* start, Node* finish);
	std::vector<int> emptyPath();
	
	void loadGrid(std::string path);
};

#endif