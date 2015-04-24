#include <iostream>
#include "Graph.h"
#include <SFML\Graphics.hpp>

int main() {
	Graph g;

	Vertex v1("A", 0, 0), v2("B", 5, 0) , v3("C", 0, 5), v4("D", 5, 5);

	g.addEdge(v1, v2, 5);
	g.addEdge(v1, v3, 5);
	g.addEdge(v2, v4, 5);
	g.addEdge(v3, v4, 5);

	//g.printGraph();

	// A ---- B
	// |      |
	// |      |
	// C ---- D

	std::cin.get();
	return 0;
}