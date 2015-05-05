#include "Graph.h"
#include "TileMap.h"

int main() {
	Graph *g = new Graph(16);

	/*g->setObstacle(1, 1);
	g->setObstacle(1, 2);
	g->setObstacle(1, 3);
	g->setObstacle(1, 4);
	g->setObstacle(1, 5);
	g-
	>setObstacle(1, 6);
	g->setObstacle(1, 0);
	g->setObstacle(5, 6);
	g->setObstacle(3, 2);
	g->setObstacle(6, 1);
	g->setObstacle(6, 3);
	g->setObstacle(6, 4);
	g->setObstacle(5, 4);
	g->setObstacle(5, 3);
	*/
	srand(time(NULL));

	for (int i = 0; i < 50; i++) {
		g->setObstacle(rand() % 15 + 1, rand() % 15 + 1);
	}

	int x, y, x1, y1;

	std::cout << "Enter start x, y: ";
	std::cin >> x >> y;

	std::cout << "Enter end x, y: ";
	std::cin >> x1 >> y1;

	//g->printGraph();

	// create the window
	sf::RenderWindow window(sf::VideoMode(512, 512), "TileMap");

	// create the tilemap from the level definition
	TileMap map;
	if (!map.load("tilea3.png", sf::Vector2u(32, 32), g->findShortestPathAstar(y, x, y1, x1), 16, 16))
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
			if (event.type == sf::Event::Closed)
				window.close();
			// mouse events
			if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2i coord = sf::Mouse::getPosition(window);

				g->setObstacle(coord.x % 16, coord.y % 16);
				std::cout << coord.x << "," << coord.y << std::endl;
				
				window.draw(map);
			}
		}

		// clear the window with black color
		window.clear(sf::Color::Black);

		// draw everything here...
		// window.draw(...);
		window.draw(map);

		// end the current frame
		window.display();
	}


	std::cin.get();

	return 0;
}