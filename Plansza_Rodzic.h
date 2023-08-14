#pragma once
/** @file */

#ifndef PLANSZA_RODZIC
#define PLANSZA_RODZIC
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <windows.h>
#include <iomanip>
#include <sstream>
#include <vector>
#include "Przycisk.h"
#include "Inne.h"

/// KLASA REPREZENTUJACA PLANSZE BAZOWA
/// 
/// Klasa Plansza_Rodzic dziedziczy po klasie Inne
/// Sluzy do dziedziczenia zawartosci klasy przez klasy pochodne
class Plansza_Rodzic : public Inne
{
public:

	/// DOMYSLNY KONSTRUKTOR KLASY PLANSZA_RODZIC
	Plansza_Rodzic() = default;

	/// DOMYSLNY DESTRUKTOR KLASY PLANSZA_RODZIC
	~Plansza_Rodzic() = default;

	/// WYPISYWANIE STATUSU PLANSZY
	/// 
	/// Operator wyjscia sluzacy do wypisywania statusu danej planszy 
	/// @param os Strumien wyjscia, do ktorego ma byc wypisany stan planszy
	/// @param plansza Obiekt klasy Plansza_Rodzic do wypisania
	/// @return os, czyli wynik referencja do strumienia wyjscia os
	friend std::ostream& operator<<(std::ostream& os, const Plansza_Rodzic& plansza);

	/// WYSWIETLANIE CZASU GRY
	/// 
	/// Funkcja sluzaca do wyswietlania czasu potrzebnego do konca gry na planszach
	/// @param zegar Obiekt sf::Clock do mierzenia czasu
	/// @param czas_tekst Tekst wyswietlajacy czas
	/// @param okno Okno renderowania
	void wysietlanie_czasu(sf::Clock& zegar, sf::Text& czas_tekst, sf::RenderWindow& okno);

	/// Tekst wskazujacy polecenie dla zawodnika
	sf::Text tekst_polecenie; 

	/// Tekst wskazujacy ilosc statkow gracza
	sf::Text tekst_status_twoje;

	/// Tekst wskazujacy ilosc statkow wroga
	sf::Text tekst_status_wrogie;

	/// Tekst wskazujacy ilosc statkow gracza pod koniec gry
	sf::Text twoje_koniec;

	/// Tekst wskazujacy ilosc statkow wroga pod koniec gry
	sf::Text wrogie_koniec;

	/// Tekst wskazujacy ilosc spudlowan gracza pod koniec gry
	sf::Text pudlo1;

	/// Tekst wskazujacy ilosc spudlowan wroga pod koniec gry
	sf::Text pudlo2;

	/// Tekst wskazujacy czas potrzebny do konca gry
	static sf::Text czas;

	/// Kolo na gornym obszarze pola
	sf::CircleShape kolo_gora;

	/// Kolo na dolnym obszarze pola
	sf::CircleShape kolo_dol;

	/// Ksztalt planszy
	sf::RectangleShape ksztalt;

	/// Liczba klikniec w kwadrat potrzebna do logiki gry
	int ilosc_klikniec_kwadrat = 0;

	/// Brakujacy czas w sekundach potrzebny do mierzenia czasu
	int brakujacy_czas_sekundy = 0;

	/// Tablica przechowujaca ilocs spudlowan graczy
	static int pudlo[2];

	/// Suma statkow na planszach
	static int suma_statkow;

	/// Tablica przechowujaca liczbe statkow dla obu graczy
	static int liczba_statkow_plansza[2];

	/// Wartosc pomocnicza odpowiedzialna za zatrzymanie klikania na planszach
	static int wartownik;
};
#endif
