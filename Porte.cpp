/**
 * @file 	Porte.cpp
 *
 * @date 	Created on: 19 may 2019
 *
 * @author  Jean-Baptiste Saillan
 *
 * @brief Fichier source de la classe Porte.
 */

#include "Porte.h"
#include "CONSTANTES.h"

Porte::Porte() :
	m_etatOuverture(false),
	m_servoMoteur(PIN_SERVO),
  m_pinOuverture(PIN_OUVERTURE)
{
}


void Porte::ouvrePorte() {
	//On ouvre la porte du four
}

void Porte::fermePorte() {
	//On ferme la porte du four
}

bool Porte::getOuverture() {
  m_etatOuverture = !digitalRead(m_pinOuverture); //1 il y a qqch 0 il y a rien
  return m_etatOuverture;
}
