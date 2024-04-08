/*********************************************************************
 * \file   funkcje.h
 * \brief  Plik nag��wkowy zawieraj�cy definicje pliku widok.cpp
 * 
 * \author Grzegorz Urba�ski
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
	

/** Funkcja sprawdzaj�ca otwarcie i poprawno�� odczytu pliku
* \param wejscie - czytany plik tekstowy
* \return true - je�eli plik jest dobry
* \return false - je�eli jest problem z odczytem
*/
bool poprawnosc_odczytu(ifstream& wejscie);


/** Funkcja czytaj�ca i wpisuj�ca do programu zawarto�� pliku drzewa
* \param drzewo - wektor struktur przechowuj�cy <numer ga��zi> <warunek> <warto�� je�li tak> <warto�� je�li nie>
* \param wejscie - czytany plik tekstowy z architektur� drzewa
* \return 0 - gdy brak b��d�w
* \return 13 - gdy podano nieprawid�owe dane
*/
int czytanie_pliku_warunkowego(vector<decyzja>& drzewo, ifstream& wejscie);


/** Funkcja czytaj�ca i wpisuj�ca do programu zawarto�� pliku wej�ciowego
* \param atrybut - wektor przechowuj�cy nazwy atrybut�w
* \param przypadki - wektor warto�ci atrybut�w danego przypadku
* \param wejscie - czytany plik tekstowy przypadk�w
* \return 0 - gdy brak b��d�w
* \return 13 - gdy podano nieprawid�owe dane
*/
int czytanie_pliku_atrybutu(vector<string>& atrybut, vector<vector<float>>& przypadki, ifstream& wejscie);

#endif // !DECISION_H