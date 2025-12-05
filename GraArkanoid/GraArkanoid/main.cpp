#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "pilka.hpp"
#include "paletka.hpp"
#include "stone.hpp"

int main() {
    float width = 640;
    float height = 480;
    int frame = 0;
    sf::RenderWindow window(sf::VideoMode(width, height), "Arkanoid test");
    window.setFramerateLimit(60);

    Pilka pilka(320, 280, 4, 3, 8);
    Paletka paletka(320, 440, 100, 20, 8);

    std::vector<Stone> bloki;
    const int ILOSC_KOLUMN = 6;
    const int ILOSC_WIERSZY = 7;
    float ROZMIAR_BLOKU_X = (width - (ILOSC_KOLUMN - 1) * 2.f) / ILOSC_KOLUMN;;//uzaleznicz od szerokosci ekranu
    float ROZMIAR_BLOKU_Y = 25.f;

    for (int y = 0; y < ILOSC_WIERSZY; y++) {
        for (int x = 0; x < ILOSC_KOLUMN; x++) {
            float posX = x * (ROZMIAR_BLOKU_X + 2.f);
            float posY = y * (ROZMIAR_BLOKU_Y + 2.f) + 60.f;
            int zycie = (y < 1) ? 1 : (y < 3) ? 2 : 3;
            bloki.emplace_back(sf::Vector2f(posX, posY), sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y), zycie);
        }
    }



    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        frame++;

        if (frame % 10 == 0) {
            std::cout << "x=" << pilka.getX() << " y=" << pilka.getY()
                << " vx=" << pilka.getVx() << " vy=" << pilka.getVy() << std::endl;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            paletka.moveLeft();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            paletka.moveRight();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            paletka.moveLeft();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            paletka.moveRight();
        }

        paletka.clampToBounds(width);

        pilka.move();
        pilka.collideWalls(width, height);
        if (pilka.collidePaddle(paletka)) {
            std::cout << "HIT PADDLE\n";
        }

        if (pilka.getY() - pilka.getRadius() > height) {
            std::cout << "MISS! KONIEC GRY\n";
            window.close();
        }


        //kolizje pilki z blokami
        for (auto& blk : bloki) {
            if (!blk.czyZniszczony() && pilka.getGlobalBounds().intersects(blk.getGlobalBounds())) {
                blk.trafienie();//zmniejsza ilosc zyc i zmeni kolor
                pilka.bounceY();//pilka sie odbija od bloku
            }
        }

        //usuwanie zniczonych blokow
        //iterujemy do konca wektora (i = bloki.size () - 1 ) do poczatku (i = 0)
        for (int i = bloki.size() - 1; i >= 0; i--) {
            if (bloki[i].czyZniszczony()) {
                bloki.erase(bloki.begin() + i);
            }
        }
        window.clear(sf::Color(20, 20, 30));
        //rysowanie blokow
        for (auto& blk : bloki) {
            window.draw(blk);
        }
        paletka.draw(window);
        pilka.draw(window);
        window.display();
    }

    return 0;
}
