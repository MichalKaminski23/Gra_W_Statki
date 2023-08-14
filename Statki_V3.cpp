#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <fstream>
#include "Inne.h"
#include "Przycisk.h"
#include "Plansza_Rodzic.h"
#include "Gra.h"
using namespace sf;


int main()
{
	RenderWindow okno_startowe(VideoMode(1000, 1000), "Gra w statki", Style::Titlebar | Style::Close);
	Inne::czcionka_laduj();
	
	Image ikonka;
	ikonka.create(32, 32);

	Color kolory_teczy[] = 
	{
		Color(255, 0, 0),    // Czerwony
		Color(255, 165, 0),  // Pomarańczowy
		Color(255, 255, 0),  // Żółty
		Color(0, 128, 0),    // Zielony
		Color(0, 0, 255),    // Niebieski
		Color(75, 0, 130),   // Indygo
		Color(148, 0, 211)   // Fioletowy
	};

	for (int i = 0; i < 7; ++i) 
	{
		for (int x = i * 4; x < (i + 1) * 4; ++x) 
		{
			for (int y = 0; y < 32; ++y) 
			{
				ikonka.setPixel(x, y, kolory_teczy[i]);
			}
		}
	}

	okno_startowe.setIcon(32, 32, ikonka.getPixelsPtr());

	okno_startowe.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - 525,
		sf::VideoMode::getDesktopMode().height / 2 - 540));

	Event ruch;
	
	Przycisk start(Vector2f(0, 600), 1000, 100, Color::Green, Color::Red);
	Przycisk autor(Vector2f(0, 750), 1000, 100, Color::Magenta, Color::Yellow);
	Przycisk wyjscie(Vector2f(0, 900), 1000, 100, Color::Black, Color::Blue);

	start.ustaw_tekst("Rozpocznij", 350, 610);
	autor.ustaw_tekst("O autorze", 350, 760);
	wyjscie.ustaw_tekst("Zamknij program", 270, 910);

	while (okno_startowe.isOpen())
	{
		while (okno_startowe.pollEvent(ruch))
		{
			if (ruch.type == Event::Closed)
			{
				okno_startowe.close();
			}
			autor.klik(ruch, okno_startowe);
			wyjscie.klik(ruch, okno_startowe);
			start.klik(ruch, okno_startowe);
		}

		okno_startowe.setFramerateLimit(60);
		okno_startowe.clear(Color::White);
		okno_startowe.draw(start);
		okno_startowe.draw(autor);
		okno_startowe.draw(wyjscie);

		Text powitanie;
		Inne powitanieX;
		powitanieX.pisanie_na_ekranie(150, 0, 60, 2, "Parostatkiem w piekny rejs", Color::Red, Color::Yellow, powitanie, Text::Style::Bold, okno_startowe);
		powitanieX.obrazki_na_ekranie(100, 100, "fotki/statek.jpg", okno_startowe);

		okno_startowe.display();

		if (start.czy_byl_klikniety())
		{
			okno_startowe.close();
			Gra gra;

			while (gra.petla_gry())
			{

			}

			start.klikniecie = false;
		}
		  

		if (autor.czy_byl_klikniety())
		{
			RenderWindow okno_autor(VideoMode(500, 300), "Od autora", Style::Titlebar | Style::Close);

			okno_autor.setIcon(32, 32, ikonka.getPixelsPtr());

			std::fstream plik_z_danymi;
			plik_z_danymi.open("pliki/dane_autora.txt", std::ios::in);
			if (plik_z_danymi.good() == true)
			{
				std::string dane;
				std::string linia;

				while (getline(plik_z_danymi, linia))
				{
					dane += linia + '\n';
				}

				plik_z_danymi.close();

				while (okno_autor.isOpen())
				{
					while (okno_startowe.pollEvent(ruch))
					{
						if (ruch.type == Event::Closed)
						{
							okno_autor.close();
							okno_startowe.close();
						}
					}

					while (okno_autor.pollEvent(ruch))
					{
						if (ruch.type == Event::Closed)
						{
							okno_autor.close();
						}
					}

					okno_autor.clear(Color::Cyan);

					Text autorX;
					Inne autor;
					autor.pisanie_na_ekranie(0, 0, 30, 0, dane, Color::Black, Color::Transparent, autorX, Text::Style::Regular, okno_autor);

					okno_autor.display();
				}
			}
			autor.klikniecie = false;
		}

		if (wyjscie.czy_byl_klikniety())
		{
			while (okno_startowe.pollEvent(ruch))
			{
				okno_startowe.close();
			}
		}

	}

	return 0;
}