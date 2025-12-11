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
	void move();
	void bounceX();
	void bounceY();
	void collideWalls(float width, float height);
	bool collidePaddle(const Paletka& p);
	void draw(sf::RenderTarget& target);
	float getX() const;
	float getY() const;
	float getVx() const;
	float getVy() const;
	float getRadius() const;
	sf::FloatRect getGlobalBounds() const;
	void setPositionAndVelocity(const sf::Vector2f& pos, const sf::Vector2f& vel);
	void setRadius(float r_in);
	void setVelocity(float vx_in, float vy_in);
};

