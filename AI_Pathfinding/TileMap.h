#include <SFML\Graphics.hpp>
#include <string>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	bool load(const std::string& tileset, sf::Vector2u tileSize, std::vector<int> tiles, unsigned int width, unsigned int height);

private:
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};