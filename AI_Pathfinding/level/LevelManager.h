#ifndef LEVELMAN_INCLUDE
#define LEVELMAN_INCLUDE

#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include "../struct/Graph.h"

class LevelManager {
	private:
		int level_count;
		int current_level;
		std::vector<std::string> level_paths;

	public:
		LevelManager();
		
		int getLevelCount();
		int getCurrentLevel();
		void loadLevel(Graph *g, int level, int curr_x, int curr_y);
		void loadRandomLevel(Graph *g, int curr_x, int curr_y);
};

#endif
