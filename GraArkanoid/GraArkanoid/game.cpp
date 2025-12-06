#include "game.hpp"
#include <iostream>

Game::Game() :
    m_pilka(320, 280, 4, 3, 8),
    m_paletka(320, 440, 100, 20, 8)

{

    const int ILOSC_KOLUMN = 6;
    const int ILOSC_WIERSZY = 7;
    float ROZMIAR_BLOKU_X = (m_width - (ILOSC_KOLUMN - 1) * 2.f) / ILOSC_KOLUMN;
    float ROZMIAR_BLOKU_Y = 25.f;

    for (int y = 0; y < ILOSC_WIERSZY; y++) {
        for (int x = 0; x < ILOSC_KOLUMN; x++) {
            float posX = x * (ROZMIAR_BLOKU_X + 2.f);
            float posY = y * (ROZMIAR_BLOKU_Y + 2.f) + 60.f;
            int zycie = (y < 1) ? 1 : (y < 3) ? 2 : 3;
            m_bloki.emplace_back(sf::Vector2f(posX, posY), sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y), zycie);
        }
    }
}


void Game::render(sf::RenderTarget& target) {
    //rysowanie blokow
    for (auto& blk : m_bloki) {
        target.draw(blk);
    }
    m_paletka.draw(target);
    m_pilka.draw(target);
}


void Game::update(sf::Time dt) {
    m_frame++;

    if (m_frame % 10 == 0) {
        std::cout << "x=" << m_pilka.getX() << " y=" << m_pilka.getY()
            << " vx=" << m_pilka.getVx() << " vy=" << m_pilka.getVy() << std::endl;
    }


    m_pilka.move();
    m_pilka.collideWalls(m_width, m_height);
    if (m_pilka.collidePaddle(m_paletka)) {
        std::cout << "HIT PADDLE\n";
    }

    if (m_pilka.getY() - m_pilka.getRadius() > m_height) {
        std::cout << "MISS! KONIEC GRY\n";
    }


    //kolizje pilki z blokami
    for (auto& blk : m_bloki) {
        if (!blk.czyZniszczony() && m_pilka.getGlobalBounds().intersects(blk.getGlobalBounds())) {
            blk.trafienie();//zmniejsza ilosc zyc i zmeni kolor
            m_pilka.bounceY();//pilka sie odbija od bloku
        }
    }

    //usuwanie zniczonych blokow
    //iterujemy do konca wektora (i = bloki.size () - 1 ) do poczatku (i = 0)
    for (int i = m_bloki.size() - 1; i >= 0; i--) {
        if (m_bloki[i].czyZniszczony()) {
            m_bloki.erase(m_bloki.begin() + i);
        }
    }
}
