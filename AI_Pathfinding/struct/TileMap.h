#ifndef TILEMAP_INCLUDE
#define TILEMAP_INCLUDE

#include <SFML/Graphics.hpp>
#include <string>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	TileMap();
	bool load(std::vector<int> tiles);
	bool update(std::vector<int> path);
private:
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
	std::string tile_path;
	sf::Vector2u tile_size;
	unsigned int width;
	unsigned int height;
	sf::Vector2u tileSize;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
