#include "Walker.h"

sf::CircleShape Walker::circle(15);
sf::Vector2f normalize(const sf::Vector2f& source);
float distance(sf::Vector2f p1, sf::Vector2f p2);

Walker::Walker() {
	speed = 100.f;
	
	position.x = 8.f * 32;
	position.y = 8.f * 32;

	circle.setFillColor(sf::Color(0, 0, 0));
	circle.setPosition(position.x, position.y);
	
	canMove = false;
}

Walker::Walker(float x, float y, float s) {
	speed = 100.f;

	position.x = x;
	position.y = y;

	circle.setFillColor(sf::Color(0, 0, 0));
	circle.setPosition(position.x, position.y);

	circle.setRadius(s);

	canMove = false;
}

void Walker::move(float time) {
	if (canMove == true)
	{
		if (distance(position, destination) > 5.f)
		{
			position += direction * speed * time;
			circle.setPosition(position);
		}
		else if (path.size() > 0)
		{
			setDestination(&path.back());
			path.pop_back();
		}
		//if (path.size() == 0 && distance(position, destination) < 10.f)
		else
		{
			canMove = false;
			//circle.setPosition(destination);
		}
	}
}

void Walker::setDestination(sf::Vector2f *d) {
	destination = *d;
	direction = destination - position;
	direction = normalize(direction);
	canMove = true;
}

void Walker::setPath(std::vector<sf::Vector2f> p) {
	resetDestination();
	path.clear();
	path = p;
	canMove = true;
}

void Walker::resetDestination() {
	destination = position;
}

void Walker::setPosition(float x, float y) {
	position.x = x;
	position.y = y;

	circle.setPosition(position.x, position.y);
}

float Walker::getX() {
	return circle.getPosition().x;
}

float Walker::getY() {
	return circle.getPosition().y;
}

sf::Vector2f Walker::getPosition() {
	return circle.getPosition();
}

bool Walker::isCanMove() {
	return canMove;
}

float distance(sf::Vector2f p1, sf::Vector2f p2)
{
	float diffY = p1.y - p2.y;
	float diffX = p1.x - p2.x;
	return sqrt((diffY * diffY) + (diffX * diffX));
}

sf::Vector2f normalize(const sf::Vector2f& source)
{
	float length = sqrt((source.x * source.x) + (source.y * source.y));
	if (length != 0)
		return sf::Vector2f(source.x / length, source.y / length);
	else
		return source;
}

void Walker::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// apply the tileset texture
	states.texture = circle.getTexture();

	// draw the vertex array
	target.draw(circle, states);
}