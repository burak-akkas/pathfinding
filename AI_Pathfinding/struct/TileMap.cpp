#include "TileMap.h"

TileMap::TileMap() {
	tile_path = "./graphics/tilea2.png";
	// load the tileset texture
	m_tileset.loadFromFile(tile_path);
	tileSize.x = 32; tileSize.y = 32;
	width = 16; height = 16;
}

bool TileMap::load(std::vector<int> tiles)
{
	// resize the vertex array to fit the level size
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(width * height * 4);

	// populate the vertex array, with one quad per tile
	for (unsigned int i = 0; i < width; ++i)
	for (unsigned int j = 0; j < height; ++j)
	{
		// get the current tile number
		int tileNumber = tiles[i + j * width];

		// find its position in the tileset texture
		int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
		int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

		// get a pointer to the current tile's quad
		sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

		// define its 4 corners
		quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
		quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
		quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
		quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

		// define its 4 texture coordinates
		quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
		quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
		quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
		quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
	}

	return true;
}

bool TileMap::update(std::vector<int> path) {
	if (path.size() != 0) {
		if (!load(path)) {
			return false;
		}
		return true;
	}
	else {
		return false;
	}
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// apply the tileset texture
	states.texture = &m_tileset;

	// draw the vertex array
	target.draw(m_vertices, states);
}