/**
 * @file 	Plat.cpp
 *
 * @date 	Created on: 19 may 2019
 *
 * @author  Jean-Baptiste Saillan
 *
 * @brief Fichier source de la classe Plat
 */
#include "Plat.h"


Plat::Plat(Date tempsCuisson, float temperature) : 
	m_tempsRestant(tempsCuisson), 
	m_tempsInitial(tempsCuisson),
	m_temperatureCuisson(temperature)
{
	//Il faut définir tout ça suivant les types
}


void Plat::setTempsRestant(Date t) {
	//on actualise le temps de cuisson restant
}

Date Plat::getTempsRestant() {
	return m_tempsRestant;
}

Date Plat::getTempsInitial() {
  return m_tempsInitial;
}
