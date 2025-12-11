#pragma once
#include <SFML/Graphics.hpp>


class Paletka {
private:
	float x;
	float y;
	float szerokosc;
	float wysokosc;
	float predkosc;
	sf::RectangleShape shape;
public:
	Paletka() = default;
	Paletka(float x_in, float y_in, float szerokosc_in, float wysokosc_in, float predkosc_in, const sf::Texture& texture);
	void moveLeft();	// przesuniecie pilki w lewo
	void moveRight();	//przesuniecie pilki w prawo
	void clampToBounds(float width);	//ograniczenia ruchu paletki
	void draw(sf::RenderTarget& target);
	//gettery
	float getX() const;
	float getY() const;
	float getSzerokosc() const;
	float getWysokosc() const;

	void setPosition(const sf::Vector2f& pos);// ustawia pozycje (wczytywanie)
};


