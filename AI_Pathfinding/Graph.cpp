#include "Graph.h"

Graph::Graph() {
	adjecency.resize(10);
}

Graph::Graph(int n) {
	adjecency.resize(n);
}

void Graph::addEdge(int from, int to, int weight) {
	adjecency[from].push_back(Edge(to, weight));
}

std::vector<int> Graph::getAdjecency(int vertex) {
	std::vector<int> t;
	for (size_t i = 0; i < adjecency[vertex].size(); ++i) {
		t.push_back(adjecency[vertex].at(i).getVertex());
	}

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