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

#include <list>




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
	 * @fn measureTemperature()
	 * @brief Mesure la temperature actuelle et l'enregistre
	 */
	void measureTemperature();

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
	void setPlat(const& Plat plat);

private:
	float m_temperatureConsigne; //<! Variable de classe contenant la consigne
	list<float> m_temperaturesMesurees; //<! Variable de classe enregistrant les mesures
	bool m_etat; //<! Variable de classe indiquant l'etat allume/eteint du four

	Plat * m_plat; //<! Variable de classe pointant sur le plat dans le four
	Porte * m_porte; //<! Variable de classe pintant vers la porte

	int m_capteurTemperaturePin; //<! Variable de classe donnant la pin du capteur de temperature
	int m_ledEtat; //<! Variable de classe donnant la pin de la LED d'etat
	int m_ledTemperature; //<! Variable de classe donnant la pin de la LED de temperature
};



#endif
