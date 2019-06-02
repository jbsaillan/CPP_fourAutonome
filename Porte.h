/**
 * 	@file 	Porte.h
 *
 *	@author Jean-Baptiste Saillan
 *
 *  @date 	15 mai 2019
 *
 *  @brief 	Fichier d'entete de la classe Porte
 */
#ifndef PORTE_H
#define PORTE_H

#include <ESP8266WiFi.h>
#include <Servo.h>

/**
 * @class Porte
 * @brief Classe representant la porte du four
 */
class Porte{

public:

	/**
	 * @fn Porte()
	 * @brief Constructeur par défaut  de la classe Porte
     */
	Porte();

  /**
   * @fn init()
   * @brief Initialise la porte (notemment le servomoteur)
     */
  void init();

	/**
	 * @fn ouvrePorte()
	 * @brief Ouvre la porte du four s'il est eteint
     */
	void ouvrePorte();

	/**
	 * @fn fermePorte()
	 * @brief Ferme la porte du four
	 */
	void fermePorte();

  /**
   * @fn getOuverture()
   * @brief Detecte la position de la porte du four
   */
  bool getOuverture();

private:

	bool m_etatOuverture; //<! Variable de classe representant l'etat d'ouverture de la porte
	int m_pinServoMoteur; //<! Variable de classe avec la pin de controle du servomoteur
  Servo * m_servoMoteur; //<! Variable de classe représentant le servomoteur
  int m_pinOuverture; //<! variable de classe avec la pin du cateur d'ouverture

};

#endif
