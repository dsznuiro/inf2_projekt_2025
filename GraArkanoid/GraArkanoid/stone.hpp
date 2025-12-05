#pragma once
#include <SFML/Graphics.hpp>
#include <array>

class Stone : public sf::RectangleShape {
private:
	int m_punktyZycia;
	bool m_jestZniszczony;
	static const std::array<sf::Color, 4> m_colorLUT;
public:
	Stone(sf::Vector2f startPos, sf::Vector2f rozmiar, int L);
	void trafienie();
	void aktualizujKolor();
	bool czyZniszczony() const;
};

Stone::Stone(sf::Vector2f startPos, sf::Vector2f rozmiar, int L)
	: m_punktyZycia(L), m_jestZniszczony(false)
{
	this->setPosition(startPos);
	this->setSize(rozmiar);
	setOutlineThickness(2.f);
	aktualizujKolor();
}

void Stone::trafienie() {
	if (m_jestZniszczony) {
		return;
	};
	--m_punktyZycia;
	aktualizujKolor();
	if (m_punktyZycia <= 0) {
		m_jestZniszczony = true;
	};
}

void Stone::aktualizujKolor() {
	if (m_punktyZycia >= 0 && m_punktyZycia <= 3) {
		this->setFillColor(m_colorLUT[m_punktyZycia]);
	}
}

const std::array<sf::Color, 4> Stone::m_colorLUT = {
sf::Color::Transparent, // L = 0
sf::Color::Red, // L = 1
sf::Color::Yellow, // L = 2
sf::Color::Blue // L = 3
};

bool Stone::czyZniszczony() const {
	return m_jestZniszczony;
}