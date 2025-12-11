#include "stone.hpp"

Stone::Stone(sf::Vector2f startPos, sf::Vector2f rozmiar, int L, const sf::Texture& texture)
	: m_punktyZycia(L), m_jestZniszczony(false)
{
	this->setPosition(startPos);
	this->setSize(rozmiar);
	this->setTexture(&texture);	//przypisane tekstury

	aktualizujTeksture();
}

//zmniejsza hp po trafieniu i aktualizuje teksture
void Stone::trafienie() {
	if (m_jestZniszczony) {
		return;
	};
	--m_punktyZycia;
	aktualizujTeksture();
	if (m_punktyZycia <= 0) {
		m_jestZniszczony = true; //jesli blok ma 0 hp to zostaje zniszczony
	};
}


void Stone::aktualizujTeksture() {
	//zastosowano sprite do optymalizacji pliku png (wystarczy tylko jeden plik png ktory odzwierciedla 3 stany)
    const int wysokosc_klatki = 25;

    if (m_punktyZycia <= 0) {
        this->setTextureRect(sf::IntRect(0, 0, 0, 0));
        return;
    }

    int wierszTextury = 3 - m_punktyZycia;
	//x jest zawsze rowny 0 a y odpowiednio 0,25,50
    this->setTextureRect(sf::IntRect(0, wierszTextury * wysokosc_klatki,(int)this->getSize().x,wysokosc_klatki));
}

//zwraca informacje czy jest zniszczony
bool Stone::czyZniszczony() const {
	return m_jestZniszczony;
}

//zwraca hp
int Stone::getHP() const {
	return m_punktyZycia;
}