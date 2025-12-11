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

//delklaracja dla kompilatora ze te klasy istnieja
class Paletka;
class Pilka;
class Stone;
class Game;

class GameStatus {
private:
    sf::Vector2f paddlePosition;
    sf::Vector2f ballPosition;
    sf::Vector2f ballVelocity;
    std::vector<BlockData> blocks;//dane o blokach
    int score;
    float ballRadius;

public:
    void capture(const Paletka& p, const Pilka& b, const std::vector<Stone>& s, const Game& g);
    //gettery
    const std::vector<BlockData>& getBlocks() const { return blocks; }
    const sf::Vector2f& getPaddlePosition() const { return paddlePosition; }
    const sf::Vector2f& getBallPosition() const { return ballPosition; }
    const sf::Vector2f& getBallVelocity() const { return ballVelocity; }
    bool saveToFile(const std::string& filename) const; //zapisywanie stanu do pliku
    bool loadFromFile(const std::string& filename); //odczytywanie stanu z pliku
    void apply(Paletka& p, Pilka& b, std::vector<Stone>& stones, const sf::Texture& blockTexture, Game& g); //zastosowanie wczytanego stanu do elementow gry
};