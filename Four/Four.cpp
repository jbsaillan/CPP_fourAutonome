/**
 * @file 	Four.cpp
 *
 * @date 	Created on: 19 may 2019
 *
 * @author  Jean-Baptiste Saillan
 *
 * @brief Fichier source de la classe Four.
 */
#include "Four.h"
#include "../CONSTANTES.h"


//Constructeur par défaut
Four::Four() : 
	m_temperatureConsigne(T_AMBIANT),
	m_etat(false),
	m_plat(NULL),
	m_porte(new Porte()),
	m_capteurTemperaturePin(PIN_CAPTEUR_TEMPERATURE),
	m_ledEtat(PIN_LED_ETAT),
	m_ledTemperature(PIN_LED_TEMPERATURE)
{
}


void Four::setTemperatureFour(float temp) {
	//Si la T° consigne est supérieure à celle ambiante, on l'actualise
	temp > T_AMBIANT ? m_temperatureConsigne = temp : m_temperatureConsigne = T_AMBIANT;
}

float Four::getTemperatureFour() {
	return m_temperatureConsigne;
}

void Four::mesureTemperature() {
	//On mesure une temperature
	//A actualiser suivant la manière dont se place le capteur
}

void Four::sendTemperature() {
	//On evoie une mesure au serveur
}

void Four::allume() {
	//On allume le four
}

void Four::eteint() {
	//On eteint le four
}

void Four::setPlat(Plat const& plat) {
	//On stocke le plat
}

