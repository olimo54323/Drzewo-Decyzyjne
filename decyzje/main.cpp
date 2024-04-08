#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <locale.h>

#include "model.h"
#include "widok.h"
#include "struktury.h"


int main(int argc, char* argv[])
{
	setlocale(LC_CTYPE, "Polish");

	string s_nazwa_warunku, s_nazwa_atrybutu, s_nazwa_wyjscia;						//zmienne nazw plikow tekstowych
	vector<decyzja> d_drzewo_decyzyjne;																//wektor drzewa decyzyjnego
	vector<string>s_atrybut;																						//wektor atrybutów
	vector<vector<float>>ff_przypadek;																	//wektor wektorów
	unordered_map <string, vector<vector<float>>>um_mapa_przypadkow;			//hashmapa dla przypadków
	int i_kod_drzewo, i_kod_wejscie, i_kod_rekurencja;											//kody b³êdów funkcji

	if (argc == 1)																											//jezeli brak przelacznikow 
	{
		cout << "Program dokonuj¹cy analizy zbioru danych z wykorzystaniem drzewa decyzyjnego;" << endl;
		cout << "Aby program zadzia³a³, wymagane jest podanie 3 prze³¹czników:\n-i -> nazwa pliku wejœciowego\n-t -> nazwa pliku drzewa\n-o -> nazwa pliku wyjœciowego" << endl;
		return 0;
	}

	if (argc != 1 and argc != 7)																					//jezeli nie ma wszystkich przelacznikow
	{
		cout << argc;
		cerr << "Liczba prze³¹czników jest niew³aœciwa" << endl;
		return 1;
	}

	for (int i = 1; i < argc; i += 2)
	{
		string s_przelacznik = argv[i];

		if (s_przelacznik == "-i")
		{
			if (i + 1 < argc)
				s_nazwa_atrybutu = argv[i + 1];
			else
				cerr << "prze³¹cznik -i wymaga podania nazwy pliku wejœciowego" << endl;
		}
		else if (s_przelacznik == "-t")
		{
			if (i + 1 < argc)
				s_nazwa_warunku = argv[i + 1];
			else
				cerr << "prze³¹cznik -t wymaga podania nazwy pliku drzewa" << endl;
		}
		else if (s_przelacznik == "-o")
		{
			if (i + 1 < argc)
				s_nazwa_wyjscia = argv[i + 1];
			else
				cerr << "prze³¹cznik -o wymaga podania nazwy pliku wyjœciowego" << endl;
		}
		else
		{
			cerr << "prze³¹cznik " << s_przelacznik << " nie jest obs³ugiwany" << endl;
			return 13;
		}
	}

	ifstream is_warunek(s_nazwa_warunku);
	ifstream is_atrybut(s_nazwa_atrybutu);
	ofstream os_wyjscie(s_nazwa_wyjscia);

	i_kod_drzewo = czytanie_pliku_warunkowego(d_drzewo_decyzyjne, is_warunek);
	if (i_kod_drzewo != 0)
	{
		return 13;
	}

	i_kod_wejscie = czytanie_pliku_atrybutu(s_atrybut, ff_przypadek, is_atrybut);
	if (i_kod_wejscie != 0)
	{
		return 13;
	}

	for (int i = 0; i < ff_przypadek.size(); i++)
	{
		i_kod_rekurencja = postepowanie_drzewa(0, i, d_drzewo_decyzyjne, s_atrybut, ff_przypadek, um_mapa_przypadkow);
		if (i_kod_rekurencja != 0)
		{
			return 13;
		}
	}

	generowanie_pliku_wyjscia(um_mapa_przypadkow, os_wyjscie);

	is_warunek.close();
	is_atrybut.close();
	os_wyjscie.close();
	return 0;
}
/*ZMIANY:
	1. dodanie plikow decision.h, decision.cpp, main.cpp
	2. dodanie struktury decyzja
	3. dodanie funkcji "blad_odczytu()", "czytanie_pliku_warunkowego()", "wypis()", "wpis()"
	4. dodanie pliku stdlibrary.h
	5. dodanie funkcji "czytanie_pliku_atrybutu"
	6. poprawki funkcji "czytanie_pliku_warunkowego()"
	7. poprawki funkcji "czytanie_pliku_atrubutu()"
	8. dodanie funkcji "wypis_wektora()", "wypis_wek_wektorow()"
	9. dodanie funkcji "czy_liczba()", "dzielenie_warunku()", "sprawdzanie_warunku()", "postepowanie_drzewa()"'
	10. dodanie pliku "struktury.h"
	11. zmiana nazwy funkcji "sprawdzanie_warunku()" na "warunek_galezi()"
	12. poprawki funkcji "postepowanie_drzewa()"
	13. poprawki funkcji "postepowanie_drzewa()", "warunek_galezi()"
	14. zmiana nazwy funkcji "blad_odczytu()" na "poprawnosc_odczytu()"
	15. dodanie funkcji "dodanie_do_mapy()"
	16. dodanie funkcji "generowanie_pliku_wyjsciowego()"
	17. dodanie obslugi przekaznikow
	18. dodanie obslugi polskich znakow diakrytycznych
	19. dodanie obslugi bledow
	20. poprawki funkcji
	21. poprawki pamieci
	22. poprawki funkcji
	23. dodanie funkcji
	24. zmiana nazw pliku funkcje.cpp/.h na widok.cpp/h
	25. wprowadzenie podzia³u na widok i model
*/