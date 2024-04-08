/*********************************************************************
 * \file   funkcje.h
 * \brief  Plik nag³ówkowy zawieraj¹cy definicje pliku widok.cpp
 * 
 * \author Grzegorz Urbañski
 * \date   January 2023
 *********************************************************************/

#ifndef FUNKCJE_H

#define FUNKCJE_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "struktury.h"
#include "model.h"
	

/** Funkcja sprawdzaj¹ca otwarcie i poprawnoœæ odczytu pliku
* \param wejscie - czytany plik tekstowy
* \return true - je¿eli plik jest dobry
* \return false - je¿eli jest problem z odczytem
*/
bool poprawnosc_odczytu(ifstream& wejscie);


/** Funkcja czytaj¹ca i wpisuj¹ca do programu zawartoœæ pliku drzewa
* \param drzewo - wektor struktur przechowuj¹cy <numer ga³êzi> <warunek> <wartoœæ jeœli tak> <wartoœæ jeœli nie>
* \param wejscie - czytany plik tekstowy z architektur¹ drzewa
* \return 0 - gdy brak b³êdów
* \return 13 - gdy podano nieprawid³owe dane
*/
int czytanie_pliku_warunkowego(vector<decyzja>& drzewo, ifstream& wejscie);


/** Funkcja czytaj¹ca i wpisuj¹ca do programu zawartoœæ pliku wejœciowego
* \param atrybut - wektor przechowuj¹cy nazwy atrybutów
* \param przypadki - wektor wartoœci atrybutów danego przypadku
* \param wejscie - czytany plik tekstowy przypadków
* \return 0 - gdy brak b³êdów
* \return 13 - gdy podano nieprawid³owe dane
*/
int czytanie_pliku_atrybutu(vector<string>& atrybut, vector<vector<float>>& przypadki, ifstream& wejscie);

#endif // !DECISION_H