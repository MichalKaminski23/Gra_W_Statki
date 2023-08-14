#pragma once
/** @file */

#ifndef INNE 
#define INNE
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>

/// KLASA REPREZENTUJACA INNE FUNKCJE
/// 
/// Klasa Inne sluzy do uladnienia kodu
class Inne
{
public:

	/// DOMYSLNY KONSTRUKTOR KLASY INNE
	Inne() = default;

	/// DOMYSLNY DESTRUKTOR KLASY INNE
	~Inne() = default;
	
	/// Czcionka uzywana w projekcie
	static sf::Font czcionka;

	/// CZCIONKA
	/// 
	/// Ladowanie wybranej czcionki
	static void czcionka_laduj();

	/// TEKST NA EKRANIE
	/// 
	/// Funkcja sluzaca do wyswietlania odpowiedniego tekstu na ekranie
	/// @param x Wspolrzedna x pozycji tekstu
	/// @param y Wspolrzedna y pozycji tekstu
	/// @param rozmiar Rozmiar czcionki
	/// @param grubosc Grubosc czcionki
	/// @param napis Tekst do wyswietlenia
	/// @param kolor Kolor tekstu
	/// @param grubosci_kolor Kolor obramowania tekstu
	/// @param tekst Obiekt do renderowania tekstu
	/// @param styl Styl tekstu
	/// @param okno Okno renderowania
	void pisanie_na_ekranie(int x, int y, int rozmiar, int grubosc, const std::string& napis, sf::Color kolor, sf::Color grubosci_kolor, sf::Text tekst, sf::Text::Style styl, sf::RenderWindow& okno);

	/// OBRAZY NA EKRANIE
	/// 
	/// Funkcja sluzaca do wyswietlania odpowiedniego obrazu na ekranie
	/// @param x Wspolrzedna x pozycji obrazka
	/// @param y Wspolrzedna y pozycji obrazka
	/// @param sciezka Sciezka do pliku obrazka
	/// @param okno Okno renderowania
	void obrazki_na_ekranie(int x, int y, const std::string& sciezka, sf::RenderWindow& okno);

	/// WIELE TEKSTU NA EKRANIE
	/// 
	/// Funkcja sluzaca do wyswietlania odpowiedniego tekstu na ekranie w duzej ilosci
	/// @param okno Okno renderowania
	/// @param gracz Nazwa gracza
	/// @param kolorek Kolor tekstu
	void mnogosc_pisan_na_ekranie(sf::RenderWindow& okno, const std::string& gracz, sf::Color kolorek);
};
#endif
