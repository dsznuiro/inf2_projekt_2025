#include "game.hpp"
#include <iostream>

//konstruktor klasy game
Game::Game()
    : m_width(800), m_height(600), m_frame(0), m_pilka(320, 280, 4, 3, 8) { 
    //konfiguracja blokow
    const int ILOSC_KOLUMN = 6;
    const int ILOSC_WIERSZY = 7;
    float ROZMIAR_BLOKU_X = (m_width - (ILOSC_KOLUMN - 1) * 2.f) / ILOSC_KOLUMN;
    float ROZMIAR_BLOKU_Y = 25.f;

    //ladowanie tekstur
    if (!m_blockTexture.loadFromFile("bloki3stany.png")) {
        std::cerr << "Blad ladowania tekstury.\n";
    }

    if (!m_backgroundTexture.loadFromFile("tlo.png")) {
        std::cerr << "Blad ladowania tekstury tla!.\n";
    }

    m_background.setTexture(m_backgroundTexture);

    if (!m_paddleTexture.loadFromFile("paletka.png")) {
        std::cerr << "Blad ladowania tekstury paletki!\n";
    }
    //tworzenie paletki po wczytaniu jej tekstury
    m_paletka = Paletka(320, 440, 100, 20, 8, m_paddleTexture);

    if (!m_font.loadFromFile("arial.ttf")) {
        std::cerr << "Blad ladowania czcionki!'.\n";
    }

    //teskt do wyniku
    m_score = 0;
    m_scoreText.setFont(m_font);
    m_scoreText.setCharacterSize(24);
    m_scoreText.setFillColor(sf::Color::White);
    m_scoreText.setPosition(10.f, m_height - 40.f);

    //poczatkowe bloki im nizej sa bloki tym wiecej maja zyc
    for (int y = 0; y < ILOSC_WIERSZY; y++) {
        for (int x = 0; x < ILOSC_KOLUMN; x++) {
            float posX = x * (ROZMIAR_BLOKU_X + 2.f);
            float posY = y * (ROZMIAR_BLOKU_Y + 2.f) + 60.f;
            int zycie = (y < 1) ? 1 : (y < 3) ? 2 : 3;
            m_bloki.emplace_back(sf::Vector2f(posX, posY), sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y), zycie, m_blockTexture);
        }
    }
}
Paletka& Game::getPaletka() {
    return m_paletka;
}

Pilka& Game::getPilka() {
    return m_pilka;
}

float Game::getWidth() const {
    return m_width;
}


float Game::getHeight() const {
    return m_height;
}

std::vector<Stone>& Game::getBlocks() {
    return m_bloki;
}

//rysowanie blokow, pilki, paletki oraz punktacji
void Game::render(sf::RenderTarget& target) {
    target.draw(m_background);
    //rysowanie blokow
    for (auto& blk : m_bloki) {
        target.draw(blk);
    }
    m_paletka.draw(target);
    m_pilka.draw(target);
    m_scoreText.setString("WYNIK: " + std::to_string(m_score));
    target.draw(m_scoreText);
}

//resetwoanie stanu gry (ustawienie na wartosci poczatkowe)
void Game::resetGame() {
    m_score = 0;
    m_gameOver = false;
    m_paletka = Paletka(320, 440, 100, 20, 8, m_paddleTexture);
    m_pilka = Pilka(320, 280, 4, 3, 8);

    m_bloki.clear();

    const int ILOSC_KOLUMN = 6;
    const int ILOSC_WIERSZY = 7;
    float ROZMIAR_BLOKU_X = (m_width - (ILOSC_KOLUMN - 1) * 2.f) / ILOSC_KOLUMN;
    float ROZMIAR_BLOKU_Y = 25.f;

    for (int y = 0; y < ILOSC_WIERSZY; y++) {
        for (int x = 0; x < ILOSC_KOLUMN; x++) {
            float posX = x * (ROZMIAR_BLOKU_X + 2.f);
            float posY = y * (ROZMIAR_BLOKU_Y + 2.f) + 60.f;
            int zycie = (y < 1) ? 1 : (y < 3) ? 2 : 3;
            m_bloki.emplace_back(sf::Vector2f(posX, posY), sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y), zycie, m_blockTexture);
        }
    }
}

//tworzenie okna porazki
void Game::drawGameOver(sf::RenderTarget& target) const {


    sf::Vector2u windowSize = target.getSize(); //pobranie wielkosci okna

    //teskt koniec gry
    sf::Text gameOverText;
    gameOverText.setFont(m_font);
    gameOverText.setString("KONIEC GRY!");
    gameOverText.setCharacterSize(60);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setOrigin(gameOverText.getGlobalBounds().width / 2.f, gameOverText.getGlobalBounds().height / 2.f);
    gameOverText.setPosition(windowSize.x / 2.f, windowSize.y / 2.f - 60.f);
    target.draw(gameOverText);

    //tekst z wynikiem koncowym
    sf::Text scoreResultText;
    scoreResultText.setFont(m_font);
    scoreResultText.setString("Twój wynik: " + std::to_string(m_score)); 
    scoreResultText.setCharacterSize(30);
    scoreResultText.setFillColor(sf::Color::White);
    scoreResultText.setOrigin(scoreResultText.getGlobalBounds().width / 2.f, scoreResultText.getGlobalBounds().height / 2.f);
    scoreResultText.setPosition(windowSize.x / 2.f, windowSize.y / 2.f + 10.f);
    target.draw(scoreResultText);

    //tekst z nacisnieciem ENTER aby wyjsc
    sf::Text instructionText;
    instructionText.setFont(m_font); 
    instructionText.setString("Nacisnij ENTER aby wyjsc...");
    instructionText.setCharacterSize(20);
    instructionText.setFillColor(sf::Color::Yellow);
    instructionText.setOrigin(instructionText.getGlobalBounds().width / 2.f, instructionText.getGlobalBounds().height / 2.f);
    instructionText.setPosition(windowSize.x / 2.f, windowSize.y / 2.f + 100.f);
    target.draw(instructionText);
}

//rysowanie okna wygranej
void Game::drawGameWon(sf::RenderTarget& target) {
    // generowanie napisu
    sf::Text winText;
    winText.setFont(m_font);
    winText.setString("GRATULACJE!\nWYGRANA!\n\nNACISNIJ ENTER, ABY WYJSC Z GRY.");
    winText.setCharacterSize(40);
    winText.setFillColor(sf::Color::Green);

    //wysrodkowanie tesktu
    sf::FloatRect textRect = winText.getLocalBounds();
    winText.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);

    winText.setPosition(m_width / 2.0f, m_height / 2.0f);

    target.draw(winText);
}

//aktlualizacja gry
void Game::update(sf::Time dt) {
    m_frame++; //zwiekszanie liczby klatek (sluzace do zliczania czasu)

    if (m_frame % 10 == 0) { // co 10 klatek wyswietlanie pozycji i predkosci pilki
        std::cout << "x=" << m_pilka.getX() << " y=" << m_pilka.getY()
            << " vx=" << m_pilka.getVx() << " vy=" << m_pilka.getVy() << std::endl;
    }


    m_pilka.move();
    m_pilka.collideWalls(m_width, m_height);
    if (m_pilka.collidePaddle(m_paletka)) { // jesli wystepuje kolizja z paletka to wyswietlany jest tekst
        std::cout << "HIT PADDLE\n";
    }

    if (m_pilka.getY() - m_pilka.getRadius() > m_height) { // jesli wypadla poza ekran to wyswietla tekst z informacja o przegranej
        m_gameOver = true;
        std::cout << "MISS! KONIEC GRY\n";
    }


    //kolizje pilki z blokami
    for (auto& blk : m_bloki) {
        if (!blk.czyZniszczony() && m_pilka.getGlobalBounds().intersects(blk.getGlobalBounds())) {
            blk.trafienie();
            m_pilka.bounceY();

            if (blk.czyZniszczony()) {
                m_score += 10;

                if (m_score % 50 == 0 && m_score > 0) {
                    float currentVx = m_pilka.getVx();
                    float currentVy = m_pilka.getVy();
                    float currentR = m_pilka.getRadius();

                    if (currentR > 4.0f) {
                        m_pilka.setRadius(currentR - 0.5f);
                    }

                    m_pilka.setVelocity(currentVx * 1.1f, currentVy * 1.1f);
                    std::cout << "Aktualna predkosc: " << m_pilka.getVx() << "\n";
                }
            }
        }
    }

    //usuwanie zniczonych blokow
    //iterujemy do konca wektora (i = bloki.size () - 1 ) do poczatku (i = 0)
    for (int i = m_bloki.size() - 1; i >= 0; i--) {
        if (m_bloki[i].czyZniszczony()) {
            m_bloki.erase(m_bloki.begin() + i);
        }
    }
    if (m_bloki.empty()) {
        m_gameWon = true;
    }
}

