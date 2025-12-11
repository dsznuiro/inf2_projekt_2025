#pragma once
#include <SFML/Graphics.hpp>
#include <array>

class Stone : public sf::RectangleShape {
private:
	int m_punktyZycia;
	bool m_jestZniszczony;
public:
	Stone(sf::Vector2f startPos, sf::Vector2f rozmiar, int L, const sf::Texture& texture); //konstrutkor (dodatkowo z tekstura)
	int getHP() const; //getter
	void trafienie(); //zmniejsza hp i aktualizuje teksture
	void aktualizujTeksture(); //ustawia poprawna teksture
	bool czyZniszczony() const;	//sprawdza czy blok ma 0 hp
};

