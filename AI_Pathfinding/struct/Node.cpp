#include "Node.h"

Node::Node() {
	x = 0;
	y = 0;
	obstacle = false;
	opened = false;
	closed = false;
	g_score = 0;
	f_score = 0;
	h_score = 0;

	parent = NULL;
}

Node::Node(int x_t, int y_t) {
	Node();

	x = x_t;
	y = y_t;
}

int Node::getX() {
	return x;
}

int Node::getY() {
	return y;
}

Node* Node::getParent() {
	return parent;
}

void Node::setParent(Node* n) {
	parent = n;
}

void Node::setGScore(int score) {
	g_score = score;
}

int Node::getGScore(Node *n) {
	return n->getGScore() + ((x == n->getX() || y == n->getY()) ? 10 : 14);
}

int Node::getGScore() {
	return g_score;
}

int Node::getHScore(Node *n) {
	return (abs(n->getX() - x) + abs(n->getY() - y)) * 10;
}

int Node::getHScore() {
	return h_score;
}

int Node::getFScore() {
	return f_score;
}

bool Node::hasParent() {
	return parent != NULL;
}

void Node::computeScoresAstar(Node *end) {
	g_score = getGScore(parent); // get parent g score
	h_score = getHScore(end); // get h score from this node to end node
	f_score = g_score + h_score; // f(v) = h(v) + g(v), h=heuristics, g=dijkstra
}

void Node::computeScoresDijkstra() { // implemented after A-star
	h_score = 0; // h(v) = 0 (non informative heuristics function)
	g_score = getGScore(parent); // get parent g score
	f_score = g_score; // f(v) = h(v) + g(v), h(v) always will be 0. 
}

void Node::computeScoresBFS(Node *end) {
	g_score = 0; // bfs does not depends on g score
	h_score = getHScore(end); // get h score from this node to end(destination) node
	f_score = h_score; // f(v) = h(v) + g(v), g(v) always will be 0.
}


void Node::setObstacle() {
	obstacle = true;
}

void Node::resetObstacle() {
	obstacle = false;
}

bool Node::isObstacle() {
	return obstacle;
}

bool Node::equals(Node *n) {
	if (n == NULL) {
		return false;
	}
	else if (n->getX() == x &&
		n->getY() == y &&
		n->isObstacle() == obstacle) {
		return true;
	}
	else {
		return false;
	}
}

std::string Node::toString() {
	return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " +
		std::to_string(obstacle) + ")";
}