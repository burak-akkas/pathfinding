#include "Graph.h"
#include "TileMap.h"
#include <algorithm>

sf::Vector2f normalize(const sf::Vector2f& source);

int main() {
	Graph *g = new Graph(16);
	Graph *prev = new Graph(16);
	std::vector<int> path;
	std::vector<Node*> *temp = new std::vector<Node*>;

	int x, y, x1, y1;

	x = 8;
	y = 8;
	x1 = 8;
	y1 = 8;

	// create the window
	sf::RenderWindow window(sf::VideoMode(512, 512), "Pathfinding");

	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(20);

	// create the tilemap from the level definition
	TileMap map;
	if (!map.load("tilea3.png", sf::Vector2u(32, 32), g->emptyPath(x, y), 16, 16))
		return -1;

	// run the main loop
	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
			while (window.pollEvent(event))
			{

				// "close requested" event: we close the window
				if (event.type == sf::Event::Closed) {
					window.close();
				}

				// mouse events
				// left click (add obstacle)
				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2i coord = sf::Mouse::getPosition(window);

					if ((coord.x / 32 != x1 || coord.y / 32 != y1)) {

						if (!g->isObstacle(coord.x / 32, coord.y / 32)) {
							g->setObstacle(coord.x / 32, coord.y / 32);
						}
						else {
							g->resetObstacle(coord.x / 32, coord.y / 32);
						}

						path = g->findShortestPathAstar(x, y, x1, y1, temp);

						if (path.size() != 0) {
							if (!map.load("tilea3.png", sf::Vector2u(32, 32), path, 16, 16))
								std::cout << "Map can not be loaded!" << std::endl;
						}
						else {
							std::cout << "No path exists between source and destination coordinates!" << std::endl;

							g->resetObstacle(coord.x / 32, coord.y / 32);
						}

					}
				}
				// right click (set new destination)
				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
					sf::Vector2i coord = sf::Mouse::getPosition(window);

					if (!g->isObstacle(coord.x / 32, coord.y / 32)) {

						x = x1;
						y = y1;

						x1 = coord.x / 32;
						y1 = coord.y / 32;

						
						path = g->findShortestPathAstar(x, y, x1, y1, temp);

						if (path.size() != 0) {
							if (!map.load("tilea3.png", sf::Vector2u(32, 32), path, 16, 16))
								std::cout << "Map can not be loaded!" << std::endl;
						}
						else {
							std::cout << "No path exists between source and destination coordinates!" << std::endl;
						}
					}
					
					std::reverse(temp->begin(), temp->end());

					for (size_t i = 0; i < temp->size(); i++) {
						if (i % 16 == 0) { std::cout << std::endl; }
						std::cout << "(" << temp->at(i)->getX() << ", " << temp->at(i)->getY() << ")";
					}
							
				}
			}


			temp->clear();
			temp->shrink_to_fit();

			// clear the window with black color
			window.clear(sf::Color::Black);

			// draw everything here...
			// window.draw(...);
			window.draw(map);
			//window.draw(playerImage);

			// end the current frame
			window.display();
		}

	return 0;
}

sf::Vector2f normalize(const sf::Vector2f& source)
{
	float length = sqrt((source.x * source.x) + (source.y * source.y));
	if (length != 0)
		return sf::Vector2f(source.x / length, source.y / length);
	else
		return source;
}