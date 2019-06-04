/**
 * 	@file 	Figure.h
 *
 *	@author Jérémy Turi & Jean-Baptiste Saillan
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

//Constantes pour la conversion de température en °C
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
	~Four();

	/**
	 * @fn init()
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
	 * @brief Renvoie la derniere temperature mesuree par le capteur de température
	 * @return Derniere temperature mesuree 
	 */
	float getTemperatureFour();

  /**
   * @fn getEtat()
   * @brief Renvoie l'etat allume/eteint du four
   * @return Dernier etat du four
   */
  bool getEtat();

	/**
	 * @fn mesureTemperature()
	 * @brief Mesure la temperature actuelle du four et l'enregistre
   * 
   * Mesure la temperature actuelle du four via le capteur et l'enregistre dans une liste de températures.
   * Si trop de températures sont enregistrées, on supprime les vieilles valeurs.
	 */
	void mesureTemperature();

   /**
   * @fn getDerniereTemperatureConsigne()
   * @brief Renvoie la dernière température consigne du four
   * @return Température consigne
   */
  float getDerniereTemperatureConsigne();

	/**
	 * @fn allume()
	 * @brief Allume le four
   * 
   * Allume le four si la porte est correctement fermée. 
   * A terme, le servomoteur fermera la porte tout seul si ce n'est pas déjà fait.
	 */
	void allume();

	/**
	 * @fn eteint()
	 * @brief Eteint le four
   * 
   * Eteint le four.*
   * A terme, le servomoteur ouvrira le four à la fin de la cuisson.
	 */
	void eteint();

	/**
	 * @fn getTemperatureFour()
	 * @brief Met un plat dans le four
	 * @param plat Nom du plat à mettre dans le four
   * 
   * On cherche à mettre un plat dans le four. 
   * Si ce dernier est connu, on allume le four pour entamer la cuisson.
	 */
	void setPlat(String const& plat);


    /**
   * @fn routine()
   * @brief Effectue les différentesmesures et actions du four.
   * 
   * On mesure et enregistre la température du four.
   * Si un plat est dans le four, on calcule le tempsd e cuisson restant.
   */
  void routine();

  /**
   * @fn clignottementLED()
   * @brief Déclenchée sous interruption, gère le clignottement de la LED suivant la température
   * 
   * Déclenchée sous interruption, gère le clignottement de la LED suivant la température.
   * Plus la température consigne est élevée, plus la fréquence est grande.
   */
  void clignottementLED();


	Porte * m_porte; //!< Variable de classe pointant vers la porte, cette dernière est publique car les méthodes de Porte sont sécurisées
  Plat * m_plat; //!< Variable de classe pointant sur le plat dans le four (pas d'acces privé car les accesseurs des plats sont déjà sécurisés)
  
private:
	float m_temperatureConsigne; //!< Variable de classe contenant la consigne de température
  std::list<float> m_temperaturesMesurees; //!< Variable de classe enregistrant les mesures de température
  
	bool m_etat; //!< Variable de classe indiquant l'etat allume/eteint du four

  int m_tempsDepart; //!< Variable de classe disant quand on a mis un plat au four
  
	int m_capteurTemperaturePin; //!< Variable de classe donnant la pin du capteur de temperature
	int m_ledEtat; //!< Variable de classe donnant la pin de la LED d'etat
	int m_ledTemperature; //!< Variable de classe donnant la pin de la LED de temperature

  int m_previousTimeLED; //!<Variable de classe permettant de gérer le clignottement de la LED de température
};



#endif
