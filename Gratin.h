/**
 * 	@file 	Figure.h
 *
 *	@author Jérémy Turi & Jean-Baptiste Saillan
 *
 *  @date 	15 mai 2019
 *
 *  @brief 	Fichier d'entete de la classe Gratin
 */
#ifndef GRATIN_H
#define GRATIN_H

#include "Date.h"


/**
 * @class Gratin
 * @brief Classe representant un gratin
 */
class Gratin : public Plat{

public:

	/**
	 * @fn Gratin()
	 * @brief Constructeur par défaut de la classe Gratin
   * @param hauteur La hauteur du gratin à enfourner 
   * 
   * La température de cuisson est fixe. Le temps dépend de la hauteur.
   */
	Gratin(int hauteur) : Plat(Date(0, 5)*hauteur, 230) , m_hauteur(hauteur)  {
	};

  /**
   * @fn getHauteur()
   * @brief assesseur de l'attribut hauteur
   * @return La hauteur du gratin
   */
  int getHauteur() {
    return m_hauteur;
  }

  /**
   * @fn setHauteur()
   * @brief assesseur de l'attribut hauteur
   * @param hauteur La hauteur à enregistrer
   */
  void setHauteur(int hauteur) {
    if(hauteur >= 0) m_hauteur = hauteur;
  }

private:

	int m_hauteur; //!< Hauteur de notre gratin

};




#endif
