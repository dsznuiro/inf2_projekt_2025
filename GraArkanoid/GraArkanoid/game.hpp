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
    sf::Texture m_blockTexture;
    int m_score = 0;
    sf::Font m_font;
    sf::Text m_scoreText;

public:
    Game();
    void update(sf::Time dt);
    void render(sf::RenderTarget& target);
    Paletka& getPaletka();
    Pilka& getPilka();
    float getWidth() const;
    float getHeight() const;
    std::vector<Stone>& getBlocks();
    const sf::Texture& getBlockTexture() const { return m_blockTexture; }
    int getScore() const { return m_score; }
    void setScore(int s) { m_score = s; }
};