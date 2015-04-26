#include "Graph.h"

int main() {
	Graph *g = new Graph(8);

	g->setObstacle(1, 1);
	g->setObstacle(1, 2);
	g->setObstacle(1, 3);
	g->setObstacle(1, 4);
	g->setObstacle(1, 5);
	g->setObstacle(1, 6);
	g->setObstacle(1, 0);
	g->setObstacle(5, 6);
	g->setObstacle(3, 2);
	g->setObstacle(6, 1);
	g->setObstacle(6, 3);
	g->setObstacle(6, 4);
	g->setObstacle(5, 4);
	g->setObstacle(5, 3);

	std::cout << g->findShortestPathAstar(0, 0, 7, 0);

	//g->printGraph();

	std::cin.get();

	return 0;
}