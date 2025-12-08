#pragma once
#include <SFML/Graphics.hpp>
#include <array>

class Stone : public sf::RectangleShape {
private:
	int m_punktyZycia;
	bool m_jestZniszczony;
	//static const std::array<sf::Color, 4> m_colorLUT;
public:
	Stone(sf::Vector2f startPos, sf::Vector2f rozmiar, int L, const sf::Texture& texture);
	int getHP() const;
	void trafienie();
	//void aktualizujKolor();
	void aktualizujTeksture();
	bool czyZniszczony() const;
};

