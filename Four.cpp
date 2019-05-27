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
#include "CONSTANTES.h"

#include <math.h>


//Constructeur par défaut
Four::Four() : 
	m_temperatureConsigne(T_AMBIANT),
	m_etat(false),
	m_plat(NULL),
	m_porte(new Porte()),
	m_capteurTemperaturePin(A0),
	m_ledEtat(PIN_LED_ETAT),
	m_ledTemperature(PIN_LED_TEMPERATURE),
	m_valeurConsigneLed(1023/2)
{
}

void Four::init() {
	//On initialise les LEDs
	pinMode(m_ledTemperature, OUTPUT);
	pinMode(m_ledEtat, OUTPUT);
	//digitalWrite(m_ledTemperature, LOW);
	digitalWrite(m_ledEtat, LOW);
}


void Four::setTemperatureFour(float temp) {
	//Si la T° consigne est supérieure à celle ambiante, on l'actualise
	temp > T_AMBIANT ? m_temperatureConsigne = temp : m_temperatureConsigne = T_AMBIANT;
}

float Four::getTemperatureFour() {
  if(m_temperaturesMesurees.size() > 0) {
	  return m_temperaturesMesurees.back();
  } else {
    return -1;
  }
}

void Four::mesureTemperature() {
	//On mesure une temperature
  float R = 1023.0/analogRead(m_capteurTemperaturePin) -1.0;
  R = COEFF_R0 * R;
  float temp = 1.0/(log(R/(COEFF_R0))/(COEFF_B)+1/298.15)-273.15;
  //On stocke la température
  m_temperaturesMesurees.push_back(temp);

  //On supprime les vieux éléments
  if(m_temperaturesMesurees.size() > 100) m_temperaturesMesurees.pop_front();
  
  //On actualise la luminosité de la led pour simuler la résistance
  if(temp < m_temperatureConsigne) {
  	m_valeurConsigneLed += 100;
  } else {
  	m_valeurConsigneLed -= 100;
  }
  if(m_valeurConsigneLed > 1023) m_valeurConsigneLed = 1023;
  if(m_valeurConsigneLed < 0 || !m_etat) m_valeurConsigneLed = 0;
  analogWrite(m_ledTemperature, m_valeurConsigneLed);
}


void Four::sendTemperature() {
	//On evoie une mesure au serveur
}

void Four::allume() {
	//On allume le four
  if(m_porte->getOuverture()) {
      m_etat = true;
      digitalWrite(m_ledEtat, HIGH);
  }
}

void Four::eteint() {
	//On eteint le four
	m_etat = false;
	digitalWrite(m_ledEtat, LOW);
}

void Four::setPlat(Plat const& plat) {
	//On stocke le plat
}
