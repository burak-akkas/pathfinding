#include <SFML\Graphics.hpp>

class Walker : sf::CircleShape {
private:
	float speed;
	float size;
	bool canMove;
	sf::Vector2f position, destination, direction;
	std::vector<sf::Vector2f> path;
	static sf::CircleShape circle;
public:
	Walker();
	Walker(float x, float y, float s);
	void move(float time);
	void setDestination(sf::Vector2f *d);
	void setPath(std::vector<sf::Vector2f> p);
	void resetDestination();
	void setPosition(float x, float y);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	float getX();
	float getY();

	sf::Vector2f getPosition();

	bool isCanMove();
};