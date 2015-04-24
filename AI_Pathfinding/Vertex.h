#include <string>
#include "Vector2D.h"

class Vertex {
private:
	Vector2D position;
	std::string label;
	// counting global vertex number
	static int global_count;
public:
	Vertex();
	Vertex(std::string lbl, Vector2D pos);
	Vertex(std::string lbl, double x, double y);

	// object vertex number
	int vertex_number;

	// Getter
	Vector2D getPosition();
	std::string getLabel();

	// Setter
	void setPosition(Vector2D pos);
	void setPosition(double x, double y);
	void setLabel(std::string lbl);
};