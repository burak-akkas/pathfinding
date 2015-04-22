#include <vector>

class Edge {
private:
	int vertex;
	int weight;
public:
	Edge();
	Edge(int v, int w) : vertex(v), weight(w) {}
	int getWeight() { return weight; }
	int getVertex() { return vertex; }
};

class Graph {
private:
	std::vector< std::vector<Edge> > adjecency;
public:
	Graph();
	Graph(int n);
	void addEdge(int from, int to, int weight);
	std::vector<int> getAdjecency(int vertex);
	int totalWeight();
};