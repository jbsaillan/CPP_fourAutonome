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
	m_pinServoMoteur(PIN_SERVO),
  m_pinOuverture(PIN_OUVERTURE),
  m_servoMoteur(new Servo())
{
}

void Porte::init() {
  //Initialisation du servomoteur
  m_servoMoteur->attach(m_pinServoMoteur);
}


void Porte::ouvrePorte() {
  //On ouvre la porte
	m_servoMoteur->write(30);
}

void Porte::fermePorte() {
  //On ferme la porte
	m_servoMoteur->write(150);
}

bool Porte::getOuverture() {
  m_etatOuverture = !digitalRead(m_pinOuverture); //1 il y a qqch 0 il y a rien
  return m_etatOuverture;
}
