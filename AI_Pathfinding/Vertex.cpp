#include "Vertex.h"

int Vertex::global_count = 0;

Vertex::Vertex() {
	position = Vector2D(0.0, 0.0); 
	global_count += 1;
	vertex_number = global_count;  
}
Vertex::Vertex(std::string lbl, Vector2D pos) : label(lbl), position(pos) {
	global_count += 1;
	vertex_number = global_count;
}
Vertex::Vertex(std::string lbl, double x, double y) : label(lbl), position(Vector2D(x, y)) {
	global_count += 1;
	vertex_number = global_count;
}

Vector2D Vertex::getPosition() {
	return position;
}

std::string Vertex::getLabel() {
	return label;
}

void Vertex::setPosition(Vector2D pos) {
	position = pos;
}

void Vertex::setPosition(double x, double y) {
	position = Vector2D(x, y);
}

void Vertex::setLabel(std::string lbl) {
	label = lbl;
}