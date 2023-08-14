#pragma once
/** @file */

#ifndef POLE 
#define POLE
#include "Plansza_Rodzic.h"
#include "Rysowanie.h"
#include <SFML/Graphics.hpp>

/// KLASA REPREZENTUJACA POJEDYNCZE POLE NA PLANSZY
/// 
/// Klasa Pole dziedziczy po klasach Plansza_Rodzic i Rysowanie
/// Sluzy do reprezentowania pojedynczego pola na planszy gry
class Pole : public Plansza_Rodzic, public Rysowanie
{
public:

    /// KONSTRUKTOR KLASY POLE
    /// 
    /// Konstruktor przyjmuje cztery argumenty i tworzy obiekt
    /// @param x Okresla poczatkowa pozycje pojedynczego pola
    /// @param y Okresla poczatkowa pozycje pojedynczego pola
    /// @param szerokosc Okresla rozmiar pojedynczego pola
    /// @param wysokosc Okresla rozmiar pojedynczego pola
    Pole(float x, float y, float szerokosc, float wysokosc);

    /// DOMYSLNY KONSTRUKTOR KLASY POLE
    Pole() = default;

    /// DOMYSLNY DESTRUKTOR KLASY POLE
    ~Pole() = default;
    
    /// RYSOWANIE KOLA NA PLANSZY U GORY
    /// 
    /// Funkcja odpowiedzialna za odpowiednie ustawianie danych kol na planszy
    /// @param kolor Ustawia odpowiedni kolor w danej sytuacji (trafienie, pudlo)
    void rysuj_kolo_gora(const sf::Color& kolor);

    /// RYSOWANIE KOLA NA PLANSZY U DOLU
    /// 
    /// Funkcja odpowiedzialna za odpowiednie ustawianie danych kol na planszy
    /// @param kolor Ustawia odpowiedni kolor w danej sytuacji (trafienie, pudlo)
    void rysuj_kolo_dol(const sf::Color& kolor);

    /// RYSOWANIE OBIEKTOW
    /// 
    /// Funkcja jest odpowiedzialna za poprawne wyswietlanie obiektow na planszy
    /// @param cel Cel renderowania
    /// @param status Status renderowania
    virtual void draw(sf::RenderTarget& cel, sf::RenderStates status) const override;
};
#endif







