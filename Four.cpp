/**
 * @file 	Four.cpp
 *
 * @date 	Created on: 19 may 2019
 *
 * @author  Jérémy Turi & Jean-Baptiste Saillan
 *
 * @brief Fichier source de la classe Four.
 */
#include "Four.h"
#include "CONSTANTES.h"

#include "Viande.h"
#include "Gratin.h"
#include "Tarte.h"

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
	m_previousTimeLED(0)
{
}

//Destructeur par défait
Four::~Four() {
  delete m_porte;
  delete m_plat;
}

void Four::init() {
	//On initialise les LEDs
	pinMode(m_ledTemperature, OUTPUT);
	pinMode(m_ledEtat, OUTPUT);
	digitalWrite(m_ledTemperature, LOW);
	digitalWrite(m_ledEtat, LOW);
  //On initialise la porte
  m_porte->init();
}


void Four::setTemperatureFour(float temp) {
	//Si la T° consigne est supérieure à celle ambiante, on l'actualise
	temp > T_AMBIANT ? m_temperatureConsigne = temp : m_temperatureConsigne = T_AMBIANT;
}

float Four::getTemperatureFour() {
  //Si on a mesuré des températures, on envoie la dernière lue
  if(m_temperaturesMesurees.size() > 0) {
	  return m_temperaturesMesurees.back();
  } else {
    return -1;
  }
}

bool Four::getEtat() {
  //On renvoie si le four est allumé ou non
  return m_etat;
}

void Four::mesureTemperature() {
	//On mesure une temperature en °C
  float R = 1023.0/analogRead(m_capteurTemperaturePin) -1.0;
  R = COEFF_R0 * R;
  float temp = 1.0/(log(R/(COEFF_R0))/(COEFF_B)+1/298.15)-273.15;
  //On stocke la température dans la liste
  m_temperaturesMesurees.push_back(temp);

  //On supprime les vieux éléments si la liste est trop grande
  if(m_temperaturesMesurees.size() > 100) m_temperaturesMesurees.pop_front();
}

//On renvoie la temperature consigne
float Four::getDerniereTemperatureConsigne() {
  return m_temperatureConsigne;
}


void Four::allume() {
	//On allume le four si la porte est fermée

  /**
  * A cause de la maquette, on ne considère pas le capteur d'ouverture qui empêche le four de démarrer
  */
  
  //if(m_porte->getOuverture()) {
      m_etat = true;
      digitalWrite(m_ledEtat, HIGH);
      Serial.println("Led allumée");
  /*} else {
    m_porte->fermePorte();
  }*/
}

void Four::eteint() {
	//On eteint le four
	m_etat = false;
	digitalWrite(m_ledEtat, LOW);
  //On ouvre la porte
  m_porte->ouvrePorte();
}

void Four::setPlat(String const& plat) {
  bool bonPlat = true;
  //Suivant le string passé ene entrée, on enfourne un plat (ce dernier doit être connu par le four) 
  if(plat == "poulet") {
    m_plat = new Viande(1);
  } else if(plat == "dinde") {
    m_plat = new Viande(3);
  } else if(plat == "boeuf") {
    m_plat = new Viande(2);
  } else if(plat == "croziflette") {
    m_plat = new Gratin(40);
  } else if(plat == "dauphinois") {
    m_plat = new Gratin(7);
  } else if(plat == "courgette") {
    m_plat = new Gratin(15);  
  } else if(plat == "tarte aux pommes") {
    m_plat = new Tarte(10);  
  } else if(plat == "tarte au chocolat") {
    m_plat = new Tarte(9);  
  } else if(plat == "tarte aux citrons") {
    m_plat = new Tarte(10); 
  } else {
    bonPlat = false;
  }
  //Si le plat était connu et enregistré, on allume le four
  if(bonPlat) {
    this->allume();
    this->setTemperatureFour(m_plat->getTemperatureCuisson());
    m_tempsDepart = millis();
  }
}


void Four::routine() {
  //On mesure une température
  mesureTemperature();
  
  //Quand le four est allumé
  if(m_etat) {
    //S'il y a un plat en train de cuire
    if(m_plat != NULL) {
      //On calcule le temps restant de cuisson
      Date tempsRestant = m_plat->getTempsInitial() - (millis()- m_tempsDepart);
      m_plat->setTempsRestant(tempsRestant);
  
      Serial.print(tempsRestant.m_heures);
      Serial.print(" : ");
      Serial.println(tempsRestant.m_minutes);

      //Si la cuisson est finie
      if(tempsRestant.m_heures <= 0 && tempsRestant.m_minutes <= 0) {
        //On eteint le four
        this->eteint();
      }
    }
  }
  
}


void Four::clignottementLED() {
  //Si le four est allumé
  if(m_etat) {
    //On calcule la periode du clignottement suivant la temperature
    int consigneClignottement = 100;
    if(m_temperatureConsigne < 80) {
      consigneClignottement = 20;
    } else if(m_temperatureConsigne < 150) {
      consigneClignottement = 5;
    } else if(m_temperatureConsigne < 400) {
      consigneClignottement = 1;
    }
    //Si la période est écoulée
    if(m_previousTimeLED > consigneClignottement) {
      //La LED change d'état
      m_previousTimeLED = 0;
      digitalWrite(m_ledTemperature, !digitalRead(m_ledTemperature));
    } else {
      m_previousTimeLED++;
    }

  }
}
