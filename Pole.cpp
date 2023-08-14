#include "Pole.h"
using namespace sf;


Pole::Pole(float x, float y, float szerokosc, float wysokosc)
{
	ksztalt.setPosition(x, y);
	ksztalt.setSize({ szerokosc,wysokosc });
	ksztalt.setFillColor(Color::Blue);
	ksztalt.setOrigin({ szerokosc - 140,wysokosc + 10 });
	ksztalt.getGlobalBounds();
}

void Pole::rysuj_kolo_gora(const Color& kolor)
{
	kolo_gora.setRadius(ksztalt.getSize().x / 4);
	kolo_gora.setPosition(ksztalt.getPosition().x + 80, ksztalt.getPosition().y - 70);
	kolo_gora.setFillColor(kolor);
}

void Pole::rysuj_kolo_dol(const Color& kolor)
{
	kolo_dol.setRadius(ksztalt.getSize().x / 4);
	kolo_dol.setPosition(ksztalt.getPosition().x + 105, ksztalt.getPosition().y - 45);
	kolo_dol.setFillColor(kolor);
}

void Pole::draw(RenderTarget& cel, RenderStates status) const
{
	cel.draw(this->ksztalt);
	cel.draw(this->kolo_gora);
	cel.draw(this->kolo_dol);
}



