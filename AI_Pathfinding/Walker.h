#include <SFML\Graphics.hpp>

class Walker : sf::Sprite {
private:
	float speed;
	bool canMove;
	sf::Vector2f position, destination, direction;
	std::vector<sf::Vector2f> path;

	sf::Vector2i source;
	sf::Sprite sprite;
	sf::Texture texture;
public:
	Walker();
	Walker(float x, float y);
	void load();
	void move(float time);
	void setDestination(sf::Vector2f *d);
	void setPath(std::vector<sf::Vector2f> p);
	void resetDestination();
	void setPosition(float x, float y);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	float getX();
	float getY();
	sf::Sprite getSprite();
	sf::Vector2f getPosition();
	bool isCanMove();
};
