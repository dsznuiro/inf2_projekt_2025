#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "paletka.hpp"
#include "pilka.hpp"
#include "stone.hpp"

class Game {
private:
    int m_frame;
    float m_width;
    float m_height;
    Paletka m_paletka;
    Pilka m_pilka;
    std::vector<Stone> m_bloki;

    // Metody prywatne (wywo³ywane wewn¹trz run())
    void processEvents();
    void update(sf::Time dt);
    void render(sf::RenderTarget& target);

public:
    // Konstruktor i g³ówna metoda uruchamiaj¹ca
    Game();
};