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
	Gratin();


private:

	float m_hauteur; //<! Hauteur de notre gratin
	//+ le type de tarte

};




#endif