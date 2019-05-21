/**
 * 	@file 	Figure.h
 *
 *	@author Jean-Baptiste Saillan
 *
 *  @date 	15 mai 2019
 *
 *  @brief 	Fichier d'entete de la classe Date
 */
#ifndef DATE_H
#define DATE_H


/**
 * @class Date
 * @brief Classe representant une date
 */
class Date {

public:

	/**
	 * @fn Date()
	 * @brief Constructeur par défaut de la classe Date
     */
	Date(int h, int m, int s) {
		m_secondes = s;
		m_minutes = m;
		m_heures = h;
	};

private:

	int m_secondes; //<! Nombre de secondes
	int m_minutes; //<! Nombre de minutes
	int m_heures; //<! Nombre d'heures

};




#endif