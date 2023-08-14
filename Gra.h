#pragma once
/** @file */

#ifndef GRA
#define GRA
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Plansza_Rodzic.h"
#include "Pole.h"

/// KLASA REPREZENTUJACA GRE
/// 
/// Klasa Gra jest odpowiedzialna za cala rozgrywke
class Gra
{
public:

	/// DOMYSLNY KONSTRUKTOR KLASY GRA
	Gra();

	/// DOMYSLNY DESTRUKTOR KLASY GRA
	~Gra() = default;

	/// PETLA GRY
	/// 
	/// Funkcja sluzaca do zapetlania gry oraz wyboru odpowiednich akcji podczas gry
	/// @return True, jesli petla gry powinna sie kontynuowac, w przeciwnym razie false
	bool petla_gry();

	/// Obiekt Plansza_Rodzic potrzebny do operatora
	Plansza_Rodzic rodzic;

	/// Wektor unikalnych wskaznikow na okna
	std::vector<std::unique_ptr<sf::RenderWindow>> okna;
private:

	/// Zegar gry
	sf::Clock zegar;

	/// Tekst informujacy o aktualnej turze
	sf::Text tura_wiadomosc;

	/// Tablica unikalnych wskaznikow na kwadraty
	std::vector<std::unique_ptr<Pole>> kwadrat[2];

	/// Flaga informujaca, czy jest tura gracza 2
	bool gracz2_tura;

	/// Flaga informujaca o zakonczeniu gry
	bool koniec;

	/// STRZELANIE W STATKI
	/// 
	/// Funkcja odpowiedzialna za poprawne oddawanie strzalow w przeciwnika
	/// @param ruch Informacje o zdarzeniu klikniecia
	void strzelanie(sf::Event& ruch);

	/// LOGIKA ROZSTAWIANIA STATKOW
	/// 
	/// Funkcja odpowiedzialna za poprawne rozstawianie statkow na planszach
	/// @param ruch Informacje o zdarzeniu klikniecia
	void rozstawianie(sf::Event& ruch);

	/// ROZSTAWIANIE STATKOW
	/// 
	/// Funkcja odpowiedzialna za poprawne rozstawianie i zaznaczanie statkow na planszy 
	/// @param ruch Informacje o zdarzeniu klikniecia
	void rysowanie_i_stawianie(sf::Event& ruch);

	/// ZAPAMIETYWANIE PLANSZY
	/// 
	/// Funkcja sluzaca do zapamietywanie pozycji statkow z funkcji "rysowanie_i_stawianie"
	void rysowanie();

	/// INICJALIZACJA PLANSZY
	/// 
	/// Funkcja sluzaca do ustawiania odpowiednich wartosci na planszy przy kazdym uruchomieniu gry
	void ustawianie_planszy();

	/// WYKRYWANIE KOLIZJI
	/// 
	/// Funkcja sluzaca do wykrywania i zapisywania wspolrzednych klikniecia myszy w danym oknie
	/// @param okno Okno, w ktorym ma byc sprawdzana kolizja
	/// @param granice Granice obiektu
	/// @return True, jesli wystepuje kolizja, w przeciwnym razie false
	bool kolizja(sf::RenderWindow& okno, sf::FloatRect granice);

	/// KONIEC GRY POPRZEZ WYNIK
	/// 
	/// Funkcja odpowiedzialna za koniec gry, gdy dany gracz straci wszystkie swoje statki
	/// @param ruch Informacje o zdarzeniu klikniecia
	/// @return True, jesli gra powinna sie zakonczyc, w przeciwnym razie false
	bool koniec_gry_wynik(const sf::Event& ruch);

	/// KONIEC GRY POPRZEZ CZAS
	/// 
	/// Funkcja odpowiedzialna za koniec gry, gdy czas bedzie rowny 0
	/// @param ruch Informacje o zdarzeniu klikniecia
	/// @return True, jesli gra powinna sie zakonczyc, w przeciwnym razie false
	bool koniec_gry_czas(const sf::Event& ruch);
};
#endif

