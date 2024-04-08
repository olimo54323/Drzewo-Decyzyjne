/*********************************************************************
 * \file   struktury.h
 * \brief  Plik zawieraj�cy struktur� do programu decyzje
 * 
 * \author Grzegorz Urba�ski
 * \date   January 2023
 *********************************************************************/

#ifndef STRUKTURY_H

#define STRUKTURY_H

using namespace std;


/** Struktura okre�laj�ca budow� ga��zi drzewa binarnego
* \param d_id - numer ga��zi drzewa
* \param d_atrybut - atrybut warunku
* \param d_znak - znak warunku
* \param d_wartosc - wartosc warunku
* \param d_tak - indeks wyj�cia tak
* \param d_nie - indeks wyj�cia nie
*/
struct decyzja
{
	int d_id;
	string d_atrybut;
	string d_znak;
	float d_wartosc;
	string d_tak;
	string d_nie;
};

#endif // !STRUCTURES_H