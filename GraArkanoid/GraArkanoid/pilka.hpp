#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>
#include "paletka.hpp"

class Paletka;

class Pilka {
private:
	float x, y;
	float vx, vy;
	float radius;
	sf::CircleShape shape;
public:

	Pilka(float x_in, float y_in, float vx_in, float vy_in, float r_in);
	void move();	//przesuwa pilke
	void bounceX();	//odbicie w osi X (zmienia predkosc na przeciwna)
	void bounceY(); //odbicie w osi Y (zmienia predkosc na przeciwna)
	void collideWalls(float width, float height);	//sprawdzanie kolizji ze sciana
	bool collidePaddle(const Paletka& p);	//sprawdzanie kolizji z paletka
	void draw(sf::RenderTarget& target);
	//gettery 
	float getX() const;
	float getY() const;
	float getVx() const;
	float getVy() const;
	float getRadius() const;
	sf::FloatRect getGlobalBounds() const;
	void setPositionAndVelocity(const sf::Vector2f& pos, const sf::Vector2f& vel); //ustawienie pozycji i predkosci (podczas wczytywania gry)
	void setRadius(float r_in);	// zmiana promienia pilki
	void setVelocity(float vx_in, float vy_in); //zmiana predkosci pilki
};

