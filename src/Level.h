#pragma once
#include "Collaiders.h"
#include "ConfigParser.h"

class Level
{
public:
	void init(const std::string& level_name, const sf::Vector2u& screen_size);
	bool is_mouse_in_rect(const sf::Vector2f& mouse_world_Pos);
	void rect_overlap(bool& dragging);
	void move_selected_rect(const sf::Vector2f& mouse_world_Posn, bool& dragging);
	bool coincidence_win_rects();

	std::vector<sf::RectangleShape>& get_rects();
	std::vector<sf::RectangleShape>& get_conecteds();
	std::vector<sf::RectangleShape>& get_win_rects();


private:

	bool level_active = false;
	LevelConfig config;
	std::vector<sf::RectangleShape> rects;
	std::vector<sf::RectangleShape> conecteds;
	std::vector<sf::RectangleShape> win_rects;

	VectFloat oldRectPose;
	int id_dragging_rect = -1;
	

};

