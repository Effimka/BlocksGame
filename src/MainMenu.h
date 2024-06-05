#pragma once
#include "Collaiders.h"

class MainMenu
{
public:
	void initMenu(const sf::Vector2u& screen_size);
	std::string choose_level(const sf::Vector2f& mouse_world_Pos);
	void draw(sf::RenderWindow& win);
private:
	bool active = false;
	std::vector<sf::RectangleShape> btns;
	std::vector<sf::Text> btns_text;
	sf::Font font;
	VectFloat size_btn = VectFloat(150, 50);
};

