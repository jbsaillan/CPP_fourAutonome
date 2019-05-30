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
  m_tempsRestant.m_heures=t.m_heures;
  m_tempsRestant.m_minutes=t.m_minutes;
}

Date Plat::getTempsRestant() {
	return m_tempsRestant;
}

Date Plat::getTempsInitial() {
  return m_tempsInitial;
}

int Plat::getTempsRestantMinutes()
{
  return m_tempsRestant.m_heures*60+m_tempsRestant.m_minutes;
}

int  Plat::getTemperatureCuisson()
{
  return m_temperatureCuisson;
}
