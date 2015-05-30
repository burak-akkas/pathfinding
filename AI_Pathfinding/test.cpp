#include "struct/Graph.h"
#include "struct/TileMap.h"
#include "object/Walker.h"
#include "ui/TextManager.h"
#include "level/LevelManager.h"

const int frame_limit = 60;
const int screen_height = 512, screen_width = 512;
const int graph_size = 16;
const int coord_pixel = screen_height / graph_size;
const std::string window_title = "Pathfinding";
const int start_pos = 7;

// algorithm switching
enum Algorithm { A_STAR, BFS, DIJKSTRA };

int main() {
	Graph *g = new Graph(graph_size);
	TileMap map;
	std::vector<Node*> directions;

	int x = start_pos, y = start_pos, x1 = start_pos, y1 = start_pos;
	int mouse_x = 0, mouse_y = 0;

	// create the window
	sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), window_title, sf::Style::Titlebar | sf::Style::Close);

	// limit fps
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(frame_limit);

	Walker walker(sf::seconds(0.2f), true, false, x * coord_pixel, y * coord_pixel);
	std::vector<Animation> anims = walker.loadAnimations();

	// text manager
	TextManager textManager;

	// level manager
	LevelManager levelManager;

	// fps
	sf::Clock frameClock;

	// load first (default) level
	levelManager.loadLevel(g, 1, x, y);

	// create the tilemap from the level definition
	map.update(g->emptyPath());

	Algorithm selection = A_STAR;

	// run the main loop
	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// window events
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			// keyboard events
			// "esc pressed" event: close the window
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
			}
			// algorithm selection
			// press "A" key for A*
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				selection = A_STAR;
			}
			// press "S" key for BFS
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				selection = BFS;
			}
			// press "D" key for Dijkstra
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				selection = DIJKSTRA;
			}
			// press "1" to load level 1
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
				levelManager.loadLevel(g, 1, x1, y1);
				map.update(g->emptyPath());
			}
			// press "2" to load level 2
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
				levelManager.loadLevel(g, 2, x1, y1);
				map.update(g->emptyPath());
			}
			// press "3" to load level 3
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
				levelManager.loadLevel(g, 3, x1, y1);
				map.update(g->emptyPath());
			}
			// press "4" to load random level
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
				levelManager.loadRandomLevel(g, x1, y1);
				map.update(g->emptyPath());
			}

			// set algorithm display text
			textManager.setAlgorithmText(selection);

			// set level display text
			textManager.setLevelText(levelManager.getCurrentLevel());

			// mouse events
			// left click (add/remove obstacle)
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2i coord = sf::Mouse::getPosition(window);

				mouse_x = coord.x / coord_pixel;
				mouse_y = coord.y / coord_pixel;

				if(mouse_x >= graph_size || mouse_y >= graph_size) {
					mouse_x = 15;
					mouse_y = 15;				
				}

				if ((mouse_x != x1 || mouse_y != y1)) {

					if (!g->isObstacle(mouse_x, mouse_y)) {
						g->setObstacle(mouse_x, mouse_y);
					}
					else {
						g->resetObstacle(mouse_x, mouse_y);
					}
				}

				map.update(g->emptyPath());
			}
			// right click (set new destination)
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
				sf::Vector2i coord = sf::Mouse::getPosition(window);

				mouse_x = coord.x / coord_pixel;
				mouse_y = coord.y / coord_pixel;

				if(mouse_x >= graph_size || mouse_y >= graph_size) {
					mouse_x = 15;
					mouse_y = 15;				
				}


				if (walker.isCanMove() == false)
				if (!g->isObstacle(mouse_x, mouse_y)) {
					sf::Vector2i backup(x, y), backup2(x1, y1);

					x = x1;	y = y1;
					x1 = mouse_x;
					y1 = mouse_y;

					switch (selection) {
						case 0:
							if (!map.update(g->findShortestPathAstar(x, y, x1, y1, &directions))) {
								//std::cout << "No path exists!" << std::endl;
								x = backup.x; y = backup.y;
								x1 = backup2.x; y1 = backup2.y;
							}
							else {
								// set text to be drawn
								textManager.setExecText("Exec time: " + std::to_string(g->getExecTime().asMicroseconds()) + " microsec");

								// set walkers path
								walker.setPath(Util::nodeToVec(directions));
							}
							break;
						case 1:
							if (!map.update(g->findShortestPathBFS(x, y, x1, y1, &directions))) {
								//std::cout << "No path exists!" << std::endl;
								x = backup.x; y = backup.y;
								x1 = backup2.x; y1 = backup2.y;
							}
							else {
								// set text to be drawn
								textManager.setExecText("Exec time: " + std::to_string(g->getExecTime().asMicroseconds()) + " microsec");

								// set walkers path
								walker.setPath(Util::nodeToVec(directions));
							}
							break;
						case 2:
							if (!map.update(g->findShortestPathDijkstra(x, y, x1, y1, &directions))) {
								//std::cout << "No path exists!" << std::endl;
								x = backup.x; y = backup.y;
								x1 = backup2.x; y1 = backup2.y;
							}
							else {
								// set text to be drawn
								textManager.setExecText("Exec time: " + std::to_string(g->getExecTime().asMicroseconds()) + " microsec");

								// set walkers path
								walker.setPath(Util::nodeToVec(directions));
							}
							break;
						default:
							break;
					}
				}
			}
		}

		sf::Time frameTime = frameClock.restart();

		walker.play(anims.at(walker.whereToMove()));

		// clear old directions
		directions.clear();
		//directions.shrink_to_fit();

		walker.move(frameTime.asSeconds());

		if (!walker.isCanMove()) {
			walker.stop();
		}

		walker.update(frameTime);

		// clear the window with black color
		window.clear(sf::Color::Black);

		// draw everything
		window.draw(map);
		window.draw(walker);
		textManager.setFPSText("FPS: " + std::to_string(1.f / frameTime.asSeconds()));
		window.draw(textManager.getExecText());
		window.draw(textManager.getFPSText());
		window.draw(textManager.getInstructionText());
		window.draw(textManager.getAlgorithmText());
		window.draw(textManager.getLevelText());
		window.draw(textManager.getLevelInstructionText());

		// end the current frame
		window.display();
	}

	return 0;
}
