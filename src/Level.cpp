#include "Level.h"


void Level::init(const std::string& level_name, const sf::Vector2u& screen_size)
{
	
	level_active = true;

	config = ConfigParser().make_config_level(level_name);


	VectFloat rect_size = VectFloat(30, 30);
	rects.resize(config.chips_count);

	for (int i = 0; i < config.chips_count; ++i) {
		rects[i] = sf::RectangleShape(rect_size);
		rects[i].setPosition(config.coord_place[config.start_place_chips[i]]);
		rects[i].setFillColor(get_random_color());
	}


	for (int i = 0; i < config.connections_count; ++i) {
		VectInt pair(config.connections[i].x, config.connections[i].y);

		VectFloat point1 = config.coord_place[pair.x];
		VectFloat point2 = config.coord_place[pair.y];
		VectFloat size;


		size.x = abs(point1.x - point2.x);
		size.y = abs(point1.y - point2.y);

		point1.x += rect_size.x / 3.f;
		point1.y += rect_size.x / 3.f;

		if (size.x >= -0.01 && size.x <= 0.01)
			size.x = rect_size.x / 3.f;

		if (size.y >= -0.01 && size.y <= 0.01)
			size.y = rect_size.x / 3.f;

		conecteds.push_back(sf::RectangleShape(size));
		conecteds[i].setPosition(point1);
		conecteds[i].setFillColor(sf::Color(169, 169, 169));
	}

	sf::Vector2u screen(screen_size.x * 0.6f, screen_size.y * 0.5f);

	for (int i = 0; i < config.chips_count; ++i) {
		sf::RectangleShape temp = rects[i];
		VectFloat pos = config.coord_place[config.win_place_chips[i]];
		temp.setSize(temp.getSize() / 2.f);
		temp.setPosition(pos.x / 2 + screen.x, pos.y / 2 + screen.y);
		win_rects.push_back(sf::RectangleShape(std::move(temp)));

	}
}

bool Level::is_mouse_in_rect(const sf::Vector2f& mouse_world_Pos)
{
	if (!level_active)
		return false;

	for (int i = 0; i < rects.size(); ++i)
	{
		if (rect_contains_point(rects[i], mouse_world_Pos)) {
			oldRectPose = rects[i].getPosition();
			id_dragging_rect = i;
			return true;
		}
	}
	return false;
}

void Level::rect_overlap(bool& dragging)
{
	if (id_dragging_rect == -1)
		return;

	bool is_collision = false;

	for (int i = 0; i < rects.size(); ++i) {
		if (i == id_dragging_rect)
			continue;
		if (intersects(rects[id_dragging_rect], rects[i])) {
			rects[id_dragging_rect].setPosition(oldRectPose);
			is_collision = true;
			break;
		}
	}
	
	if (is_collision) {
		id_dragging_rect == -1;
		dragging = false;
	}
}

void Level::move_selected_rect(const sf::Vector2f& mouse_world_Pos, bool& dragging)
{
	if (id_dragging_rect == -1)
		return;
	auto target = find_closest_point(mouse_world_Pos, config.coord_place);
	VectFloat currentPos = rects[id_dragging_rect].getPosition();
	currentPos = move_lerp(currentPos, target, 0.01f);
	rects[id_dragging_rect].setPosition(currentPos);
	rect_overlap(dragging);
}

bool Level::coincidence_win_rects()
{
	if (!level_active)
		return false;

	bool is_win_point = false;
	for (int i = 0; i < win_rects.size(); ++i)
	{
		for (int j = 0; j < win_rects.size(); ++j)
		{
			sf::FloatRect temp(config.coord_place[config.win_place_chips[i]], VectFloat(10.f, 10.f));
			if (rects[j].getGlobalBounds().intersects(temp))
				if (win_rects[i].getFillColor() == rects[j].getFillColor())
					is_win_point = true;

		}
		if (!is_win_point)
			return false;
		else
			is_win_point = false;
	}

	rects.clear();
	conecteds.clear();
	win_rects.clear();
	level_active = false;
	return true;
}

std::vector<sf::RectangleShape>& Level::get_rects()
{
	return rects;
}

std::vector<sf::RectangleShape>& Level::get_conecteds()
{
	return conecteds;
}

std::vector<sf::RectangleShape>& Level::get_win_rects()
{
	return win_rects;
}
