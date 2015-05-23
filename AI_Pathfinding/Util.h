#pragma once
#include "Node.h"
#include <SFML\Graphics\Vertex.hpp>
#include <cmath>
#include <vector>

class Util {
	public:
		static float distance(sf::Vector2f p1, sf::Vector2f p2);
		static sf::Vector2f normalize(const sf::Vector2f& source);
		static std::vector<sf::Vector2f> nodeToVec(std::vector<Node*> n);
};