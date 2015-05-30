#ifndef NODE_INCLUDE
#define NODE_INCLUDE
#include <string>
#include <cmath>

class Node {
private:
	int	x, y;
	bool obstacle;
	int g_score;
	int h_score;
	int f_score;
	Node *parent;
public:
	bool opened, closed;

	Node();
	Node(int x_t, int y_t);

	int getX();
	int getY();
	Node* getParent();
	void setParent(Node* n);
	void setObstacle();
	bool isObstacle();
	void resetObstacle();

	void setGScore(int score);
	int getGScore();
	int getGScore(Node *n);

	int getFScore();

	int getHScore(Node *n);
	int getHScore();

	bool hasParent();

	void computeScoresAstar(Node *end);
	void computeScoresDijkstra();
	void computeScoresBFS(Node *end);

	bool equals(Node *n);
};

#endif
