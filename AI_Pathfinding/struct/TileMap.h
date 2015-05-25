#ifndef TILEMAP_INCLUDE
#define TILEMAP_INCLUDE

#include <SFML\Graphics.hpp>
#include <string>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	TileMap();
	bool load(const std::string& tileset, sf::Vector2u tileSize, std::vector<int> tiles, unsigned int width, unsigned int height);
	bool update(std::vector<int> path);
private:
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
	std::string tile_path;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif