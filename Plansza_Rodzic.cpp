#include "Plansza_Rodzic.h"
using namespace sf;


int Plansza_Rodzic::liczba_statkow_plansza[2] = { 0,0 };
int Plansza_Rodzic::pudlo[2] = { 0,0 };
int Plansza_Rodzic::suma_statkow = 0;
int Plansza_Rodzic::wartownik = 0;
Text Plansza_Rodzic::czas{};

std::ostream& operator<<(std::ostream& os, const Plansza_Rodzic& plansza) 
{
	os << "**********************************" << std::endl;
	os << "Stan gry:" << std::endl;
	os << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
	os << "Liczba statkow gracza 1:   " << plansza.liczba_statkow_plansza[0] << std::endl;
	os << "Liczba spudlowan gracza 1: " << plansza.pudlo[0] << std::endl;
	os << "----------------------------------" << std::endl;
	os << "Liczba statkow gracza 2:   " << plansza.liczba_statkow_plansza[1] << std::endl;
	os << "Liczba spudlowan gracza 2: " << plansza.pudlo[1] << std::endl;
	os << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;

	if (Plansza_Rodzic::suma_statkow != 40)
	{
	os << "Suma statkow na planszach: " << plansza.suma_statkow << std::endl;
	}

	os << "**********************************" << std::endl;
	return os;

	//Operator << jest przeci¹¿any aby mo¿na by³o go u¿ywaæ w sposób podobny do 
	//standardowego wypisywania za pomoc¹ strumienia std::ostream
	//std::ostream & -Zwracany typ strumienia. Pozwala na ³añcuchowe wywo³anie wielu operacji na strumieniu.
	//os - Referencja do strumienia, na którym chcemy wykonaæ wypisanie.
	
}

void Plansza_Rodzic::wysietlanie_czasu(Clock& zegar, Text& czas_tekst, RenderWindow& okno)
{
	int czas_gry = 600; // Czas gry w sekundach (10 minut)

	Time uplyw_czasu = zegar.getElapsedTime(); 	// Pobieramy czas od rozpoczêcia odliczania
	
	brakujacy_czas_sekundy = czas_gry - static_cast<int>(uplyw_czasu.asSeconds());	// Obliczamy pozosta³y czas w sekundach
	//static_cast<int> jest operatorem rzutowania(konwersji typu) w jêzyku C++.S³u¿y do jawnej zmiany typu zmiennej na inny typ.
	//static_cast<int> jest u¿ywany do rzutowania wyniku funkcji uplyw_czasu.asSeconds() na typ int.

	if (brakujacy_czas_sekundy < 0)
	{
		czas_tekst.setPosition(840, 185);
		czas_tekst.setStyle(Text::Bold);
		czas_tekst.setFillColor(Color::Red);
		czas_tekst.setString("KONIEC GRY");
		tekst_polecenie.setString(" ");
		okno.draw(tekst_polecenie);
		tekst_status_twoje.setString(" ");
		okno.draw(tekst_status_twoje);
		tekst_status_wrogie.setString(" ");
		okno.draw(tekst_status_wrogie);
		Plansza_Rodzic::wartownik = 1;
	}
	else
	{
		// Przekszta³camy czas na format mm:ss
		int minuty = brakujacy_czas_sekundy / 60;
		int sekundy = brakujacy_czas_sekundy % 60;

		//std::ostringstream jest u¿ywany do konwersji liczby na ³añcuch znaków w odpowiednim formacie.
		//Manipulatory std::setw(2) i std::setfill('0') ustawiaj¹ minimaln¹ szerokoœæ pola na 2 i wype³niaj¹ pole zerami wiod¹cymi, 
		//jeœli liczba jest krótsza ni¿ 2 cyfry. Dziêki temu czas bêdzie wypisany w formacie "mm:ss" z odpowiednimi zerami wiod¹cymi.
		std::ostringstream ladny_tekst;
		ladny_tekst << std::setw(2) << std::setfill('0') << minuty << ":" << std::setw(2) << std::setfill('0') << sekundy;
		czas_tekst.setString(ladny_tekst.str());

		Text czasX;
		pisanie_na_ekranie(841, 150, 30, 0, "Koniec gry za", Color::Black, Color::Transparent, czasX, Text::Style::Regular, okno);
	}
}

