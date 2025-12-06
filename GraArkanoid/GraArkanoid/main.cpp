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
    Menu menu(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
    Game game;
    GameState currentState = GameState::Menu;

    while (window.isOpen()) {
        sf::Time dt = deltaClock.restart();
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (currentState == GameState::Menu) {
                    if (event.key.code == sf::Keyboard::Up) {
                        menu.przesunG();
                    }
                    if (event.key.code == sf::Keyboard::Down) {
                        menu.przesunD();
                    }

                    if (event.key.code == sf::Keyboard::Enter) {
                        if (menu.getSelectedItem() == 0) {
                            currentState = GameState::Playing;
                        }
                        else if (menu.getSelectedItem() == 2) {
                            currentState = GameState::Exiting;
                        }
                    }
                }
                else if (currentState == GameState::Playing && event.key.code == sf::Keyboard::Escape) {
                    currentState = GameState::Menu;
                }
            }
        } 

        switch (currentState) {
        case GameState::Playing:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                game.getPaletka().moveLeft();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                game.getPaletka().moveRight();
            }
            game.getPaletka().clampToBounds(game.getWidth());

            game.update(dt);
            break;

        case GameState::Exiting:
            window.close();
            break;
        }


        window.clear(sf::Color::Black);

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