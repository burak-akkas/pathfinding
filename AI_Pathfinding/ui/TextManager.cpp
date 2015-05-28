#include "TextManager.h"

TextManager::TextManager() {
	font_path = "ui/font/gamer.ttf";
	font.loadFromFile(font_path);

	fps.setFont(font);
	fps.setString("FPS: ");
	fps.setCharacterSize(14);
	fps.setColor(sf::Color::Red);
	fps.setStyle(sf::Text::Bold);
	fps.setPosition(512 - 135, 10);

	exec.setFont(font);
	exec.setString("");
	exec.setCharacterSize(14);
	exec.setColor(sf::Color::White);
	exec.setStyle(sf::Text::Bold);
	exec.setPosition(10, 35);

	inst.setFont(font);
	inst.setString("# Press Key 'A' for A-star, Key 'S' for BFS, Key 'D' for Dijkstra !");
	inst.setCharacterSize(13);
	inst.setColor(sf::Color::White);
	inst.setStyle(sf::Text::Bold);
	inst.setPosition(10, 512 - 20 );

	alg.setFont(font);
	alg.setString("");
	alg.setCharacterSize(14);
	alg.setColor(sf::Color::White);
	alg.setStyle(sf::Text::Bold);
	alg.setPosition(10, 10);
}

TextManager::TextManager(std::string _font_path, int _character_size, sf::Color _color, int _style) : font_path(_font_path), character_size(_character_size), color(_color), style(_style) {
	font.loadFromFile(font_path);

	fps.setFont(font);
	fps.setString("FPS: ");
	fps.setCharacterSize(character_size);
	fps.setColor(color);
	fps.setStyle(style);
	fps.setPosition(512 - 120, 10);

	exec.setFont(font);
	exec.setString("");
	exec.setCharacterSize(character_size);
	exec.setColor(color);
	exec.setStyle(style);
	exec.setPosition(10, 35);

	inst.setFont(font);
	inst.setString("# Press Key 'A' for A-star, Key 'S' for BFS, Key 'D' for Dijkstra !");
	inst.setCharacterSize(character_size);
	inst.setColor(color);
	inst.setStyle(style);
	inst.setPosition(25, 512 - 25);

	alg.setFont(font);
	alg.setString("");
	alg.setCharacterSize(character_size);
	alg.setColor(color);
	alg.setStyle(style);
	alg.setPosition(10, 10);
}

sf::Text TextManager::getExecText() {
	return exec;
}

sf::Text TextManager::getFPSText() {
	return fps;
}

sf::Text TextManager::getInstructionText() {
	return inst;
}

sf::Text TextManager::getAlgorithmText() {
	return alg;
}

void TextManager::setExecText(std::string text) {
	exec.setString(text);
}

void TextManager::setFPSText(std::string text) {
	fps.setString(text);
}

void TextManager::setAlgorithmText(int select) {
	switch (select) {
		case 0:
			alg.setString("Algorithm: A-star");
			break;
		case 1:
			alg.setString("Algorithm: BFS");
			break;
		case 2:
			alg.setString("Algorithm: Dijkstra");
			break;
		default:
			alg.setString("Algorithm: A-star");
	}
}