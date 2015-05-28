#pragma once
#include "struct\Graph.h"
#include "struct\TileMap.h"
#include "object\Walker.h"
#include <algorithm>

const int frame_limit = 60;
const int screen_height = 512, screen_width = 512;
const int graph_size = 16;
const int coord_pixel = screen_height / graph_size;
const std::string window_title = "Pathfinding";

int main() {
	Graph *g = new Graph(graph_size);
	TileMap map;
	std::vector<Node*> directions;

	int x = 8, y = 8, x1 = 8, y1 = 8;
	int mouse_x = 0, mouse_y = 0;

	// create the window
	sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), window_title);

	// limit fps
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(frame_limit);

	Walker walker(sf::seconds(0.2f), true, false, x * coord_pixel, y * coord_pixel);
	std::vector<Animation> anims = walker.loadAnimations();

	// fps
	sf::Clock frameClock;

	// algorithm execute time
	sf::Clock execClock;
	bool exec_changed = false;

	// text test
	sf::Font font;
	font.loadFromFile("Anke.ttf");

	sf::Text fps_text, exec_text;
	fps_text.setFont(font);
	fps_text.setString("FPS: ");
	fps_text.setCharacterSize(14);
	fps_text.setColor(sf::Color::White);
	fps_text.setStyle(sf::Text::Bold);
	fps_text.setPosition(screen_width - 120, 10);

	exec_text = fps_text;
	exec_text.setPosition(10, 10);
	exec_text.setString("");
	// #text test

	// create the tilemap from the level definition
	map.update(g->emptyPath());

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
			// "esc pressed" event: close the window
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
			}
			// mouse events
			// left click (add/remove obstacle)
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2i coord = sf::Mouse::getPosition(window);

				mouse_x = coord.x / coord_pixel;
				mouse_y = coord.y / coord_pixel;

				if ((mouse_x != x1 || mouse_y != y1)) {

					if (!g->isObstacle(mouse_x, mouse_y)) {
						g->setObstacle(mouse_x, mouse_y);
					}
					else {
						g->resetObstacle(mouse_x, mouse_y);
					}
				}

				if (!map.update(g->emptyPath())) {

				}
			}
			// right click (set new destination)
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
				sf::Vector2i coord = sf::Mouse::getPosition(window);

				mouse_x = coord.x / coord_pixel;
				mouse_y = coord.y / coord_pixel;

				if (walker.isCanMove() == false)
				if (!g->isObstacle(mouse_x, mouse_y)) {
					sf::Vector2i backup(x, y), backup2(x1, y1);

					x = x1;	y = y1;
					x1 = mouse_x;
					y1 = mouse_y;

					// restart algorithm execution clock
					execClock.restart();
					if (!map.update(g->findShortestPathBFS(x, y, x1, y1, &directions))) {
					//if (!map.update(g->findShortestPathDijkstra(x, y, x1, y1, &directions))) {
					//if (!map.update(g->findShortestPathAstar(x, y, x1, y1, &directions))) {
						std::cout << "No path exists!" << std::endl;
						x = backup.x; y = backup.y;
						x1 = backup2.x; y1 = backup2.y;
					}
					else {
						// get algorithm execution time
						sf::Time execTime = execClock.restart();

						// set text to be drawn
						exec_text.setString("Exec time: " + std::to_string(execTime.asMilliseconds()) + " ms");

						// set walkers path
						walker.setPath(Util::nodeToVec(directions));
					}
				}
			}
		}

		sf::Time frameTime = frameClock.restart();

		walker.play(anims.at(walker.whereToMove()));

		// clear old directions
		directions.clear();
		directions.shrink_to_fit();

		walker.move(frameTime.asSeconds());

		if (!walker.isCanMove()) {
			walker.stop();
		}

		walker.update(frameTime);

		// clear the window with black color
		window.clear(sf::Color::Black);

		// draw everything here...
		window.draw(map);
		window.draw(walker);

		// text test
		fps_text.setString("FPS: " + std::to_string(1.f / frameTime.asSeconds()));
		window.draw(fps_text);
		window.draw(exec_text);

		// #text test

		// end the current frame
		window.display();
	}

	return 0;
}