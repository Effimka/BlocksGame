#pragma once
#include "base.h"
#include <vector>

sf::Color get_random_color();

bool intersects(const sf::RectangleShape& rect1, const sf::RectangleShape& rect2);

bool rect_contains_point(const sf::RectangleShape& rect, const VectFloat& point);

VectFloat find_closest_point(const VectFloat& mousePos, const std::vector<VectFloat>& points);

VectFloat move_lerp(const VectFloat& start, const VectFloat& end, float t);
