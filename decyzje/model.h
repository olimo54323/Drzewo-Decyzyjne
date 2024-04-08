/*********************************************************************
 * \file   model.h
 * \brief  Plik nag��wkowy zawieraj�cy definicje pliku model.cpp
 * 
 * \author Grzegorz Urba�ski
 * \date   January 2023
 *********************************************************************/

#ifndef MODEL_H

#define MODEL_H

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <unordered_map>

#include "struktury.h"
#include "widok.h"


/**
* \brief Funkcja sprawdzaj�ca czy ci�g wyraz�w to liczba zmiennoprzecinkowa
* \param wyraz - ciag znak�w, kt�ry ma zosta� sprawdzony
* \return true - je�li wyraz jest liczb�
* \return false - je�li wyraz nie jest liczb�
*/
bool czy_liczba(const string& wyraz);


/**
* \brief Procedura sprawdzajaca czy ci�g znak�w to liczba naturalna
* \param wyraz - ci�g znak�w, kt�ry ma zosta� sprawdzony
* \return true - je�li wyraz jest liczb�
* \return false - je�li wyraz nie jest liczb�
*/
bool czy_liczba_naturalna(const string& wyraz);


/**
* \brief Procedura wpisuj�ca dane do drzewa
* \param drzewo - wektor struktur przechowuj�cy <numer ga��zi> <warunek> <warto�� je�li tak> <warto�� je�li nie>
* \param *tablica - tablica pomocnicza do wpisywania danych do struktury
* \param linia - numer ga��zi
* \return -
*/
void przypisywanie_do_drzewa(vector <decyzja>& drzewo, string* tablica, const int& linia);


/**
* \brief Procedura wpisuj�ca dane do wektora wektor�w przypadk�w
* \param przypadki - wektor wektor�w przechowuj�cy warto�ci atrybut�w przypadk�w
* \param wiersz - wektor pomocniczy do wpisywania danych do wektora wektor�w
*/
void przypisywanie_do_warunku(vector<vector<float>>& przypadki, vector<float>& wiersz);


/**
* \brief Procedura zmieniaj�ca ci�g znak�w warunku na pola struktury
* \param obiekt - obiekt wektora struktur, do kt�rego wpisywane s� warto�ci
* \param warunek - ci�g znak�w warunku, pobrane z pliku tekstowego
* \return -
*/
void dzielenie_warunku(decyzja& obiekt, string& warunek);


/**
* \brief Procedura generuj�ca plik wyj�ciowy z mapy asocjacyjnej
* \param mapa - mapa asocjacyjna, z kt�rej wpisywane sa wektory przypadk�w
* \param wyjscie - strumie� wyj�cia pliku tekstowego
* \return -
*/
void generowanie_pliku_wyjscia(unordered_map<string, vector<vector<float>>>& mapa, ofstream& wyjscie);


/**
* \brief Funkcja sprawdzaj�ca warunek ga��zi drzewa z atrybutem przypadku
* \param nr_przypadku - indeks wektora, sprawdzanego przypadku
* \param nr_galezi - indeks ga��zi, kt�rej warunek jest rozpatrywany
* \param przypadek - wektor przechowuj�cy wektor warto�ci atrybut�w przypadku
* \param drzewo - wektor struktur przechowyj�cy warunki ga��zi
* \return true - je�li warunek jest spe�niony
* \return false -  je�li warunek nie jest spe�niony
*/
bool warunek_galezi(int nr_przypadku, int nr_galezi, int nr_war_atrybutu, const vector<vector<float>>& przypadek, const vector<decyzja>& drzewo);


/**
* \brief Procedura wpisuj�ca wektor przypadku do mapy asocjacyjnej
* \param mapa - mapa asocjacyjna, do kt�rej wpisywane sa wektory przypadk�w
* \param klucz - klucz mapy asocjacyjnej
* \param przpadki - wektor warto�ci przypadku, kt�ry jest wpisywany do mapy
* \return -
*/
void dodawanie_do_mapy(unordered_map<string, vector<vector<float>>>& mapa, const string& klucz, const vector<float>& przypadki);


/**
* \brief Funkcja poruszania si� programu po drzewie decyzyjnym
* \param nr_galezi - indeks ga��zi, kt�rej warunek jest rozpatrywany
* \param nr_przypadku - indeks wektora, sprawdzanego przypadku
* \param drzewo - wektor struktur zawieraj�cy drzewo decyzyjne
* \param atrybut - wektor atrybut�w, z kt�rym por�wnywany jest atrybut warunku ga��zi drzewa
* \param przypadek - wektor przechowuj�cy wektor warto�ci atrybut�w przypadku
* \param przyporzadkowane_przypadki - mapa asocjacyjna zawieraj�ca jako klucz odpowiednie etykiety, a jako warto�� wektor wektor�w przechowuj�cy przypadki
* \return 0 - gdy brak b��d�w
* \return 13 - gdy podano nieprawid�owe dane
*/
int postepowanie_drzewa(int nr_galezi, const int nr_przypadku, const vector<decyzja>& drzewo, const vector<string>& atrybut, const vector<vector<float>>& przypadek, unordered_map<string, vector<vector<float>>>& przyporzadkowane_przypadki);

#endif // !MODEL_H

