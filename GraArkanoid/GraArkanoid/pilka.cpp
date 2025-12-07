#include "pilka.hpp"

Pilka::Pilka(float x_in, float y_in, float vx_in, float vy_in, float r_in)
	: x(x_in), y(y_in), vx(vx_in), vy(vy_in), radius(r_in) {
	shape.setRadius(radius);
	shape.setOrigin(radius, radius);
	shape.setPosition(x, y);
	shape.setFillColor(sf::Color::White);
}

void Pilka::move() {
	x += vx;
	y += vy;
	shape.setPosition(x, y);
}

void Pilka::bounceX() {
	vx = -vx;
}

void Pilka::bounceY() {
	vy = -vy;
}

void Pilka::collideWalls(float width, float height) {
	if (x - radius <= 0) {
		bounceX();
		x = radius;
	}
	if (x + radius >= width) {
		bounceX();
		x = width - radius;
	}
	if (y - radius <= 0) {
		bounceY();
		y = radius;
	}
}

bool Pilka::collidePaddle(const Paletka& p) {
	float px = p.getX();
	float py = p.getY();
	float pw = p.getSzerokosc();
	float ph = p.getWysokosc();

	bool inRangeX = (x >= px - pw / 2) && (x <= px + pw / 2);
	bool inRangeY = (y + radius >= py - ph / 2) && (y - radius < py - ph / 2);

	if (inRangeX && inRangeY && vy > 0) {
		vy = -std::abs(vy);
		y = py - ph / 2 - radius;
		return true;
	}
	return false;
}

void Pilka::draw(sf::RenderTarget& target) {
	target.draw(shape);
}

void Pilka::setPositionAndVelocity(const sf::Vector2f& pos, const sf::Vector2f& vel) {
	shape.setPosition(pos);

	x = pos.x;
	y = pos.y;

	vx = vel.x;
	vy = vel.y;
}

float Pilka::getX() const { return x; }
float Pilka::getY() const { return y; }
float Pilka::getVx() const { return vx; }
float Pilka::getVy() const { return vy; }
float Pilka::getRadius() const { return radius; }

sf::FloatRect Pilka::getGlobalBounds() const {
	return shape.getGlobalBounds();
}