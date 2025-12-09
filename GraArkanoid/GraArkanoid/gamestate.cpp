#include "gamestate.hpp"
#include "paletka.hpp"
#include "pilka.hpp"
#include "stone.hpp"
#include <fstream>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "game.hpp"

void GameStatus::capture(const Paletka& p, const Pilka& b, const std::vector<Stone>& s, const Game& g) {
    paddlePosition = sf::Vector2f(p.getX(), p.getY());
    ballPosition = sf::Vector2f(b.getX(), b.getY());
    ballVelocity = sf::Vector2f(b.getVx(), b.getVy());

    blocks.clear();
    score = g.getScore();

    for (const auto& stone : s) {
        if (!stone.czyZniszczony()) {

            sf::Vector2f pos = stone.getPosition();

            blocks.emplace_back(pos.x, pos.y, stone.getHP());


        }
    }
}

bool GameStatus::saveToFile(const std::string& filename) const {

    std::ofstream file(filename);
    if (!file.is_open()) return false;


    // Zapis Paletki
    file << "PADDLE " << paddlePosition.x << " " << paddlePosition.y << "\n";

    // Zapis Pi³ki
    file << "BALL " << ballPosition.x << " " << ballPosition.y << " " << ballVelocity.x << " " << ballVelocity.y << "\n";

    // Zapis wyniku
    file << "SCORE " << score << "\n";

    // Zapis liczby bloków
    file << "BLOCKS_COUNT " << blocks.size() << "\n";

    // Zapis bloków
    for (const auto& block : blocks) {
        file << block.x << " " << block.y << " " << block.hp << "\n";
    }

    file.close();
    return true;
}

bool GameStatus::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::string label;

    if (file >> label >> paddlePosition.x >> paddlePosition.y) {
        if (label != "PADDLE") {
            std::cerr << "Oczekiwano PADDLE. " << label << ".\n";
            return false;
        }
    }
    else {
        std::cerr << "Brak danych dla Paletki.\n";
        return false;
    }

    if (file >> label >> ballPosition.x >> ballPosition.y >> ballVelocity.x >> ballVelocity.y) {
        if (label != "BALL") {
            std::cerr << "Oczekiwano BALL.\n";
            return false;
        }
    }
    else {
        std::cerr << "Brak danych dla Pi³ki.\n";
        return false;
    }

    if (file >> label >> score) {
        if (label != "SCORE") {
            std::cerr << "Oczekiwano SCORE.\n";
            return false;
        }
    }
    else {
        std::cerr << "Brak danych dla SCORE.\n";
        return false;
    }

    int blocksCount;
    if (file >> label >> blocksCount) {
        if (label != "BLOCKS_COUNT") {
            std::cerr << "Oczekiwano BLOCKS_COUNT.\n";
            return false;
        }
    }
    else {
        std::cerr << "Brak danych dla liczby bloków.\n";
        return false;
    }

    blocks.clear();
    for (int i = 0; i < blocksCount; ++i) {
        float x, y;
        int hp;
        if (!(file >> x >> y >> hp)) {
            std::cerr << "Brak danych dla bloku numer: " << i + 1 << ".\n";
            return false;
        }
        blocks.push_back({ x, y, hp });
    }

    file.close();
    std::cout << "Stan gry wczytany.\n";
    return true;
}
void GameStatus::apply(Paletka& p, Pilka& b, std::vector<Stone>& stones, const sf::Texture& blockTexture, Game& g) {
    p.setPosition(paddlePosition);
    b.setPositionAndVelocity(ballPosition, ballVelocity);
    stones.clear();

    sf::Vector2f size(133.667f, 25.f);
    g.setScore(score);
    for (const auto& data : blocks) {
        stones.emplace_back(sf::Vector2f(data.x, data.y), size, data.hp, blockTexture);
    }
}