#pragma once
#include "MainMenu.h"
#include "Level.h"

class Game
{
public:
	void StartGameLoop();
	void ShowMenu();
	void GameEnd();
	void Draw();
private:
	MainMenu menu;
	Level level;
	sf::RenderWindow window;
	bool is_dragging;

	
};

