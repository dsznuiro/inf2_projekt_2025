#include "aplikacja.hpp"
#include <iostream>

Aplikacja::Aplikacja()
    : m_window(sf::VideoMode({ 800, 600 }), "Arkanoid"),
    m_menu(static_cast<float>(m_window.getSize().x), static_cast<float>(m_window.getSize().y)),
    m_currentState(GameState::Menu) //poczatkowy stan na menu
{
    m_window.setFramerateLimit(60); //liczba klatek ograniczona do 60
}

void Aplikacja::run() {
    while (m_window.isOpen()) {
        sf::Time dt = m_clock.restart(); //czas ktory uplyna od klatki

        processEvents(); // obsluga zdarzen
        update(dt);      // aktualizacja
        render();        // rysowanie grafiki
    }
}

void Aplikacja::update(sf::Time dt) {
    switch (m_currentState) {
    case GameState::Playing:
        //ruch paletki od klaiwszy
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            m_game.getPaletka().moveLeft();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            m_game.getPaletka().moveRight();
        }
        //ograniczenia zeby paletka nie wyleciala za okno
        m_game.getPaletka().clampToBounds(m_game.getWidth());

        m_game.update(dt);  //aktualizacja obiektow w grze
        if (m_game.isGameOver()) {
            m_currentState = GameState::GameOver;
        }
        else if (m_game.isGameWon()) {
            m_currentState = GameState::GameWon;
        }
        break;

    case GameState::Exiting:
        m_window.close();
        break;
    }
}

//obsluga zdarzen
void Aplikacja::processEvents() {
    sf::Event event;

    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
        }

        if (event.type == sf::Event::KeyPressed) {


            if (m_currentState == GameState::Menu) {
                if (event.key.code == sf::Keyboard::Up) { m_menu.przesunG(); }
                if (event.key.code == sf::Keyboard::Down) { m_menu.przesunD(); }

                if (event.key.code == sf::Keyboard::Enter) {
                    if (m_menu.getSelectedItem() == 0) {
                        m_game.resetGame();
                        m_currentState = GameState::Playing;
                    }
                    else if (m_menu.getSelectedItem() == 1) {

                        GameStatus loadedState;

                        if (loadedState.loadFromFile("savegame.txt")) {
                            loadedState.apply(m_game.getPaletka(), m_game.getPilka(), m_game.getBlocks(), m_game.getBlockTexture(), m_game);
                            m_currentState = GameState::Playing;
                            std::cout << "\nGra wczytana!\n";
                        }
                        else {
                            std::cerr << "\nNie udalo sie wczytac gry!\n";
                        }
                    }
                    else if (m_menu.getSelectedItem() == 2) {
                        m_currentState = GameState::Exiting;
                    }
                }
            }
            //zapis stanu gry
            if (event.key.code == sf::Keyboard::F5) {
                GameStatus snapshot;

                snapshot.capture(m_game.getPaletka(), m_game.getPilka(), m_game.getBlocks(), m_game);

                if (snapshot.saveToFile("savegame.txt")) {

                    std::cout << "\nGra zapisana!\n";
                }
                else {
                    std::cout << "\nNie udalo sie zapisac gry!\n";
                }
            }
            //powrot do menu w trakcie gry
            if (m_currentState == GameState::Playing && event.key.code == sf::Keyboard::Escape) {
                m_currentState = GameState::Menu;
            }
        }
    }

    if (m_currentState == GameState::GameOver && event.key.code == sf::Keyboard::Enter) {
        m_currentState = GameState::Exiting;
    }

    if (m_currentState == GameState::GameWon && event.key.code == sf::Keyboard::Enter) {
        m_currentState = GameState::Exiting;
    }


}

//rysowanie aktualnego stanu gry na ekranie
void Aplikacja::render() {
    m_window.clear(sf::Color::Black);

    if (m_currentState == GameState::Menu) {
        m_menu.draw(m_window);
    }
    else if (m_currentState == GameState::Playing) {
        m_game.render(m_window);
    }
    else if (m_currentState == GameState::GameOver) {
        m_game.drawGameOver(m_window);
    }
    else if (m_currentState == GameState::GameWon) {
        m_game.drawGameWon(m_window);
    }
    m_window.display();
}