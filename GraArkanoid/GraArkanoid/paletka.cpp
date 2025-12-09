#include "paletka.hpp"

Paletka::Paletka(float x_in, float y_in, float szerokosc_in, float wysokosc_in, float predkosc_in, const sf::Texture& texture)
	: x(x_in), y(y_in), szerokosc(szerokosc_in), wysokosc(wysokosc_in), predkosc(predkosc_in) {
	shape.setSize({ szerokosc, wysokosc });
	shape.setOrigin(szerokosc / 2, wysokosc / 2);
	shape.setPosition(x, y);
	//shape.setFillColor(sf::Color::Yellow);
	shape.setTexture(&texture);
}

void Paletka::moveLeft() {
	x -= predkosc;
	shape.setPosition(x, y);
}

void Paletka::moveRight() {
	x += predkosc;
	shape.setPosition(x, y);
}

void Paletka::clampToBounds(float width) {
	if (x - szerokosc / 2 < 0) {
		x = szerokosc / 2;
	}
	if (x + szerokosc / 2 > width) {
		x = width - szerokosc / 2;
	}
	shape.setPosition(x, y);
}

void Paletka::draw(sf::RenderTarget& target) {
	target.draw(shape);
}

void Paletka::setPosition(const sf::Vector2f& pos) {
	shape.setPosition(pos);
}

float Paletka::getX() const { return x; }
float Paletka::getY() const { return y; }
float Paletka::getSzerokosc() const { return szerokosc; }
float Paletka::getWysokosc() const { return wysokosc; }