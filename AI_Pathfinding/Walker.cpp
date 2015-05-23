#include "Walker.h"

Walker::Walker() {
	speed = 100.f;

	position.x = 8.f * 32;
	position.y = 8.f * 32 - 20;

	// sprite prop
	load();
	sprite.setPosition(position);

	canMove = false;
}

Walker::Walker(float x, float y) {
	speed = 100.f;

	position.x = x * 32;
	position.y = y * 32 - 20;

	// sprite prop
	load();
	sprite.setPosition(position);

	canMove = false;
}

void Walker::load() {
	if (texture.loadFromFile("Player.png", sf::IntRect(32, 48, 32, 48))) {
		sprite.setTexture(texture);
	}
}

void Walker::move(float time) {
	if (canMove == true)
	{
		if (Util::distance(position, destination) > 5.f)
		{
			position += direction * speed * time;
			sprite.setPosition(position.x, position.y - 20);
		}
		else if (path.size() > 0)
		{
			setDestination(&path.back());
			path.pop_back();
		}
		else
		{
			canMove = false;
		}
	}
}

void Walker::setDestination(sf::Vector2f *d) {
	destination = *d;
	direction = destination - position;
	direction = Util::normalize(direction);
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

	sprite.setPosition(position.x, position.y);
}

float Walker::getX() {
	return sprite.getPosition().x;
}

float Walker::getY() {
	return sprite.getPosition().y;
}

sf::Vector2f Walker::getPosition() {
	return sprite.getPosition();
}

sf::Sprite Walker::getSprite() {
	return sprite;
}

bool Walker::isCanMove() {
	return canMove;
}

void Walker::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// apply the tileset texture
	states.texture = sprite.getTexture();

	// draw the vertex array
	target.draw(sprite, states);
}