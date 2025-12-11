#pragma once

#include <SFML/Graphics.hpp>
#include "game.hpp"
#include "menu.hpp"
#include "gamestate.hpp"

enum class GameState { Menu, Playing, Scores, Exiting, GameOver, GameWon };

class Aplikacja {
private:
    sf::RenderWindow m_window;
    sf::Clock m_clock;

    Menu m_menu;
    Game m_game;
    GameState m_currentState;

    void processEvents(); //zdarzenia wejsciowe uzytkownika
    void update(sf::Time dt); // aktualizuje gre
    void render();  //rysowanie obrazu

public:
    Aplikacja();
    void run();
};