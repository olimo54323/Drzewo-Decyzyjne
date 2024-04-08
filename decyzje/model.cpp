#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>

#include "model.h"
#include "widok.h"
#include "struktury.h"


bool czy_liczba(const string& wyraz)
{
	for (int i = 0; i < wyraz.size(); i++)
	{
		if (!isdigit(wyraz[i]) and wyraz[i] != '.')																										//czy znak nie jest cyfra lub .
		{
			return false;
		}
	}
	return true;
}


bool czy_liczba_naturalna(const string& wyraz)
{
	for (int i = 0; i < wyraz.size(); i++)
	{
		if (!isdigit(wyraz[i]))																																	//czy znak nie jest cyfra
		{
			return false;
		}
	}
	return true;
}


void przypisywanie_do_drzewa(vector<decyzja>& drzewo, string* tablica, const int& linia)
{
	drzewo.at(linia).d_id = stoi(tablica[0]);																											//wpisywanie wartosci do wektora																													
	dzielenie_warunku(drzewo.at(linia), tablica[1]);																							
	drzewo.at(linia).d_tak = tablica[2];
	drzewo.at(linia).d_nie = tablica[3];
}


void przypisywanie_do_warunku(vector<vector<float>>& przypadki, vector<float>& wiersz)
{
	przypadki.push_back(wiersz);																														//wypchanie wektora pomocniczego do wektora wektorow
	wiersz.clear();																																					//czyszczenie wektora pomocniczego do ilosci liczb
}


void dzielenie_warunku(decyzja& obiekt, string& warunek)																			
{
	string s_separator_1 = "<";																																//operatory logiczne
	string s_separator_2 = ">=";																							
	int i_separator_1 = s_separator_1.length();																									//dlugosci operatorow logicznych
	int i_separator_2 = s_separator_2.length();									

	if (warunek.find(s_separator_1) != string::npos)																							//jezeli separator_1 jest znaloziony w tekscie warunku galezi
	{
		obiekt.d_atrybut = warunek.substr(0, warunek.find(s_separator_1));														//do d_atrybut wpisz atrybut warunku
		obiekt.d_znak = s_separator_1;																													//znak
		obiekt.d_wartosc = stof(warunek.substr(warunek.find(s_separator_1) + i_separator_1, warunek.npos));	//wartosc
	}
	else																																									//jezeli separator_1 nie jest znaleziony
	{
		obiekt.d_atrybut = warunek.substr(0, warunek.find(s_separator_2));														//do d_atrybut wpisz atrybut warunku
		obiekt.d_znak = s_separator_2;																													//znak
		obiekt.d_wartosc = stof(warunek.substr(warunek.find(s_separator_2) + i_separator_2, warunek.npos));	//wartosc

	}
}


void generowanie_pliku_wyjscia(unordered_map<string, vector<vector<float>>>& mapa, ofstream& wyjscie)
{
	for (const auto& etykieta : mapa)
	{
		wyjscie << etykieta.first << endl;																													//wyswietlanie etykiety

		for (const auto& wiersz : etykieta.second)																								//wyswietlanie przypadkow
		{
			for (const auto& wartosc_wiersza : wiersz)
			{
				wyjscie << wartosc_wiersza << " ";
			}
			wyjscie << endl;
		}
		wyjscie << endl;
	}
}


bool warunek_galezi(int nr_przypadku, int nr_galezi, int nr_war_atrybutu, const vector<vector<float>>& przypadek, const vector<decyzja>& drzewo)
{
	if (drzewo.at(nr_galezi).d_znak == "<")																											//jezeli operatorem warunkowym jest <
	{
		if (przypadek[nr_przypadku].at(nr_war_atrybutu) < drzewo.at(nr_galezi).d_wartosc)							//jezeli warunek galezi jest spelniony
		{
			return true;
		}
		else																																								//jezeli warunek galezi jest nie spelniony
		{
			return false;
		}
	}
	else																																									//jezeli operatorem jest >=
	{
		if (przypadek[nr_przypadku].at(nr_war_atrybutu) >= drzewo.at(nr_galezi).d_wartosc)							//jezeli warunek galezi jest spelniony
		{
			return true;
		}
		else																																								//jezeli warunek galezi jest nie spelniony
		{
			return false;
		}
	}
}


void dodawanie_do_mapy(unordered_map<string, vector<vector<float>>>& mapa, const string& klucz, const vector<float>& przypadki)
{
	if (mapa.find(klucz) == mapa.end())																												//jezeli nie ma takiego klucza 
	{
		vector<vector<float>> tablica;																														//stwórz wektor pomocniczy
		tablica.push_back(przypadki);																													
		mapa.emplace(klucz, tablica);																													//stworz taki klucz oraz dodaj do niego tabele;
	}
	else
	{
		mapa[klucz].push_back(przypadki);																											//dodaj na koniec wartosci mapy kolejny przypadek
	}
}


int postepowanie_drzewa(int nr_galezi, const int nr_przypadku, const vector<decyzja>& drzewo, const vector<string>& atrybut, const vector<vector<float>>& przypadek, unordered_map<string, vector<vector<float>>>& przyporzadkowane_przypadki)
{
	for (int i = 0; i < atrybut.size(); i++)
	{
		if (atrybut.at(i) != drzewo.at(nr_galezi).d_atrybut)																						//jezeli nazwa atrybutu nie zgadza sie z atrybutem warunku galezi przejdz do nastepnego kroku petli
		{
			continue;
		}

		if (warunek_galezi(nr_przypadku, nr_galezi, i, przypadek, drzewo))														//jezeli warunek galezi sie zgadza
		{
			if (czy_liczba(drzewo[nr_galezi].d_tak))																								//sprawdzamy czy "indeks wejscia tak'" jest liczba - kolejna galaz
			{
				postepowanie_drzewa(stoi(drzewo[nr_galezi].d_tak), nr_przypadku, drzewo, atrybut, przypadek, przyporzadkowane_przypadki);
			}
			else if (czy_liczba(drzewo[nr_galezi].d_tak) and stoi(drzewo[nr_galezi].d_tak) > drzewo.size())	//OBS£UGA B£ÊDÓW: sprawdzenie, czy warunek wyjscia tak jest na liscie galezi
			{
				cerr << "w ga³êzi " << nr_galezi << " w <indeksie wyjœcia tak> nast¹pi³o odwo³anie do nieistniej¹cej ga³êzi" << stoi(drzewo[nr_galezi].d_tak) << endl;
				return 13;
			}
			else																																							//jesli nie - wpisujemy do nieuporzadkowanej mapy
			{
				dodawanie_do_mapy(przyporzadkowane_przypadki, drzewo[nr_galezi].d_tak, przypadek[nr_przypadku]);
				return 0;
			}
		}
		else																																								//jezeli warunek galezi sie nie zgadza
		{
			if (czy_liczba(drzewo[nr_galezi].d_nie))																									//sprawdzamy czy "indeks wejscia nie'" jest liczba -kolejna galaz
			{
				postepowanie_drzewa(stoi(drzewo[nr_galezi].d_nie), nr_przypadku, drzewo, atrybut, przypadek, przyporzadkowane_przypadki);
			}
			else if (czy_liczba(drzewo[nr_galezi].d_nie) and stoi(drzewo[nr_galezi].d_nie) > drzewo.size())		//OBS£UGA B£ÊDÓW: sprawdzenie, czy warunek wyjscia tak jest na liscie galezi
			{
				cerr << "w ga³êzi " << nr_galezi << " w <indeksie wyjœcia nie> nast¹pi³o odwo³anie do nieistniej¹cej ga³êzi: " << stoi(drzewo[nr_galezi].d_nie) << endl;
				return 13;
			}
			else																																							//jesli nie - wpisujemy do nieuporzadkowanej mapy
			{
				dodawanie_do_mapy(przyporzadkowane_przypadki, drzewo[nr_galezi].d_nie, przypadek[nr_przypadku]);
				return 0;
			}
		}
	}
	return 0;
}