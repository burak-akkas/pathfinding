#pragma once
#include "struct\Graph.h"
#include "struct\TileMap.h"
#include "object\Walker.h"
#include <algorithm>

const float fixed_time = 0.08f;
const int frame_limit = 20;
const int screen_height = 512, screen_width = 512;
const int graph_size = 16;
const int coord_pixel = screen_height / graph_size;
const std::string window_title = "Pathfinding";

int main() {
	Graph *g = new Graph(graph_size);
	TileMap map;
	std::vector<int> path;
	std::vector<Node*> *directions = new std::vector<Node*>;
	Walker *walker = new Walker(8, 8);

	int x = 8, y = 8, x1 = 8, y1 = 8;

	// create the window
	sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), window_title);

	// limit fps
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(frame_limit);
	
	// create the tilemap from the level definition
	map.update(g->emptyPath(x, y));

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

				if ((coord.x / coord_pixel != x1 || coord.y / coord_pixel != y1)) {

					if (!g->isObstacle(coord.x / coord_pixel, coord.y / coord_pixel)) {
						g->setObstacle(coord.x / coord_pixel, coord.y / coord_pixel);
					}
					else {
						g->resetObstacle(coord.x / coord_pixel, coord.y / coord_pixel);
					}

					path = g->findShortestPathAstar(x, y, x1, y1, directions);

					if (!map.update(path)) {
						std::cout << "No path exists!" << std::endl;
						g->resetObstacle(coord.x / coord_pixel, coord.y / coord_pixel);
					}

				}
			}
			// right click (set new destination)
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
				sf::Vector2i coord = sf::Mouse::getPosition(window);
				if (!g->isObstacle(coord.x / coord_pixel, coord.y / coord_pixel)) {

					x = x1;	y = y1;
					x1 = coord.x / coord_pixel;
					y1 = coord.y / coord_pixel;

					path = g->findShortestPathAstar(x, y, x1, y1, directions);
					walker->setPath(Util::nodeToVec(*directions));

					if (!map.update(path)) std::cout << "No path exists!" << std::endl;
				}
					
				std::reverse(directions->begin(), directions->end());

				for (size_t i = 0; i < directions->size(); i++) {
					if (i % 16 == 0) { std::cout << std::endl; }
					std::cout << "(" << directions->at(i)->getX() << ", " << directions->at(i)->getY() << ")";
				}				
			}
		}

		// clear old directions
		directions->clear();
		directions->shrink_to_fit();
		
		// move the walker 
		walker->move(fixed_time);

		// clear the window with black color
		window.clear(sf::Color::Black);

		// draw everything here...
		window.draw(map);
		walker->draw(window, sf::RenderStates::Default);

		// end the current frame
		window.display();
	}

	return 0;
}