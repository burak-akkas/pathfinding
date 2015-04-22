#include <iostream>
#include "Graph.h"

int main() {
	Graph g;
	std::vector<int> t;

	g.addEdge(3, 2, 5);
	g.addEdge(3, 3, 10);
	g.addEdge(1, 2, 5);
	g.addEdge(2, 3, 8);
	g.addEdge(3, 4, 2);

	t = g.getAdjecency(3);

	for (std::vector<int>::iterator it = t.begin(); it != t.end(); ++it) {
		std::cout << *it << ",";
	}

	std::cout << std::endl << "Total weight: " << g.totalWeight() << std::endl;

	std::cin.get();

	return 0;
}