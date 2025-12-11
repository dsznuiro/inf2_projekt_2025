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
    sf::Texture m_paddleTexture;
    sf::Texture m_backgroundTexture;
    sf::Sprite m_backgroundSprite;
    bool m_gameOver = false;
    bool m_gameWon = false;
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
    void setScore(int s) { m_score = s; };
    void resetGame();
    bool isGameOver() const { return m_gameOver; }
    bool isGameWon() const { return m_gameWon; }
    const sf::Font& getFont() const { return m_font; }
    void drawGameOver(sf::RenderTarget& target) const;
    void drawGameWon(sf::RenderTarget& target);
};