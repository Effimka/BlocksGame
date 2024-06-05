#include "Game.h"

void Game::StartGameLoop()
{
    window.create(sf::VideoMode(800, 600), "Cupboards");
    srand(time(0));
    ShowMenu();
    std::string level_name;
    is_dragging = false;
    while (window.isOpen())
    {
        sf::Event event;
        sf::Vector2f worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
            
            if (event.type == sf::Event::EventType::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

                

                level_name = menu.choose_level(worldPos);
                if (level_name != "")
                    level.init(level_name, window.getSize());

                if (!is_dragging && level.is_mouse_in_rect(worldPos)) {
                    is_dragging = true;
                }
            }

            if (event.type == sf::Event::EventType::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                is_dragging = false;



        }

        if(is_dragging)
            level.move_selected_rect(worldPos, is_dragging);

        window.clear(sf::Color::White);
        Draw();
        window.display();

        GameEnd();
    }
}

void Game::ShowMenu()
{
    menu.initMenu(window.getSize());
}

void Game::GameEnd()
{
    if (level.coincidence_win_rects())
    {
        is_dragging = false;
        ShowMenu();
    }
}

void Game::Draw()
{
    menu.draw(window);
    const std::vector<sf::RectangleShape>& rects = level.get_rects();
    const std::vector<sf::RectangleShape>& conecteds = level.get_conecteds();
    const std::vector<sf::RectangleShape>& win_rects = level.get_win_rects();

   

    for (int i = 0; i < conecteds.size(); ++i)
        window.draw(conecteds[i]);

    for (int i = 0; i < conecteds.size(); ++i) {
        sf::RectangleShape rect = conecteds[i];
        VectFloat pos = rect.getPosition();
        sf::Vector2u screen(window.getSize().x * 0.6f, window.getSize().y * 0.5f);
        rect.setSize(VectFloat(rect.getSize().x / 2, rect.getSize().y / 2));
        rect.setPosition(pos.x / 2 + screen.x, pos.y / 2 + screen.y);
        window.draw(rect);
    }

    for (int i = 0; i < win_rects.size(); ++i)
        window.draw(win_rects[i]);

    for (int i = 0; i < rects.size(); ++i)
        window.draw(rects[i]);

    
}



