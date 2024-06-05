#include "MainMenu.h"

void MainMenu::initMenu(const sf::Vector2u& screen_size)
{
	active = true;

	float posX = screen_size.x / 2.f - (size_btn.x / 2.f);
	float stepY = screen_size.y / 4.f;
	font.loadFromFile("arial_bolditalicmt.ttf");
	for (int i = 0; i < 3; ++i)
	{
		btns.push_back(sf::RectangleShape(size_btn));
		btns[i].setPosition(VectFloat(posX, i * stepY + stepY));
		btns_text.push_back(sf::Text(std::to_string(i + 1), font));
		btns_text[i].setPosition(posX + size_btn.x / 2, i * stepY + stepY);
		btns_text[i].setFillColor(sf::Color::Black);
	}

	btns[0].setFillColor(sf::Color::Green);
	btns[1].setFillColor(sf::Color::Yellow);
	btns[2].setFillColor(sf::Color::Red);
}

std::string MainMenu::choose_level(const sf::Vector2f& mouse_world_Pos)
{
	std::string filename = "";
	if (active)
	{
		
		if (rect_contains_point(btns[0], mouse_world_Pos)) {
			btns[0].setFillColor(sf::Color::Blue);
			filename = "level1.txt";
		}
		else if (rect_contains_point(btns[1], mouse_world_Pos)) {
			btns[1].setFillColor(sf::Color::Blue);
			filename = "level2.txt";
		}
		else if (rect_contains_point(btns[2], mouse_world_Pos)) {
			btns[2].setFillColor(sf::Color::Blue);
			filename = "level3.txt";
		}

		if (filename != "")
			active = false;

	}

	return filename;
}

void MainMenu::draw(sf::RenderWindow& win)
{
	if (active) {
		for (int i = 0; i < btns.size(); ++i) {
			win.draw(btns[i]);
			win.draw(btns_text[i]);
		}
	}
}
