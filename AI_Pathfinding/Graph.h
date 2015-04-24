#include <vector>
#include "Edge.h"

class Graph {
private:
	std::vector< std::vector<Edge> > adjecency;
public:
	Graph();
	Graph(int n);
	void addEdge(Vertex from, Vertex to, int weight);
	std::vector<Vertex> getAdjecency(Vertex vertex);
	int totalWeight();
	void printGraph();
};