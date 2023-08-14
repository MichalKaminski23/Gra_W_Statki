#include "Gra.h"
using namespace sf;


Gra::Gra()
{
	okna.emplace_back(std::make_unique<RenderWindow>(VideoMode(1000, 1000), "Plansza gracza 1", Style::Titlebar | Style::Close));
	okna.emplace_back(std::make_unique<RenderWindow>(VideoMode(1000, 1000), "Plansza gracza 2", Style::Titlebar | Style::Close));

	okna[0]->setPosition(Vector2i(VideoMode::getDesktopMode().width / 2 - 960,
		VideoMode::getDesktopMode().height / 2 - 540));

	okna[1]->setPosition(Vector2i(VideoMode::getDesktopMode().width / 2 + 40,
		VideoMode::getDesktopMode().height / 2 - 540));

	ustawianie_planszy();
}

bool Gra::petla_gry()
{
	Image ikonka;
	ikonka.create(32, 32);

	Color kolory_teczy[] =
	{
		Color(255, 0, 0),    // Czerwony
		Color(255, 165, 0),  // Pomarañczowy
		Color(255, 255, 0),  // ¯ó³ty
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

	Event ruch;

	okna[0]->setFramerateLimit(60);
	okna[1]->setFramerateLimit(60);
	okna[0]->setIcon(32, 32, ikonka.getPixelsPtr());
	okna[1]->setIcon(32, 32, ikonka.getPixelsPtr());

	while (okna[0]->isOpen() and okna[1]->isOpen())
	{
		while (okna[0]->pollEvent(ruch) or okna[1]->pollEvent(ruch))
		{
			okna[0]->clear(Color::White);
			okna[1]->clear(Color::White);

			if (koniec)
			{
				if (koniec_gry_wynik(ruch) == true)
				{
					return true;
				}
			}

			else
			{
				if (Plansza_Rodzic::suma_statkow >= 40)
				{
					if (Plansza_Rodzic::liczba_statkow_plansza[0] == 0 or Plansza_Rodzic::liczba_statkow_plansza[1] == 0)
					{
						Plansza_Rodzic::wartownik = 1;
						koniec = true;
					}

					else
					{
						strzelanie(ruch);
					}
				}

				else
				{
					rozstawianie(ruch);
				}

			}

			if (rodzic.brakujacy_czas_sekundy < -2)
			{
				koniec_gry_czas(ruch);
			}

			if (ruch.type == Event::Closed)
			{
				okna[0]->close();
				okna[1]->close();
			}

			okna[0]->display();
			okna[1]->display();
		}
	}

	return false;
}

void Gra::strzelanie(Event& ruch)
{
	this->rysowanie();

	if (ruch.type == Event::MouseButtonPressed && ruch.mouseButton.button == Mouse::Left)
	{
		for (int i = 0; i < 100; i++)
		{
			auto& pole_gracza = kwadrat[gracz2_tura].at(i);
			auto& pole_wroga = kwadrat[!gracz2_tura].at(i);
			if (Plansza_Rodzic::wartownik == 0)
			{
				if (kolizja(*okna[gracz2_tura], pole_gracza->ksztalt.getGlobalBounds()) && pole_gracza->ilosc_klikniec_kwadrat == 1)
				{
					if (pole_wroga->ksztalt.getFillColor() == Color::Blue)
					{
						//std::cout << "PUDLO" << std::endl;
						//std::cout << " " << std::endl;
						Plansza_Rodzic::pudlo[gracz2_tura]++;
						pole_gracza->ilosc_klikniec_kwadrat = 0;
						pole_gracza->rysuj_kolo_gora(Color::Magenta);
						gracz2_tura = !gracz2_tura;

						//OPERATOR
						std::cout << rodzic << std::endl;
						//OPERATOR
					}

					else if (pole_wroga->ksztalt.getFillColor() == Color::Green)
					{
						//std::cout << "TRAFIONY" << std::endl;
						Plansza_Rodzic::liczba_statkow_plansza[!gracz2_tura]--;
						//std::cout << "POZOSTALO NA PLANSZY STATKOW: " << Plansza_Rodzic::liczba_statkow_plansza[!gracz2_tura] << std::endl;
						//std::cout << " " << std::endl;
						pole_gracza->ilosc_klikniec_kwadrat = 0;
						pole_gracza->rysuj_kolo_gora(Color::Red);
						pole_wroga->rysuj_kolo_dol(Color::Black);

						//OPERATOR
						std::cout << rodzic << std::endl;
						//OPERATOR
					}
				}
			}
		}
	}
}

void Gra::rozstawianie(Event& ruch)
{
	rodzic.mnogosc_pisan_na_ekranie(*okna[0], "Gracz1", Color::Yellow);
	rodzic.wysietlanie_czasu(zegar, Plansza_Rodzic::czas, *okna[0]);
	okna[0]->draw(Plansza_Rodzic::czas);

	if (!gracz2_tura) 
	{
		this->rysowanie_i_stawianie(ruch);

		if (Plansza_Rodzic::suma_statkow < 20)
		{
			int potrzebne_statki = 20 - Plansza_Rodzic::suma_statkow;
			rodzic.tekst_polecenie.setString("Potrzebne statki: " + std::to_string(potrzebne_statki));
			okna[0]->draw(rodzic.tekst_polecenie);
		}

		else
		{
			gracz2_tura = !gracz2_tura;
		}

		Text czekanie_na_ruch;
		rodzic.pisanie_na_ekranie(200, 200, 50, 0, "CZEKAJ NA RUCH GRACZA 1", Color::Green, Color::Transparent, czekanie_na_ruch, Text::Style::Bold, *okna[1]);
	}
	else
	{
		okna[1]->clear(Color::White);

		for (auto& pole : this->kwadrat[0])
		{
			okna[0]->draw(*pole);
		}

		rodzic.mnogosc_pisan_na_ekranie(*okna[1], "Gracz2", Color::Magenta);
		rodzic.wysietlanie_czasu(zegar, Plansza_Rodzic::czas, *okna[1]);

		okna[1]->draw(Plansza_Rodzic::czas);

		this->rysowanie_i_stawianie(ruch);

		if (Plansza_Rodzic::suma_statkow < 40)
		{
			int potrzebne_statki = 40 - Plansza_Rodzic::suma_statkow;
			rodzic.tekst_polecenie.setString("Potrzebne statki: " + std::to_string(potrzebne_statki));
			okna[1]->draw(rodzic.tekst_polecenie);

		}
		else 
		{
			gracz2_tura = !gracz2_tura;

			for (auto& wektor : kwadrat)
			{
				for (auto& pole : wektor)
				{
					pole->ilosc_klikniec_kwadrat = 1;
				}
			}
		}
	}
}

void Gra::rysowanie_i_stawianie(Event& ruch)
{
	for (auto& pole : this->kwadrat[gracz2_tura])
	{
		okna[gracz2_tura]->draw(*pole);

		if (Plansza_Rodzic::wartownik == 0)
		{
			if (ruch.type == Event::MouseButtonPressed)
			{

				if (kolizja(*okna[gracz2_tura], pole->ksztalt.getGlobalBounds()))
				{
					if (ruch.mouseButton.button == Mouse::Left)
					{
						if (Plansza_Rodzic::liczba_statkow_plansza[gracz2_tura] < 20)
						{
							if (pole->ilosc_klikniec_kwadrat < 1)
							{
								pole->ksztalt.setFillColor(Color::Green);
								pole->ilosc_klikniec_kwadrat++;
								//std::cout << "Liczba klikniec dla tego kwadratu: " << pole->ilosc_klikniec_kwadrat << std::endl;
								Plansza_Rodzic::suma_statkow++;

								

								if (Plansza_Rodzic::liczba_statkow_plansza[gracz2_tura] < 20)
								{
									Plansza_Rodzic::liczba_statkow_plansza[gracz2_tura]++;

									//OPERATOR
									std::cout << rodzic << std::endl;
									//OPERATOR
									
									//std::cout << "Liczba statkow na planszy1: " << Plansza_Rodzic::liczba_statkow_plansza[gracz2_tura] << std::endl;
									//std::cout << "Suma wszystkich statkow: " << Plansza_Rodzic::suma_statkow << std::endl;
									//std::cout << " " << std::endl;
								}

								if (Plansza_Rodzic::liczba_statkow_plansza[gracz2_tura] >= 20 && !gracz2_tura)
								{
									Plansza_Rodzic::liczba_statkow_plansza[!gracz2_tura] = 0;
									//std::cout << " " << std::endl;
								}
							}
						}
					}

					else if (ruch.mouseButton.button == Mouse::Right)
					{
						if (Plansza_Rodzic::suma_statkow < 40)
						{
							if (Plansza_Rodzic::liczba_statkow_plansza[!gracz2_tura])
							{
								if (pole->ilosc_klikniec_kwadrat == 1)
								{
									pole->ksztalt.setFillColor(Color::Blue);
									pole->ilosc_klikniec_kwadrat--;
									//std::cout << "Liczba klikniec dla tego kwadratu: " << pole->ilosc_klikniec_kwadrat << std::endl;
									Plansza_Rodzic::suma_statkow--;

									if (Plansza_Rodzic::liczba_statkow_plansza[gracz2_tura] < 20)
									{
										Plansza_Rodzic::liczba_statkow_plansza[gracz2_tura]--;
										//std::cout << "Liczba statkow na planszy1: " << Plansza_Rodzic::liczba_statkow_plansza[gracz2_tura] << std::endl;
									}
									//std::cout << "Suma wszystkich statkow: " << Plansza_Rodzic::suma_statkow << std::endl;
									//std::cout << "" << std::endl;

									//OPERATOR
									std::cout << rodzic << std::endl;
									//OPERATOR
								}
							}

							else
							{
								if (pole->ilosc_klikniec_kwadrat == 1)
								{
									pole->ksztalt.setFillColor(Color::Blue);
									pole->ilosc_klikniec_kwadrat--;
									//std::cout << "Liczba klikniec dla tego kwadratu: " << pole->ilosc_klikniec_kwadrat << std::endl;
									Plansza_Rodzic::suma_statkow--;

									if (Plansza_Rodzic::liczba_statkow_plansza[gracz2_tura] < 20)
									{
										Plansza_Rodzic::liczba_statkow_plansza[gracz2_tura]--;
										//std::cout << "Liczba statkow na planszy1: " << Plansza_Rodzic::liczba_statkow_plansza[gracz2_tura] << std::endl;
									}
									//std::cout << "Suma wszystkich statkow: " << Plansza_Rodzic::suma_statkow << std::endl;
									//std::cout << "" << std::endl;

									//OPERATOR
									std::cout << rodzic << std::endl;
									//OPERATOR
								}
							}
						}
					}
				}
			}
		}
	}
}

void Gra::rysowanie()
{
	for (auto& pole : this->kwadrat[0])
	{
		okna[0]->draw(*pole);
	}

	for (auto& pole : this->kwadrat[1])
	{
		okna[1]->draw(*pole);
	}

	rodzic.mnogosc_pisan_na_ekranie(*okna[0], "Gracz1", Color::Yellow);
	rodzic.wysietlanie_czasu(zegar, Plansza_Rodzic::czas, *okna[0]);
	okna[0]->draw(Plansza_Rodzic::czas);

	rodzic.mnogosc_pisan_na_ekranie(*okna[1], "Gracz2", Color::Magenta);
	rodzic.wysietlanie_czasu(zegar, Plansza_Rodzic::czas, *okna[1]);
	okna[1]->draw(Plansza_Rodzic::czas);

	rodzic.pisanie_na_ekranie(375, 800, 70, 2, "!Strzelaj!", Color::Red, Color::Black, tura_wiadomosc, Text::Style::Bold, *okna[gracz2_tura]);
	rodzic.pisanie_na_ekranie(375, 800, 70, 2, "!Czekaj!", Color::Green, Color::Black, tura_wiadomosc, Text::Style::Bold, *okna[!gracz2_tura]);

	rodzic.tekst_status_twoje.setString("Twoje statki: " + std::to_string(Plansza_Rodzic::liczba_statkow_plansza[0]));
	okna[0]->draw(rodzic.tekst_status_twoje);

	rodzic.tekst_status_twoje.setString("Twoje statki: " + std::to_string(Plansza_Rodzic::liczba_statkow_plansza[1]));
	okna[1]->draw(rodzic.tekst_status_twoje);

	rodzic.tekst_status_wrogie.setString("Wrogie statki: " + std::to_string(Plansza_Rodzic::liczba_statkow_plansza[1]));
	okna[0]->draw(rodzic.tekst_status_wrogie);

	rodzic.tekst_status_wrogie.setString("Wrogie statki: " + std::to_string(Plansza_Rodzic::liczba_statkow_plansza[0]));
	okna[1]->draw(rodzic.tekst_status_wrogie);
}

void Gra::ustawianie_planszy()
{

	Plansza_Rodzic::pudlo[0] = 0;
	Plansza_Rodzic::pudlo[1] = 0;
	Plansza_Rodzic::suma_statkow = 0;
	Plansza_Rodzic::liczba_statkow_plansza[0] = 0;
	Plansza_Rodzic::liczba_statkow_plansza[1] = 0;
	Plansza_Rodzic::wartownik = 0;
	koniec = false;
	gracz2_tura = false;

	rodzic.tekst_polecenie.setFont(Inne::czcionka);
	rodzic.tekst_polecenie.setCharacterSize(40);
	rodzic.tekst_polecenie.setFillColor(Color::Green);
	rodzic.tekst_polecenie.setPosition(325, 775);

	rodzic.tekst_status_twoje.setFont(Inne::czcionka);
	rodzic.tekst_status_twoje.setCharacterSize(25);
	rodzic.tekst_status_twoje.setFillColor(Color::Green);
	rodzic.tekst_status_twoje.setPosition(840, 250);

	rodzic.tekst_status_wrogie.setFont(Inne::czcionka);
	rodzic.tekst_status_wrogie.setCharacterSize(23);
	rodzic.tekst_status_wrogie.setFillColor(Color::Red);
	rodzic.tekst_status_wrogie.setPosition(840, 300);

	Plansza_Rodzic::czas.setFont(Inne::czcionka);
	Plansza_Rodzic::czas.setCharacterSize(30);
	Plansza_Rodzic::czas.setFillColor(Color::Black);
	Plansza_Rodzic::czas.setPosition(885, 185);

	int KwadratX1{ 10 }, KwadratY1{ 10 }, KwadratWysokosc1{ 65 }, KwadratSzerokosc1{ 65 };
	kwadrat[0].clear();
	kwadrat[1].clear();

	for (int i = 0; i < KwadratY1; i++)
	{
		for (int j = 0; j < KwadratX1; j++)
		{
			kwadrat[0].emplace_back(std::make_unique<Pole>((j + 1) * (KwadratSzerokosc1 + 5), (i + 2) * (KwadratWysokosc1 + 5), KwadratSzerokosc1, KwadratWysokosc1));
		}
	}

	int KwadratX2{ 10 }, KwadratY2{ 10 }, KwadratWysokosc2{ 65 }, KwadratSzerokosc2{ 65 }; //tutaj inicjalizujemy wektor z polami2 ktore sa chowane w wektorze2 

	//Linia kodu std::vector<std::unique_ptr<Pole>> Gra::kwadrat[2]; deklaruje wektor dwuelementowy kwadrat (0 lub 1), który przechowuje wskaŸniki typu std::unique_ptr<Pole>.	
	//std::vector jest kontenerem sekwencyjnym w bibliotece standardowej C++, który umo¿liwia przechowywanie i zarz¹dzanie dynamicznie rozszerzaln¹ kolekcj¹ elementów.
	//std::unique_ptr jest inteligentnym wskaŸnikiem, który zarz¹dza dynamicznie alokowanymi obiektami i automatycznie zwalnia pamiêæ, gdy obiekt przestaje byæ potrzebny.
	//W tym przypadku, std::unique_ptr przechowuje wskaŸniki na obiekty typu Pole.
	//Pole to typ obiektów, na które wskazuj¹ wskaŸniki przechowywane w wektorze kwadrat.
	//W rezultacie, kwadrat jest wektorem, który przechowuje wskaŸniki na obiekty Pole i automatycznie zarz¹dza ich pamiêci¹. Dziêki temu mo¿na bezpiecznie dodawaæ, 
	//usuwaæ i zarz¹dzaæ obiektami w wektorze kwadrat bez koniecznoœci rêcznego zarz¹dzania pamiêci¹.

	for (int i = 0; i < KwadratY2; i++)
	{
		for (int j = 0; j < KwadratX2; j++)
		{
			kwadrat[1].emplace_back(std::make_unique<Pole>((j + 1) * (KwadratSzerokosc2 + 5), (i + 2) * (KwadratWysokosc2 + 5), KwadratSzerokosc2, KwadratWysokosc2));
			//std::make_unique<Pole> tworzy unikalny wskaŸnik na obiekt typu Pole, 
			//alokuj¹c pamiêæ dla tego obiektu i inicjalizuj¹c go za pomoc¹ przekazanych argumentów konstruktora.
		}
	}
}

bool Gra::kolizja(RenderWindow& okno, FloatRect granice)
{
	Vector2i mysz_pozycja = Mouse::getPosition(okno); //aktualne wspolrzedne myszki
	Vector2f mysz_pozycja_F(static_cast<float>(mysz_pozycja.x), static_cast<float>(mysz_pozycja.y)); //zamiana na zmiennoprzecinkowe te wartosci

	return granice.contains(mysz_pozycja_F); //sprawdzanie czy wspolrzedne myszki mieszcza sie w danym obiekcie;
}

bool Gra::koniec_gry_wynik(const Event& ruch)
{
	okna[0]->clear(Color::White);
	okna[1]->clear(Color::White);

	Text napis;

	koniec = true;

	zegar.restart();

	if (Plansza_Rodzic::liczba_statkow_plansza[0] > Plansza_Rodzic::liczba_statkow_plansza[1])
	{
		rodzic.pisanie_na_ekranie(260, 200, 60, 2, "WYGRAL GRACZ 1", Color::Black, Color::Magenta, napis, Text::Style::Bold, *okna[0]);
		rodzic.pisanie_na_ekranie(260, 200, 60, 2, "WYGRAL GRACZ 1", Color::Black, Color::Magenta, napis, Text::Style::Bold, *okna[1]);
	}

	if (Plansza_Rodzic::liczba_statkow_plansza[0] < Plansza_Rodzic::liczba_statkow_plansza[1])
	{
		rodzic.pisanie_na_ekranie(260, 200, 60, 2, "WYGRAL GRACZ 2", Color::Black, Color::Yellow, napis, Text::Style::Bold, *okna[0]);
		rodzic.pisanie_na_ekranie(260, 200, 60, 2, "WYGRAL GRACZ 2", Color::Black, Color::Yellow, napis, Text::Style::Bold, *okna[1]);
	}

	rodzic.twoje_koniec.setFont(Inne::czcionka);
	rodzic.twoje_koniec.setCharacterSize(60);
	rodzic.twoje_koniec.setFillColor(Color::Green);
	rodzic.twoje_koniec.setPosition(200, 300);

	rodzic.wrogie_koniec.setFont(Inne::czcionka);
	rodzic.wrogie_koniec.setCharacterSize(60);
	rodzic.wrogie_koniec.setFillColor(Color::Red);
	rodzic.wrogie_koniec.setPosition(200, 400);

	rodzic.pudlo1.setFont(Inne::czcionka);
	rodzic.pudlo1.setCharacterSize(60);
	rodzic.pudlo1.setFillColor(Color::Magenta);
	rodzic.pudlo1.setPosition(200, 500);

	rodzic.pudlo2.setFont(Inne::czcionka);
	rodzic.pudlo2.setCharacterSize(60);
	rodzic.pudlo2.setFillColor(Color::Magenta);
	rodzic.pudlo2.setPosition(200, 500);

	rodzic.pudlo1.setString("Ilosc spudlowan: " + std::to_string(Plansza_Rodzic::pudlo[0]));
	okna[0]->draw(rodzic.pudlo1);
	rodzic.pudlo2.setString("Ilosc spudlowan: " + std::to_string(Plansza_Rodzic::pudlo[1]));
	okna[1]->draw(rodzic.pudlo2);

	rodzic.twoje_koniec.setString("Ilosc twoich statkow: " + std::to_string(Plansza_Rodzic::liczba_statkow_plansza[0]));
	okna[0]->draw(rodzic.twoje_koniec);
	rodzic.twoje_koniec.setString("Ilosc twoich statkow: " + std::to_string(Plansza_Rodzic::liczba_statkow_plansza[1]));
	okna[1]->draw(rodzic.twoje_koniec);

	rodzic.wrogie_koniec.setString("Ilosc wrogich statkow: " + std::to_string(Plansza_Rodzic::liczba_statkow_plansza[1]));
	okna[0]->draw(rodzic.wrogie_koniec);
	rodzic.wrogie_koniec.setString("Ilosc wrogich statkow: " + std::to_string(Plansza_Rodzic::liczba_statkow_plansza[0]));
	okna[1]->draw(rodzic.wrogie_koniec);

	Przycisk od_nowa(Vector2f(0, 750), 1000, 100, Color::Green, Color::Red);
	od_nowa.ustaw_tekst("Nowa gra :))", 350, 760);
	od_nowa.klik(ruch, *okna[0]);

	Przycisk wyjscie(Vector2f(0, 900), 1000, 100, Color::Black, Color::Blue);
	wyjscie.ustaw_tekst("Koniec gry :((", 350, 910);
	wyjscie.klik(ruch, *okna[0]);

	okna[0]->draw(od_nowa);
	okna[0]->draw(wyjscie);

	if (wyjscie.czy_byl_klikniety())
	{
		okna[0]->close();
		okna[1]->close();

		wyjscie.klikniecie = false;
	}

	if (od_nowa.czy_byl_klikniety())
	{
		okna[0]->close();
		okna[1]->close();
		okna.pop_back();
		okna.pop_back();

		okna.emplace_back(std::make_unique<sf::RenderWindow>(VideoMode(1000, 1000), "Plansza gracza 1", Style::Titlebar | Style::Close));
		okna.emplace_back(std::make_unique<sf::RenderWindow>(VideoMode(1000, 1000), "Plansza gracza 2", Style::Titlebar | Style::Close));

		okna[0]->setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - 960,
			sf::VideoMode::getDesktopMode().height / 2 - 540));

		okna[1]->setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 + 40,
			sf::VideoMode::getDesktopMode().height / 2 - 540));

		ustawianie_planszy();

		system("cls");

		od_nowa.klikniecie = false;
		return true;
	}
	return false;
}

bool Gra::koniec_gry_czas(const Event& ruch)
{
	okna[0]->clear(Color::White);
	okna[1]->clear(Color::White);
	
	Text napis;
	
	rodzic.pisanie_na_ekranie(350, 200, 60, 2, "KONIEC CZASU", Color::Black, Color::Magenta, napis, Text::Style::Bold, *okna[0]);
	rodzic.pisanie_na_ekranie(350, 200, 60, 2, "KONIEC CZASU", Color::Black, Color::Magenta, napis, Text::Style::Bold, *okna[1]);
	koniec = true;
	zegar.restart();

	Przycisk od_nowa(Vector2f(0, 750), 1000, 100, Color::Green, Color::Red);
	od_nowa.ustaw_tekst("Nowa gra :))", 350, 760);
	od_nowa.klik(ruch, *okna[0]);

	Przycisk wyjscie(Vector2f(0, 900), 1000, 100, Color::Black, Color::Blue);
	wyjscie.ustaw_tekst("Koniec gry :((", 350, 910);
	wyjscie.klik(ruch, *okna[0]);

	okna[0]->draw(od_nowa);
	okna[0]->draw(wyjscie);

	if (wyjscie.czy_byl_klikniety())
	{
		okna[0]->close();
		okna[1]->close();

		wyjscie.klikniecie = false;
	}

	if (od_nowa.czy_byl_klikniety())
	{
		okna[0]->close();
		okna[1]->close();
		okna.pop_back();
		okna.pop_back();

		okna.emplace_back(std::make_unique<sf::RenderWindow>(VideoMode(1000, 1000), "Plansza gracza 1", Style::Titlebar | Style::Close));
		okna.emplace_back(std::make_unique<sf::RenderWindow>(VideoMode(1000, 1000), "Plansza gracza 2", Style::Titlebar | Style::Close));

		okna[0]->setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - 960,
			sf::VideoMode::getDesktopMode().height / 2 - 540));

		okna[1]->setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 + 40,
			sf::VideoMode::getDesktopMode().height / 2 - 540));

		ustawianie_planszy();

		system("cls");

		od_nowa.klikniecie = false;
		return true;
	}
	return false;
}


