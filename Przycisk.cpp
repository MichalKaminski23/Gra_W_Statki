#include "Przycisk.h"
using namespace sf;


Przycisk::Przycisk(const Vector2f& pozycja, float szerokosc, float wysokosc, const Color& kolor_podstawowy, const Color& kolor_zakrycia)
    : ksztalt(Vector2f(szerokosc, wysokosc)), klikniecie(false), kolor_podstawa(kolor_podstawowy), kolor_zakrycie(kolor_zakrycia)
    //lista inicjalizacyjna
    //Dziêki temu, zmienne s¹ inicjowane od razu, co jest zalecane dla pól const oraz referencji, 
    //poniewa¿ nie mo¿na ich póŸniej zmieniæ na inn¹ wartoœæ ani przypisaæ innego obiektu.
{
    ksztalt.setFillColor(kolor_podstawowy);
    ksztalt.setPosition(pozycja);

    tekst.setFont(Inne::czcionka);
    tekst.setCharacterSize(60);
    tekst.setFillColor(Color::White);
    tekst.setStyle(Text::Bold);
    tekst.setOutlineColor(Color::Black);
    tekst.setOutlineThickness(2);
}

void Przycisk::ustaw_tekst(const std::string& napis, float x, float y)
{
    tekst.setString(napis);
    tekst.setPosition(x, y);
}

void Przycisk::klik(const Event& ruch, RenderWindow& okno)
{
    if (ruch.type == Event::MouseButtonPressed && ruch.mouseButton.button == Mouse::Left)
    {
        Vector2i mysz_pozycja = Mouse::getPosition(okno); 
        Vector2f mysz_pozycja_F(static_cast<float>(mysz_pozycja.x), static_cast<float>(mysz_pozycja.y));

        if (ksztalt.getGlobalBounds().contains(mysz_pozycja_F)) 
        {
            klikniecie = true;
        }
    }
    else if (ruch.type == Event::MouseMoved)
    {
        Vector2i mysz_pozycja = Mouse::getPosition(okno);
        Vector2f mysz_pozycja_F(static_cast<float>(mysz_pozycja.x), static_cast<float>(mysz_pozycja.y));

        if (ksztalt.getGlobalBounds().contains(mysz_pozycja_F))
        {
            ksztalt.setFillColor(kolor_zakrycie);
        }

        else
        {
            ksztalt.setFillColor(kolor_podstawa);
        }
    }
}

void Przycisk::draw(RenderTarget& cel, RenderStates status) const
{
    cel.draw(this->ksztalt);
    cel.draw(this->tekst);
}

bool Przycisk::czy_byl_klikniety() const
{
    return klikniecie;
}


