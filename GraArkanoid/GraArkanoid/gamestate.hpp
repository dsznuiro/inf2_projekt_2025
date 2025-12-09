#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

struct BlockData {
    float x, y;
    int hp;

    BlockData(float x_in, float y_in, int hp_in) : x(x_in), y(y_in), hp(hp_in) {}
};

class Paletka;
class Pilka;
class Stone;
class Game;

class GameStatus {
private:
    sf::Vector2f paddlePosition;
    sf::Vector2f ballPosition;
    sf::Vector2f ballVelocity;
    std::vector<BlockData> blocks;
    int score;
    float ballRadius;

public:
    void capture(const Paletka& p, const Pilka& b, const std::vector<Stone>& s, const Game& g);
    const std::vector<BlockData>& getBlocks() const { return blocks; }

    const sf::Vector2f& getPaddlePosition() const { return paddlePosition; }
    const sf::Vector2f& getBallPosition() const { return ballPosition; }
    const sf::Vector2f& getBallVelocity() const { return ballVelocity; }
    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);
    void apply(Paletka& p, Pilka& b, std::vector<Stone>& stones, const sf::Texture& blockTexture, Game& g);
};