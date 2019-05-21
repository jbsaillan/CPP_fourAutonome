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
	Viande();


private:

	float m_poids; //<! Poids du morceau de viande
	//+ le type de tarte

};




#endif