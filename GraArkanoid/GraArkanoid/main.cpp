#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.hpp"
#include "menu.hpp"
#include "gamestate.hpp"

enum class GameState { Menu, Playing, Scores, Exiting, GameOver, GameWon };

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
                    if (event.key.code == sf::Keyboard::Up) { menu.przesunG(); }
                    if (event.key.code == sf::Keyboard::Down) { menu.przesunD(); }

                    if (event.key.code == sf::Keyboard::Enter) {
                        if (menu.getSelectedItem() == 0) {
                            game.resetGame();
                            currentState = GameState::Playing;
                        }
                        else if (menu.getSelectedItem() == 1) {

                            GameStatus loadedState;

                            if (loadedState.loadFromFile("savegame.txt")) {
                                loadedState.apply(game.getPaletka(), game.getPilka(), game.getBlocks(), game.getBlockTexture(), game );
                                currentState = GameState::Playing;
                                std::cout << "\nGra wczytana!\n";
                            }
                            else {
                                std::cerr << "\nNie udalo sie wczytac gry!\n";
                            }
                        }
                        else if (menu.getSelectedItem() == 2) {
                            currentState = GameState::Exiting;
                        }
                    }
                }

                if (event.key.code == sf::Keyboard::F5) {
                    GameStatus snapshot;

                    snapshot.capture(game.getPaletka(), game.getPilka(), game.getBlocks(), game);

                    if (snapshot.saveToFile("savegame.txt")) {

                        std::cout << "\nGra zapisana!\n";
                    }
                    else {
                        std::cout << "\nNie udalo sie zapisac gry!\n";
                    }
                }

                if (currentState == GameState::Playing && event.key.code == sf::Keyboard::Escape) {
                    currentState = GameState::Menu;
                }
            }
        }

        if (currentState == GameState::GameOver && event.key.code == sf::Keyboard::Enter) {
            currentState = GameState::Exiting;
        }

        if (currentState == GameState::GameWon && event.key.code == sf::Keyboard::Enter) {
            currentState = GameState::Exiting;
        }

        if (currentState == GameState::Playing && event.key.code == sf::Keyboard::Escape) {
            currentState = GameState::Menu;
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
            if (game.isGameOver()) {
                currentState = GameState::GameOver;
            }
            else if (game.isGameWon()) {
                currentState = GameState::GameWon;
            }
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
        else if (currentState == GameState::GameOver) {
            game.drawGameOver(window);
        }
        else if (currentState == GameState::GameWon) {
            game.drawGameWon(window);
        }
        window.display();
    }

    return 0;
}