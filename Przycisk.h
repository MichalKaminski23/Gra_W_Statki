#pragma once
/** @file */

#ifndef PRZYCISK 
#define PRZYCISK
#include <SFML/Graphics.hpp>
#include "Rysowanie.h"
#include "Inne.h"

/// KLASA REPREZENTUJACA INTERAKTYWNY PRZYCISK
/// 
/// Klasa Przycisk dziedziczy po klasie Rysowanie
/// Sluzy do tworzenia interaktywnych przyciskow w grze
class Przycisk : public Rysowanie
{
public:

    /// KONSTRUKTOR KLASY PRZYCISK
    /// 
    /// Konstruktor przyjmuje piec argumentow i tworzy obiekt
    /// @param pozycja Polozenie przycisku
    /// @param szerokosc Szerokosc przycisku
    /// @param wysokosc Wysokosc przycisku
    /// @param kolor_podstawa Kolor przycisku w stanie podstawowym
    /// @param kolor_zakrycie Kolor przycisku w stanie po najechaniu
    Przycisk(const sf::Vector2f& pozycja, float szerokosc, float wysokosc, const sf::Color& kolor_podstawa, const sf::Color& kolor_zakrycie);

    /// DOMYSLNY KONSTRUKTOR KLASY PRZYCISK
    Przycisk() = delete;

    /// DOMYSLNY DESTRUKTOR KLASY PRZYCISK
    ~Przycisk() = default;

    /// USTAWIANIE TEKSTU W PRZYCISKU
    /// 
    /// Funkcja sluzaca do ustawiania odpowiedniej pozycji tekstu
    /// @param napis Tekst do wyswietlenia na przycisku
    /// @param x Wspolrzedna x pozycji tekstu
    /// @param y Wspolrzedna y pozycji tekstu
    void ustaw_tekst(const std::string& napis, float x, float y);

    /// KLIKANIE W PRZYCISK
    /// 
    /// Funkcja sluzaca do obslugi klikniec w przycisk
    /// @param ruch Informacje o zdarzeniu klikniecia    
    /// @param okno Okno renderowania
    void klik(const sf::Event& ruch, sf::RenderWindow& okno);

    /// RYSOWANIE OBIEKTOW
    /// 
    /// Funkcja jest odpowiedzialna za poprawne wyswietlanie przyciskow
    /// @param cel Cel renderowania
    /// @param status Status renderowania
    void draw(sf::RenderTarget& cel, sf::RenderStates status) const override;

    /// SPRAWDZANIE KLIKNIECIA
    /// 
    /// Funkcja sluzaca do sprawdzania, czy przycisk zostal klikniety
    /// @return True, jesli przycisk zostal klikniety, w przeciwnym razie false
    bool czy_byl_klikniety() const;

    /// Informacja, czy przycisk zostal klikniety
    bool klikniecie{ false };

private:

    /// Ksztalt przycisku
    sf::RectangleShape ksztalt; 

    /// Kolor przycisku w stanie podstawowym
    sf::Color kolor_podstawa;

    /// Kolor przycisku po najechaniu
    sf::Color kolor_zakrycie;

    /// Tekst wyswietlany na przycisku
    sf::Text tekst;
};
#endif



