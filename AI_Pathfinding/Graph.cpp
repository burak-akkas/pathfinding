#include "Graph.h"
#include <iostream>

Graph::Graph() {
	adjecency.resize(10);
}

Graph::Graph(int n) {
	adjecency.resize(n);
}


void Graph::addEdge(Vertex from, Vertex to, int weight) {
	adjecency[from.vertex_number].push_back(Edge(to, weight));
}

std::vector<Vertex> Graph::getAdjecency(Vertex vertex) {
	std::vector<Vertex> t;
	//for (size_t i = 0; i < adjecency[vertex].size(); ++i) {
	//	t.push_back(adjecency[vertex].at(i).getDestinationVertex());
	//}

	return t;
}

int Graph::totalWeight() {
	int total = 0;

	for (size_t i = 0; i < adjecency.size(); ++i) {
		for (size_t j = 0; j < adjecency[i].size(); ++j) {
			total += adjecency[i].at(j).getWeight();
		}
	}

	return total;
}

void Graph::printGraph() {
	for (int i = 0; i < adjecency.size(); i++)
	{
		std::vector<int> t;
		//t = getAdjecency(i);
		if (t.size() != 0) {
			std::cout << i << "->";
			for (std::vector<int>::iterator it = t.begin(); it != t.end(); ++it) {
				std::cout << *it << "->";
			}
			std::cout << std::endl;
		}
	}
}