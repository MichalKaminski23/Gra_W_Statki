#include "Inne.h"
using namespace sf;


Font Inne::czcionka{};

void Inne::czcionka_laduj()
{
	if (!czcionka.loadFromFile("czcionki/calibri.ttf"))
	{
		std::cout << "Problem z czcionka" << std::endl;
		system("pause");
	}
}

void Inne::pisanie_na_ekranie(int x, int y, int rozmiar, int grubosc, const std::string& napis, Color kolor, Color grubosci_kolor, Text tekst, Text::Style styl, RenderWindow& okno)
{

	tekst.setFont(czcionka);
	tekst.setPosition(Vector2f(x, y));
	tekst.setCharacterSize(rozmiar);
	tekst.setFillColor(kolor);
	tekst.setString(napis);
	tekst.setStyle(styl);
	tekst.setOutlineColor(grubosci_kolor);
	tekst.setOutlineThickness(grubosc);
	okno.draw(tekst);
}

void Inne::obrazki_na_ekranie(int x, int y, const std::string& sciezka, RenderWindow& okno)
{
	Texture tekstura;
	Sprite krasnoludek; //wed³ug google t³umacz sprite = krasnoludek - krasnoludek jest potrzebny do tworzenia obiektow
	if (!tekstura.loadFromFile(sciezka))
	{
		std::cout << "Problem z obrazkiem" << std::endl;
		system("pause");
	}
	krasnoludek.setTexture(tekstura);
	krasnoludek.setPosition(Vector2f(x, y));
	tekstura.setSmooth(true);
	okno.draw(krasnoludek);
}

void Inne::mnogosc_pisan_na_ekranie(RenderWindow& okno, const std::string& gracz, Color kolorek)
{
	Text twoj_statek, trafienie_we_wroga, trafienie_wroga, pudlo, legenda, graczX;
	pisanie_na_ekranie(0, 780, 50, 0, "LEGENDA", Color::Black, Color::Transparent, legenda, Text::Style::Regular, okno);
	pisanie_na_ekranie(0, 840, 30, 0, "Twoje statki", Color::Green, Color::Transparent, twoj_statek, Text::Style::Regular, okno);
	pisanie_na_ekranie(0, 880, 30, 0, "Twoje trafienia", Color::Red, Color::Transparent, trafienie_we_wroga, Text::Style::Regular, okno);
	pisanie_na_ekranie(0, 920, 30, 0, "Wrogie trafienia", Color::Black, Color::Transparent, trafienie_wroga, Text::Style::Regular, okno);
	pisanie_na_ekranie(0, 960, 30, 0, "Pudlo", Color::Magenta, Color::Transparent, pudlo, Text::Style::Regular, okno);
	pisanie_na_ekranie(860, 70, 40, 2, gracz, Color::Black, kolorek, graczX, Text::Style::Regular, okno);

	Text literki;
	Text c1, c2, c3, c4, c5, c6, c7, c8, c9, c10;
	pisanie_na_ekranie(165, 10, 45, 0, "A    B     C     D    E     F    G    H     I      J", Color::Black, Color::Transparent, literki, Text::Style::Regular, okno);
	pisanie_na_ekranie(90, 65, 45, 0, "1", Color::Black, Color::Transparent, c1, Text::Style::Regular, okno);
	pisanie_na_ekranie(90, 135, 45, 0, "2", Color::Black, Color::Transparent, c2, Text::Style::Regular, okno);
	pisanie_na_ekranie(90, 205, 45, 0, "3", Color::Black, Color::Transparent, c3, Text::Style::Regular, okno);
	pisanie_na_ekranie(90, 280, 45, 0, "4", Color::Black, Color::Transparent, c4, Text::Style::Regular, okno);
	pisanie_na_ekranie(90, 350, 45, 0, "5", Color::Black, Color::Transparent, c5, Text::Style::Regular, okno);
	pisanie_na_ekranie(90, 420, 45, 0, "6", Color::Black, Color::Transparent, c6, Text::Style::Regular, okno);
	pisanie_na_ekranie(90, 490, 45, 0, "7", Color::Black, Color::Transparent, c7, Text::Style::Regular, okno);
	pisanie_na_ekranie(90, 560, 45, 0, "8", Color::Black, Color::Transparent, c8, Text::Style::Regular, okno);
	pisanie_na_ekranie(90, 630, 45, 0, "9", Color::Black, Color::Transparent, c9, Text::Style::Regular, okno);
	pisanie_na_ekranie(90, 700, 45, 0, "10", Color::Black, Color::Transparent, c10, Text::Style::Regular, okno);
}