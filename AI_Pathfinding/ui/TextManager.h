#ifndef TEXTMAN_INCLUDE
#define TEXTMAN_INCLUDE

#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics\Text.hpp>

class TextManager {
private:
	sf::Font font;
	std::string font_path;
	int character_size;
	sf::Color color;
	int style;

	sf::Text fps, exec, inst, alg, level, level_inst;
public:
	TextManager();
	TextManager(std::string _font_path, int _character_size, sf::Color _color, int _style);
	
	sf::Text getFPSText();
	sf::Text getExecText();
	sf::Text getInstructionText();
	sf::Text getAlgorithmText();
	sf::Text getLevelText();
	sf::Text getLevelInstructionText();
	void setExecText(std::string text);
	void setFPSText(std::string text);
	void setAlgorithmText(int select);
	void setLevelText(int curr_level);
};

#endif