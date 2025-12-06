#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.hpp"
#include "menu.hpp"

enum class GameState { Menu, Playing, Scores, Exiting };

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Arkanoid");
    sf::Clock deltaClock;
    window.setFramerateLimit(60);
    Menu menu(window.getSize().x, window.getSize().y);
    Game game; // Za³aduje bloki, paletkê itp.
    GameState currentState = GameState::Menu;

    while (window.isOpen()) {
        sf::Time dt = deltaClock.restart();
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (currentState == GameState::Menu) {
                menu.handleInput(event); 
            }
        }
        switch (currentState) {
        case GameState::Menu:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                if (menu.getSelectedItem() == 0) { // Opcja "Nowa Gra"
                    currentState = GameState::Playing;
                }
                else if (menu.getSelectedItem() == 3) { // Opcja "Wyjœcie"
                    currentState = GameState::Exiting;
                }
            }
            break;

        case GameState::Playing:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                game.m_paletka.moveLeft();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                game.m_paletka.moveRight();
            }
            game.m_paletka.clampToBounds(game.m_width);

            game.update(dt);

            // powrot do menu
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                currentState = GameState::Menu;
            }
            break;

        case GameState::Exiting:
            window.close();
            break;
        }
        window.clear();

        if (currentState == GameState::Menu) {
            menu.draw(window);
        }
        else if (currentState == GameState::Playing) {
            game.render(window);
        }

        window.display();
    }

    return 0;
}
}