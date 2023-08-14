#pragma once
/** @file */

#ifndef RYSOWANIE 
#define RYSOWANIE
#include <SFML/Graphics.hpp>

/// KLASA ABSTRAKCYJNA RYSOWANIE
/// 
/// Klasa abstrakcyjna definiujaca interfejs do rysowania obiektow
/// Dziedziczenie po sf::Drawable umozliwia renderowanie obiektow w oknie SFML
class Rysowanie : public sf::Drawable 
{
public:

	/// RYSOWANIE OBIEKTOW
	/// 
	/// Funkcja wirtualna jest odpowiedzialna za poprawne rysowanie obiektow
	/// @param cel Cel renderowania
	/// @param status Status renderowania
	virtual void draw(sf::RenderTarget& cel, sf::RenderStates status) const = 0;
};
#endif
