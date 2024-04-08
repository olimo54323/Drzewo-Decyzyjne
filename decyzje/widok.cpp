#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <iostream>

#include "widok.h"
#include "model.h"
#include "struktury.h"


bool poprawnosc_odczytu(ifstream &wejscie)
{
	if (!wejscie.is_open())
	{
		cerr << "nie zostal otwarty ";
		return false;
	}

	if (!wejscie.good())
	{
		cerr << "blad odczytu ma ";
		return false;
	}
	return true;
}


int czytanie_pliku_warunkowego(vector<decyzja>&drzewo, ifstream &wejscie)
{
	int i_linia = 0;																																	//zmienna do numeru linii; do wektora wektorow
	int i_wyraz = 0;																																//zmienna pomocnicza dla tablicy ciagu znakow
	string s_linia;																																	//zmienna dla ustalenia hierarchii drzewa			
	string s_wyraz;																																//zmienna pomocnicza do wpisywania wyrazu w wektor
	string s_tablica[4];																															//tablica pomocnicza do wpisywania fragmentow linii do wektora struktur

	if (!poprawnosc_odczytu(wejscie))
	{
		cerr << "plik drzewa" << endl;
		return 13;
	}

	while (getline(wejscie, s_linia))																									//czytanie pliku
	{											
		string s_linia_bez_dodatkowych_spacji;

		for (int i = 0; i < s_linia.size(); i++)																							//OBSLUGA BLEDOW: usuwanie dodatkowych spacji
		{
			if (s_linia[i] != ' ' or (s_linia[i] == ' ' and s_linia_bez_dodatkowych_spacji.back() != ' '))
			{
				s_linia_bez_dodatkowych_spacji += s_linia[i];
			}
		}

		stringstream ss_objekt_bez_dodatkowych_spacji(s_linia_bez_dodatkowych_spacji);
		
		while (getline(ss_objekt_bez_dodatkowych_spacji, s_wyraz, ' '))											//podzielenie linii na s³owa			
		{
			if (s_wyraz == "%" or s_wyraz[0] == '%')
			{
				break;
			}

			s_tablica[i_wyraz] = s_wyraz;
			i_wyraz++;
		}
		
		if (!czy_liczba_naturalna(s_tablica[0]))																					//OBSLUGA BLEDOW:	sprawdzenie czy numer galezi jest liczba naturalna
		{
			cerr << "w pliku drzewa, w linii " << i_linia + 1 << " wartosc numeru galezi nie jest liczba: " << s_tablica[0] << endl;
			return 13;	 
		}

		drzewo.push_back(decyzja());																								
		przypisywanie_do_drzewa(drzewo, s_tablica, i_linia);															//wpisanie danych z pliku do wektora struktur

		i_wyraz = 0;
		i_linia++;
	}
	return 0;
}


int czytanie_pliku_atrybutu(vector<string>& atrybut, vector<vector<float>>&przypadki, ifstream& wejscie)
{
	int i_linia = 0;																																//zmienna do numeru linii; do wektora wektorow
	string s_linia;																																//zmienna dla popbrania linii z pliku	
	string s_wyraz;																															//zmienna pomocnicza do wpisywania wyrazu w wektor
	vector<float>f_wiersz;																													//wektor do wypychania zmiennych do wektora wektorow

	if (!poprawnosc_odczytu(wejscie))
	{
		cerr << "plik wejsciowy" << endl;
		return 13;
	}

	while (getline(wejscie, s_linia))
	{
		string s_linia_bez_dodatkowych_spacji;

		for (int i = 0; i < s_linia.size(); i++)																								//OBSLUGA BLEDOW: usuwanie dodatkowych spacji
		{
			if (s_linia[i] != ' ' or (s_linia[i] == ' ' and s_linia_bez_dodatkowych_spacji.back() != ' '))
			{
				s_linia_bez_dodatkowych_spacji += s_linia[i];
			}
		}

		stringstream ss_objekt_bez_dodatkowych_spacji(s_linia_bez_dodatkowych_spacji);

		if (i_linia == 0)																																//jezeli to 0. linia to czyta atrybuty 
		{
			while (getline(ss_objekt_bez_dodatkowych_spacji, s_wyraz, ' ') )										//jezeli jest co czytac	
			{
				if (s_wyraz == "%" or s_wyraz[0] == '%')
				{
					break;
				}
				atrybut.push_back(s_wyraz);
			}
		}
		else																																				//jezeli to inna linia to czyta przypadki
		{
			while (getline(ss_objekt_bez_dodatkowych_spacji, s_wyraz, ' '))											// jezeli jest co czytac
			{
				if (s_wyraz == "%" or s_wyraz[0] == '%')
				{
					break;
				}

				if (czy_liczba(s_wyraz))																										//OBSLUGA BLEDOW: sprawdzenie, czy wartosc jest liczba
				{
					f_wiersz.push_back(stod(s_wyraz));																				//wpisywanie w pomocniczego wektora rzutowanych na float stringow
				}
				else
				{
					cerr << "w pliku wejsciowym, w linii " << i_linia + 1 << " zostala wprowadzona zlego typu wartosc: "<< s_wyraz << endl;
					return 13;
				}
			}

			if (atrybut.size() != f_wiersz.size())																						//OBSLUGA BLEDOW: jezeli ilosc atrybutow nie zgadza sie z iloscia wartosci atrybutow
			{
				cerr << "w pliku wejsciowym, liczba wartosci atrybutow w linijce " << i_linia + 1 << " jest niezgodna z iloscia atrybutow: " << f_wiersz.size() << " != " << atrybut.size() << endl;
				return 13;
			}
			przypisywanie_do_warunku(przypadki, f_wiersz);
		}
		i_linia++;
	}
	return 0;
}
