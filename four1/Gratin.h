/**
 * 	@file 	Figure.h
 *
 *	@author Jean-Baptiste Saillan
 *
 *  @date 	15 mai 2019
 *
 *  @brief 	Fichier d'entete de la classe Gratin
 */
#ifndef GRATIN_H
#define GRATIN_H

#include "Date.h"


/**
 * @class Gratin
 * @brief Classe representant un gratin
 */
class Gratin : public Plat{

public:

	/**
	 * @fn Gratin()
	 * @brief Constructeur par défaut de la classe Gratin
     */
	Gratin(int hauteur) : Plat(Date(1, 2), 280) {
	  m_hauteur = hauteur;
	};

private:

	int m_hauteur; //<! Hauteur de notre gratin
	//+ le type de tarte

};




#endif
