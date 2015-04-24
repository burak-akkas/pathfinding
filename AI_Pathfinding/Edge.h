#include "Vertex.h"

class Edge {
private:
	Vertex destination_vertex;
	int weight;
public:
	Edge();
	Edge(Vertex to, int w) : destination_vertex(to), weight(w) {}
	int getWeight() { return weight; }
	Vertex getDestinationVertex() { return destination_vertex; }
};