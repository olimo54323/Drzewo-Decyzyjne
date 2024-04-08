/*********************************************************************
 * \file   struktury.h
 * \brief  Plik zawieraj¹cy strukturê do programu decyzje
 * 
 * \author Grzegorz Urbañski
 * \date   January 2023
 *********************************************************************/

#ifndef STRUKTURY_H

#define STRUKTURY_H

using namespace std;


/** Struktura okreœlaj¹ca budowê ga³êzi drzewa binarnego
* \param d_id - numer ga³êzi drzewa
* \param d_atrybut - atrybut warunku
* \param d_znak - znak warunku
* \param d_wartosc - wartosc warunku
* \param d_tak - indeks wyjœcia tak
* \param d_nie - indeks wyjœcia nie
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