#include "LevelManager.h"

LevelManager::LevelManager() {
	level_count = 3;
	current_level = 1;
	
	level_paths.push_back(".//level//levels//level1.txt");
	level_paths.push_back(".//level//levels//level2.txt");
	level_paths.push_back(".//level//levels//level3.txt");
}

int LevelManager::getLevelCount() {
	return level_count;
}

int LevelManager::getCurrentLevel() {
	return current_level;
}

void LevelManager::loadLevel(Graph *g, int level, int curr_x, int curr_y) {
	if (level <= level_paths.size()) {
		std::fstream file(level_paths.at(level - 1).c_str(), std::ios_base::in);
		
		// reset current level
		int size = g->getSize();
		for (int j = 0; j < size; j++) {
			for (int i = 0; i < size; i++) {
				g->resetObstacle(i, j);
			}
		}

		// set new level
		int a;
		for (int j = 0; j < size; j++) {
			for (int i = 0; i < size; i++) {
				if (file >> a) {
					if (a == 1) {
						if (i != curr_x || j != curr_y) {
							g->setObstacle(i, j);
						}
					}
				}
			}
			if (!file) {
				std::cout << "file not found!" << std::endl;
				break;
			}
		}

		current_level = level;
	}
	else {
		std::cout << "level not found!";
	}
	
}

void LevelManager::loadRandomLevel(Graph *g, int curr_x, int curr_y) {
	srand(time(NULL));

	int size = g->getSize();

	// reset current level
	for (int j = 0; j < size; j++) {
		for (int i = 0; i < size; i++) {
			g->resetObstacle(i, j);
		}
	}

	// set new random level
	for (int i = 0; i < size; i++) {
		for (int j = 2; j < size - 2; j++) {
			if (i != curr_x || j != curr_y) {
				if (rand() % 2 != 0) {
					g->setObstacle(i, j);
				}
			}
		}
	}

	current_level = 4;
}
