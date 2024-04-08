/*********************************************************************
 * \file   model.h
 * \brief  Plik nag³ówkowy zawieraj¹cy definicje pliku model.cpp
 * 
 * \author Grzegorz Urbañski
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
* \brief Funkcja sprawdzaj¹ca czy ci¹g wyrazów to liczba zmiennoprzecinkowa
* \param wyraz - ciag znaków, który ma zostaæ sprawdzony
* \return true - jeœli wyraz jest liczb¹
* \return false - jeœli wyraz nie jest liczb¹
*/
bool czy_liczba(const string& wyraz);


/**
* \brief Procedura sprawdzajaca czy ci¹g znaków to liczba naturalna
* \param wyraz - ci¹g znaków, który ma zostaæ sprawdzony
* \return true - jeœli wyraz jest liczb¹
* \return false - jeœli wyraz nie jest liczb¹
*/
bool czy_liczba_naturalna(const string& wyraz);


/**
* \brief Procedura wpisuj¹ca dane do drzewa
* \param drzewo - wektor struktur przechowuj¹cy <numer ga³êzi> <warunek> <wartoœæ jeœli tak> <wartoœæ jeœli nie>
* \param *tablica - tablica pomocnicza do wpisywania danych do struktury
* \param linia - numer ga³êzi
* \return -
*/
void przypisywanie_do_drzewa(vector <decyzja>& drzewo, string* tablica, const int& linia);


/**
* \brief Procedura wpisuj¹ca dane do wektora wektorów przypadków
* \param przypadki - wektor wektorów przechowuj¹cy wartoœci atrybutów przypadków
* \param wiersz - wektor pomocniczy do wpisywania danych do wektora wektorów
*/
void przypisywanie_do_warunku(vector<vector<float>>& przypadki, vector<float>& wiersz);


/**
* \brief Procedura zmieniaj¹ca ci¹g znaków warunku na pola struktury
* \param obiekt - obiekt wektora struktur, do którego wpisywane s¹ wartoœci
* \param warunek - ci¹g znaków warunku, pobrane z pliku tekstowego
* \return -
*/
void dzielenie_warunku(decyzja& obiekt, string& warunek);


/**
* \brief Procedura generuj¹ca plik wyjœciowy z mapy asocjacyjnej
* \param mapa - mapa asocjacyjna, z której wpisywane sa wektory przypadków
* \param wyjscie - strumieñ wyjœcia pliku tekstowego
* \return -
*/
void generowanie_pliku_wyjscia(unordered_map<string, vector<vector<float>>>& mapa, ofstream& wyjscie);


/**
* \brief Funkcja sprawdzaj¹ca warunek ga³êzi drzewa z atrybutem przypadku
* \param nr_przypadku - indeks wektora, sprawdzanego przypadku
* \param nr_galezi - indeks ga³êzi, której warunek jest rozpatrywany
* \param przypadek - wektor przechowuj¹cy wektor wartoœci atrybutów przypadku
* \param drzewo - wektor struktur przechowyj¹cy warunki ga³êzi
* \return true - jeœli warunek jest spe³niony
* \return false -  jeœli warunek nie jest spe³niony
*/
bool warunek_galezi(int nr_przypadku, int nr_galezi, int nr_war_atrybutu, const vector<vector<float>>& przypadek, const vector<decyzja>& drzewo);


/**
* \brief Procedura wpisuj¹ca wektor przypadku do mapy asocjacyjnej
* \param mapa - mapa asocjacyjna, do której wpisywane sa wektory przypadków
* \param klucz - klucz mapy asocjacyjnej
* \param przpadki - wektor wartoœci przypadku, który jest wpisywany do mapy
* \return -
*/
void dodawanie_do_mapy(unordered_map<string, vector<vector<float>>>& mapa, const string& klucz, const vector<float>& przypadki);


/**
* \brief Funkcja poruszania siê programu po drzewie decyzyjnym
* \param nr_galezi - indeks ga³êzi, której warunek jest rozpatrywany
* \param nr_przypadku - indeks wektora, sprawdzanego przypadku
* \param drzewo - wektor struktur zawieraj¹cy drzewo decyzyjne
* \param atrybut - wektor atrybutów, z którym porównywany jest atrybut warunku ga³êzi drzewa
* \param przypadek - wektor przechowuj¹cy wektor wartoœci atrybutów przypadku
* \param przyporzadkowane_przypadki - mapa asocjacyjna zawieraj¹ca jako klucz odpowiednie etykiety, a jako wartoœæ wektor wektorów przechowuj¹cy przypadki
* \return 0 - gdy brak b³êdów
* \return 13 - gdy podano nieprawid³owe dane
*/
int postepowanie_drzewa(int nr_galezi, const int nr_przypadku, const vector<decyzja>& drzewo, const vector<string>& atrybut, const vector<vector<float>>& przypadek, unordered_map<string, vector<vector<float>>>& przyporzadkowane_przypadki);

#endif // !MODEL_H

