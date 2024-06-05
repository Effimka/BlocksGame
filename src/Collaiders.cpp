#include "Collaiders.h"


sf::Color get_random_color()
{
    int r = rand() % 255;
    int g = rand() % 255;
    int b = rand() % 255;
    return sf::Color(r, g, b);
}

bool intersects(const sf::RectangleShape& rect1, const sf::RectangleShape& rect2)
{
    VectFloat pos_rect1 = rect1.getPosition();
    VectFloat size_rect1 = rect1.getSize();
    VectFloat center_rect1(pos_rect1.x + size_rect1.x / 2, pos_rect1.y + size_rect1.y / 2);
    return rect2.getGlobalBounds().contains(center_rect1);
}

bool rect_contains_point(const sf::RectangleShape& rect, const VectFloat& point)
{
    return rect.getGlobalBounds().contains(point);
}



VectFloat find_closest_point(const VectFloat& mousePos, const std::vector<VectFloat>& points) {
    float minDistance = std::numeric_limits<float>::max();
    sf::Vector2f closestPoint;

    for (const auto& point : points) {
        float distance = std::hypot(mousePos.x - point.x, mousePos.y - point.y);
        if (distance < minDistance) {
            minDistance = distance;
            closestPoint = point;
        }
    }

    return closestPoint;
}

VectFloat move_lerp(const VectFloat& start, const VectFloat& end, float t)
{
    return (1 - t) * start + t * end;
}


