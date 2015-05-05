#include "Graph.h"

Graph::Graph() {
	size = 0;
	initGrid();
}

Graph::Graph(int s) {
	size = s;
	initGrid();
}

void Graph::initGrid() {
	for (int y = 0; y < size; y++) {
		std::vector<Node*> tmp;
		for (int x = 0; x < size; x++) {
			tmp.push_back(new Node(x, y));
		}
		grid.push_back(tmp);
		tmp.clear();
	}
}

/*int Graph::heuristic(Node *current, Node *target) {
	return fmaxf(abs(current->getX() - target->getX()),
		abs(current->getY() - target->getY()));
}*/

bool Graph::search(Node* n, std::vector<Node*> path) {
	for (size_t y = 0; y < path.size(); y++) {
		if (path.at(y)->equals(n)) {
			return true;
		}
	}
	return false;
}

void Graph::setObstacle(int x, int y) {
	grid.at(y).at(x)->setObstacle();
}

std::vector<int> Graph::findShortestPathAstar(int start_x, int start_y, int finish_x, int finish_y) {

	std::vector<Node*> path;

	Node *start = grid[start_y][start_x];
	Node *end = grid[finish_y][finish_x];
	Node *current = NULL;
	Node *child = NULL;

	std::list<Node*> openList;
	std::list<Node*> closedList;
	std::list<Node*>::iterator i;

	openList.push_back(start);
	start->opened = true;

	int n = 0;

	while (current != end && n != 100)
	{
		for (i = openList.begin(); i != openList.end(); ++i)
		{
			if (i == openList.begin() || (*i)->getFScore() <= current->getFScore())
			{
				current = (*i);
			}
		}

		if (current == end)
		{
			break;
		}

		openList.remove(current);
		current->opened = false;

		closedList.push_back(current);
		current->closed = true;

		for (int x = -1; x < 2; x++)
		{
			for (int y = -1; y < 2; y++)
			{
				if (x == 0 && y == 0)
				{
					continue;
				}

				if (current->getX() + x < 0 || current->getY() + y < 0 || current->getX() + x == size || current->getY() + y == size) {
					continue;
				}

				child = grid[current->getY() + y][current->getX() + x];

				if (child->closed || child->isObstacle())
				{
					continue;
				}

				if (x != 0 && y != 0)
				{
					if (grid[current->getY() + y][current->getX()]->isObstacle() || grid[current->getY() + y][current->getX()]->closed)
					{
						continue;
					}
					if (grid[current->getY()][current->getX() + x]->isObstacle() || grid[current->getY()][current->getX() + x]->closed)
					{
						continue;
					}
				}

				if (child->opened)
				{
					if (child->getGScore() > child->getGScore(current))
					{
						child->setParent(current);
						child->computeScores(end);
					}
				}
				else
				{
					openList.push_back(child);
					child->opened = true;

					child->setParent(current);
					child->computeScores(end);
				}
			}
		}

		n++;

		if (n >= 100) { std::vector<int> t; return t; }
	}

	while (current->hasParent() && !current->equals(start))
	{
		path.push_back(current);
		current = current->getParent();
	}

	// print path
	//printPath(path, start, end);

	// for testing
	//for (size_t i = 0; i < path.size(); i++) {
	//	std::cout << path[i]->toString() << "\n";
	//}

	return printPath(path, start, end);
}

void Graph::printGraph() {
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			Node *n = grid.at(y).at(x);
			std::cout << "[" << n->isObstacle() << "] ";
		}
		std::cout << std::endl;
	}
}

std::vector<int> Graph::printPath(std::vector<Node*> path, Node* start, Node* finish) {
	std::vector<int> t;	t.push_back(0);

	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			if (grid.at(y).at(x)->isObstacle()) {
				std::cout << "X ";
				t.push_back(1);
			}
			else if (grid.at(y).at(x)->equals(start)) {
				std::cout << "S ";
				t.push_back(4);
			}
			else if (grid.at(y).at(x)->equals(finish)) {
				std::cout << "F ";
				t.push_back(6);
			}
			else if (search(grid.at(y).at(x), path)) {
				std::cout << "* ";
				t.push_back(2);
			}
			else {
				std::cout << "0 ";
				t.push_back(0);
			}
		}

		std::cout << std::endl;
	}

	return t;
}