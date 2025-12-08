#include "stone.hpp"

Stone::Stone(sf::Vector2f startPos, sf::Vector2f rozmiar, int L, const sf::Texture& texture)
	: m_punktyZycia(L), m_jestZniszczony(false)
{
	this->setPosition(startPos);
	this->setSize(rozmiar);
	//setOutlineThickness(2.f);
	//aktualizujKolor();
	this->setTexture(&texture);

	aktualizujTeksture();
}

void Stone::trafienie() {
	if (m_jestZniszczony) {
		return;
	};
	--m_punktyZycia;
	//aktualizujKolor();
	aktualizujTeksture();
	if (m_punktyZycia <= 0) {
		m_jestZniszczony = true;
	};
}

//void Stone::aktualizujKolor() {
//	if (m_punktyZycia >= 0 && m_punktyZycia <= 3) {
//		this->setFillColor(m_colorLUT[m_punktyZycia]);
//	}
//}

//const std::array<sf::Color, 4> Stone::m_colorLUT = {
//sf::Color::Transparent, // L = 0
//sf::Color::Red, // L = 1
//sf::Color::Yellow, // L = 2
//sf::Color::Blue // L = 3
//};

void Stone::aktualizujTeksture() {

    const int wysokosc_klatki = 25;

    if (m_punktyZycia <= 0) {
        this->setTextureRect(sf::IntRect(0, 0, 0, 0));
        return;
    }

    int wierszTextury = 3 - m_punktyZycia;

    this->setTextureRect(sf::IntRect(0, wierszTextury * wysokosc_klatki,(int)this->getSize().x,wysokosc_klatki));
}

bool Stone::czyZniszczony() const {
	return m_jestZniszczony;
}

int Stone::getHP() const {
	return m_punktyZycia;
}