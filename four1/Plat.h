/**
 * 	@file 	Figure.h
 *
 *	@author Jean-Baptiste Saillan
 *
 *  @date 	15 mai 2019
 *
 *  @brief 	Fichier d'entete de la classe Plat
 */
#ifndef PLAT_H
#define PLAT_H

#include "Date.h"


/**
 * @class Porte
 * @brief Classe representant la porte du four
 */
class Plat {

public:

	/**
	 * @fn Plat()
	 * @brief Constructeur par défaut de la classe Plat
	 * @param tempsCuisson Le temps de cuisson de base nécessaire
	 * @param temperature La temperature de cuisson
     */
	Plat(Date tempsCuisson, float temperature);

	/**
	 * @fn setTempsRestant()
	 * @brief Actualise le temps restant pour la cuisson du plat
	 * @param t Le nouveau temps à enregistrer
     */
	void setTempsRestant(Date t);

	/**
	 * @fn getTempsRestant()
	 * @brief Donne le temps restant pour la cuisson du plat
	 * @return Temps restant
     */
	Date getTempsRestant();

  /**
   * @fn getTempsInitial()
   * @brief Donne le temps initial pour la cuisson du plat
   * @return Temps initial
     */
  Date getTempsInitial();

private:

	Date m_tempsRestant; //<! Temps restant pour la cuisson
	Date m_tempsInitial; //<! Temps de bas pour la cuisson
	float m_temperatureCuisson; //<! Temperature encessaire pour cuire le plat

};




#endif
