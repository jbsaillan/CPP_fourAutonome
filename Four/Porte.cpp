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
#include "../CONSTANTES.h"

Porte::Porte() :
	m_etatOuverture(false),
	m_servoMoteur(PIN_SERVO)
{
}


void ouvrePorte() {
	//On ouvre la porte du four
}

void fermePorte() {
	//On ferme la porte du four
}