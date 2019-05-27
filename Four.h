/**
 * 	@file 	Figure.h
 *
 *	@author Jean-Baptiste Saillan
 *
 *  @date 	15 mai 2019
 *
 *  @brief 	Fichier d'entete de la classe Four
 */
#ifndef FOUR_H
#define FOUR_H

#include <ESP8266WiFi.h>

#include <list>

#include "Date.h"
#include "Plat.h"
#include "Porte.h"

//Constantes pour le calcul de température
#define COEFF_B 4275
#define COEFF_R0 100000


/**
 * @class Four
 * @brief Classe représentant le four
 */
class Four {

public:

	/**
	 * @fn Four()
	 * @brief Constructeur par défaut de la classe Four
	 */
	Four();

	/**
	 * @fn ~Four()
	 * @brief Destructeur de la classe Four
	 */
	//~Four();

	/**
	 * @fn Init()
	 * @brief Initialise les pins nécessaires
	 */
	void init();

	/**
	 * @fn setTemperatureFour()
	 * @brief Actualise la temperature consigne du four
	 * @param temp Temperature consigne choisie
	 */
	void setTemperatureFour(float temp);

	/**
	 * @fn getTemperatureFour()
	 * @brief Renvoie la derniere temperature mesuree
	 * @return Derniere temperature mesuree
	 */
	float getTemperatureFour();

	/**
	 * @fn mesureTemperature()
	 * @brief Mesure la temperature actuelle et l'enregistre
	 */
	void mesureTemperature();

   /**
   * @fn getDerniereTemperature()
   * @brief Renvoie la dernière température mesurée
   */
  float getDerniereTemperature();

	/**
	 * @fn sendTemperature()
	 * @brief Envoie la temperature sur le serveur
	 */
	void sendTemperature();

	/**
	 * @fn allume()
	 * @brief Allume le four
	 */
	void allume();

	/**
	 * @fn getTemperatureFour()
	 * @brief Eteint le four
	 */
	void eteint();

	/**
	 * @fn getTemperatureFour()
	 * @brief Met un plat dans le four
	 * @param plat Plat à mettre dans le four
	 */
	void setPlat(Plat const& plat);

	Porte * m_porte; //<! Variable de classe pointant vers la porte
  
private:
	float m_temperatureConsigne; //<! Variable de classe contenant la consigne
	bool m_etat; //<! Variable de classe indiquant l'etat allume/eteint du four
	Plat * m_plat; //<! Variable de classe pointant sur le plat dans le four
  std::list<float> m_temperaturesMesurees; //<! Variable de classe enregistrant les mesures
	int m_capteurTemperaturePin; //<! Variable de classe donnant la pin du capteur de temperature
	int m_ledEtat; //<! Variable de classe donnant la pin de la LED d'etat
	int m_ledTemperature; //<! Variable de classe donnant la pin de la LED de temperature
	int m_valeurConsigneLed; //<! Variable de classe donnant la consigne de luminosité
};



#endif
