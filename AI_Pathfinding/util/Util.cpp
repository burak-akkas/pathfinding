#include "Util.h"

float Util::distance(sf::Vector2f p1, sf::Vector2f p2)
{
	float diffY = p1.y - p2.y;
	float diffX = p1.x - p2.x;
	return sqrt((diffY * diffY) + (diffX * diffX));
}

sf::Vector2f Util::normalize(const sf::Vector2f& source)
{
	float length = sqrt((source.x * source.x) + (source.y * source.y));
	if (length != 0)
		return sf::Vector2f(source.x / length, source.y / length);
	else
		return source;
}

std::vector<sf::Vector2f> Util::nodeToVec(std::vector<Node*> n) {
	std::vector<sf::Vector2f> tmp;
	sf::Vector2f vec;
	for (size_t i = 0; i < n.size(); i++) {
		vec.x = n[i]->getX() * 32;
		vec.y = n[i]->getY() * 32;

		tmp.push_back(vec);
	}

	return tmp;
}