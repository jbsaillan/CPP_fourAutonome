/**
 * 	@file 	Figure.h
 *
 *	@author Jean-Baptiste Saillan
 *
 *  @date 	15 mai 2019
 *
 *  @brief 	Fichier d'entete de la classe Viande
 */
#ifndef VIANDE_H
#define VIANDE_H

#include "Date.h"

/**
 * @class Viande
 * @brief Classe representant un plat de type viande
 */
class Viande : public Plat{

public:

	/**
	 * @fn Viande()
	 * @brief Constructeur par défaut de la classe Viande
     */
	Viande(int poids) : Plat(Date(1, 2), 180) {
	  m_poids = poids;
	};


private:

	int m_poids; //<! Poids du morceau de viande

};




#endif
