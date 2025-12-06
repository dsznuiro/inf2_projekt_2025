#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>

struct BlockData {
    float x, y;
    int hp;
};

class Paletka;
class Pilka;
class Stone;

class GameState {
private:
    sf::Vector2f paddlePosition;
    sf::Vector2f ballPosition;
    sf::Vector2f ballVelocity;
    std::vector<BlockData> blocks;

public:
    void capture(const Paletka& p, const Pilka& b, const std::vector<Stone>& s);

    const std::vector<BlockData>& getBlocks() const { return blocks; }

    const sf::Vector2f& getPaddlePosition() const { return paddlePosition; }
    const sf::Vector2f& getBallPosition() const { return ballPosition; }
    const sf::Vector2f& getBallVelocity() const { return ballVelocity; }
    bool saveToFile(const std::string& filename) const;
};