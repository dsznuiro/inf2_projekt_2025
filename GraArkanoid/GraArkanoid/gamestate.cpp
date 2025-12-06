#include "GameState.hpp"
#include "paletka.hpp"
#include "pilka.hpp"
#include "stone.hpp"
#include <fstream>
#include <string>
#include <iostream>

void GameState::capture(const Paletka& p, const Pilka& b, const std::vector<Stone>& s) {
    paddlePosition = sf::Vector2f(p.getX(), p.getY());

    ballPosition = sf::Vector2f(b.getX(), b.getY());
    ballVelocity = sf::Vector2f(b.getVx(), b.getVy());

    blocks.clear();

    for (const auto& stone : s) {
        if (!stone.czyZniszczony()) {

            sf::Vector2f pos = stone.getPosition();

            blocks.emplace_back(pos.x, pos.y, stone.getHP());
        }
    }
}

bool GameState::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Blad: Nie mozna otworzyc pliku do zapisu: " << filename << std::endl;
        return false;
    }

    file << "PADDLE " << paddlePosition.x << " " << paddlePosition.y << "\n";

    file << "BALL " << ballPosition.x << " " << ballosition.y << " "
        << ballVelocity.x << " " << ballVelocity.y << "\n";

    file << "BLOCKS_COUNT " << blocks.size() << "\n";

    for (const auto& block : blocks) {
        file << block.x << " " << block.y << " " << block.hp << "\n";
    }

    file.close();
    return true;
}