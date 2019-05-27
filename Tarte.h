/**
 * 	@file 	Figure.h
 *
 *	@author Jean-Baptiste Saillan
 *
 *  @date 	15 mai 2019
 *
 *  @brief 	Fichier d'entete de la classe Tarte
 */
#ifndef TARTE_H
#define TARTE_H


/**
 * @class Tarte
 * @brief Classe representant la porte du four
 */
class Tarte : public Plat{

public:

	/**
	 * @fn Tarte()
	 * @brief Constructeur par défaut de la classe Tarte
     */
	Tarte();


private:

	float m_surface; //<! Surface de notre tarte
	//+ le type de tarte

};




#endif