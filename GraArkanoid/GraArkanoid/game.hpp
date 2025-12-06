#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "paletka.hpp"
#include "pilka.hpp"
#include "stone.hpp"

class Game {
private:
    int m_frame = 0;
    float m_width = 800;
    float m_height = 600;
    Paletka m_paletka;
    Pilka m_pilka;
    std::vector<Stone> m_bloki;

public:
    Game();
    void update(sf::Time dt);
    void render(sf::RenderTarget& target);
    Paletka& getPaletka();
    float getWidth() const;
    float getHeight() const;
};