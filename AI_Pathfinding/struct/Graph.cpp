#include "Graph.h"

Graph::Graph() {
	size = 0;
	bound = 1000;
	initGrid();
}

Graph::Graph(int s) {
	size = s;
	bound = 1000;
	initGrid();
}

Graph::~Graph() {
	grid.clear();
	grid.shrink_to_fit();
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

void Graph::resetObstacle(int x, int y) {
	grid.at(y).at(x)->resetObstacle();
}

bool Graph::isObstacle(int x, int y) {
	return grid.at(y).at(x)->isObstacle();
}

std::vector<int> Graph::findShortestPathAstar(int start_x, int start_y, int finish_x, int finish_y, std::vector<Node*> *path) {
	sf::Clock execClock;
	execClock.restart();

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

	while (current != end && n != bound) {
		for (i = openList.begin(); i != openList.end(); ++i) {
			if (i == openList.begin() || (*i)->getFScore() <= current->getFScore())	{
				current = (*i);
			}
		}

		if (current == end) {
			break;
		}

		openList.remove(current);
		current->opened = false;

		closedList.push_back(current);
		current->closed = true;

		for (int x = -1; x < 2; x++) {
			for (int y = -1; y < 2; y++) {
				if (x == 0 && y == 0) {
					continue;
				}

				if (current->getX() + x < 0 || current->getY() + y < 0 || current->getX() + x == size || current->getY() + y == size) {
					continue;
				}

				child = grid[current->getY() + y][current->getX() + x];

				if (child->closed || child->isObstacle()) {
					continue;
				}

				if (x != 0 && y != 0) {
					if (grid[current->getY() + y][current->getX()]->isObstacle() || grid[current->getY() + y][current->getX()]->closed) {
						continue;
					}
					if (grid[current->getY()][current->getX() + x]->isObstacle() || grid[current->getY()][current->getX() + x]->closed) {
						continue;
					}
				}

				if (child->opened) {
					if (child->getGScore() > child->getGScore(current)) {
						child->setParent(current);
						child->computeScoresAstar(end);
					}
				}
				else {
					openList.push_back(child);
					child->opened = true;

					child->setParent(current);
					child->computeScoresAstar(end);
				}
			}
		}

		n++;

		if (n >= bound) {
			std::vector<int> t; 
			std::cout << "Tried " << bound << " times to find a path!" << std::endl;
			resetNodes();
			return t; 
		}
	}

	while (current->hasParent() && !current->equals(start))	{
		path->push_back(current);
		current = current->getParent();
	}

	execTime = execClock.getElapsedTime();

	resetNodes();

	return printPath(path, start, end);
}

// example trace of dijksta's algorithm
// http://jhave.org/algorithms/graphs/Dijkstra/dijkstra.shtml
std::vector<int> Graph::findShortestPathDijkstra(int start_x, int start_y, int finish_x, int finish_y, std::vector<Node*> *path) {
	sf::Clock execClock;
	execClock.restart();

	Node *start = grid[start_y][start_x];
	Node *end = grid[finish_y][finish_x];
	Node *current = NULL;
	Node *child = NULL;

	std::list<Node*> openList;
	std::list<Node*>::iterator i;

	openList.push_back(start);
	start->opened = true;

	int n = 0;

	while (current != end && n != bound) {
		for (i = openList.begin(); i != openList.end(); ++i) {
			if (i == openList.begin() || (*i)->getGScore() <= current->getGScore())	{
				current = (*i);
			}
		}

		if (current == end) {
			break;
		}

		openList.remove(current);
		current->opened = false;
		current->closed = true;

		for (int x = -1; x < 2; x++) {
			for (int y = -1; y < 2; y++) {
				if (x == 0 && y == 0) {
					continue;
				}

				if (current->getX() + x < 0 || current->getY() + y < 0 || current->getX() + x == size || current->getY() + y == size) {
					continue;
				}

				child = grid[current->getY() + y][current->getX() + x];

				if (child->closed || child->isObstacle()) {
					continue;
				}

				if (x != 0 && y != 0) {
					if (grid[current->getY() + y][current->getX()]->isObstacle() || grid[current->getY() + y][current->getX()]->closed) {
						continue;
					}
					if (grid[current->getY()][current->getX() + x]->isObstacle() || grid[current->getY()][current->getX() + x]->closed) {
						continue;
					}
				}

				if (child->opened) {
					if (child->getGScore() > child->getGScore(current))
					{
						child->setParent(current);
						child->computeScoresDijkstra();
					}
				}
				else {
					openList.push_back(child);
					child->opened = true;

					child->setParent(current);
					child->computeScoresDijkstra();
				}
			}
		}

		n++;

		if (n >= bound) {
			std::vector<int> t;
			std::cout << "Tried " << bound << " times to find a path!" << std::endl;
			resetNodes();
			return t;
		}
	}

	while (current->hasParent() && !current->equals(start)) {
		path->push_back(current);
		current = current->getParent();
	}

	execTime = execClock.getElapsedTime();

	resetNodes();

	return printPath(path, start, end);
}

// used psuedo-code
// http://en.wikibooks.org/wiki/Artificial_Intelligence/Search/Heuristic_search/Best-first_search
std::vector<int> Graph::findShortestPathBFS(int start_x, int start_y, int finish_x, int finish_y, std::vector<Node*> *path) {
	sf::Clock execClock;
	execClock.restart();

	Node *start = grid[start_y][start_x];
	Node *end = grid[finish_y][finish_x];
	Node *current = NULL;
	Node *child = NULL;

	// Define a list, OPEN
	std::list<Node*> openList;
	// Define a list, CLOSED
	std::list<Node*> closedList;
	std::list<Node*>::iterator i;

	openList.push_back(start);
	start->opened = true;

	int n = 0;

	while (current != end && n != bound) { // IF bound has been reached, fail
		for (i = openList.begin(); i != openList.end(); ++i) {
			if (i == openList.begin() || (*i)->getFScore() <= current->getFScore())	{
				current = (*i);
			}
		}

		// IF any successor to n is the goal node, return success and the solution
		if (current == end) {
			break;
		}

		openList.remove(current);
		current->opened = false;

		closedList.push_back(current);
		current->closed = true;

		for (int x = -1; x < 2; x++) {
			for (int y = -1; y < 2; y++) {
				if (x == 0 && y == 0) {
					continue;
				}

				if (current->getX() + x < 0 || current->getY() + y < 0 || current->getX() + x == size || current->getY() + y == size) {
					continue;
				}

				child = grid[current->getY() + y][current->getX() + x];

				if (child->closed || child->isObstacle()) {
					continue;
				}

				if (x != 0 && y != 0) {
					if (grid[current->getY() + y][current->getX()]->isObstacle() || grid[current->getY() + y][current->getX()]->closed) {
						continue;
					}
					if (grid[current->getY()][current->getX() + x]->isObstacle() || grid[current->getY()][current->getX() + x]->closed) {
						continue;
					}
				}
				if (!child->opened) {
					openList.push_back(child);
					child->opened = true;

					child->setParent(current);
					child->computeScoresBFS(end);
				}
			}
		}

		n++;

		if (n >= bound) {
			std::vector<int> t;
			std::cout << "Tried " << bound << " times to find a path!" << std::endl;
			resetNodes();
			return t;
		}
	} // looping structure by sending the algorithm back to head of the loop


	while (current->hasParent() && !current->equals(start))	{
		path->push_back(current);
		current = current->getParent();
	}

	execTime = execClock.getElapsedTime();

	resetNodes();

	// set-up path for rendering
	return printPath(path, start, end);
}

std::vector<int> Graph::findShortestPathIDAstar(int start_x, int start_y, int finish_x, int finish_y, std::vector<Node*> *path) {
	std::vector<int> t;
	return t;
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

std::vector<int> Graph::printPath(std::vector<Node*> *path, Node* start, Node* finish) {
	std::vector<int> t;

	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			if (grid.at(y).at(x)->isObstacle()) {
				t.push_back(54);
			}
			else if (grid.at(y).at(x)->equals(start)) {
				t.push_back(0);
			}
			else if (grid.at(y).at(x)->equals(finish)) {
				t.push_back(0);
			}
			else if (search(grid.at(y).at(x), *path)) {
				t.push_back(0);
			}
			else {
				t.push_back(0);
			}
		}
	}

	return t;
}

std::vector<int> Graph::emptyPath() {
	std::vector<int> t;

	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			if (grid.at(y).at(x)->isObstacle()) {
				t.push_back(54);
			}
			else {
				t.push_back(0);
			}
		}
	}

	return t;
}

void Graph::resetNodes() {
	// clear opened, closed states of nodes
	for (size_t i = 0; i < grid.size(); i++) {
		for (size_t j = 0; j < grid.at(i).size(); j++) {
			grid.at(i).at(j)->closed = false;
			grid.at(i).at(j)->opened = false;
		}
	}
}

sf::Time Graph::getExecTime() {
	return execTime;
}

int Graph::getSize() {
	return size;
}