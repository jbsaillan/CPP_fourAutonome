/**
 * 	@file 	Figure.h
 *
 *	@author Jérémy Turi & Jean-Baptiste Saillan
 *
 *  @date 	15 mai 2019
 *
 *  @brief 	Fichier d'entete de la classe Tarte
 */
#ifndef TARTE_H
#define TARTE_H

#include "Date.h"

/**
 * @class Tarte
 * @brief Classe representant la porte du four
 */
class Tarte : public Plat{

public:

	/**
	 * @fn Tarte()
	 * @brief Constructeur par défaut de la classe Tarte
   * @param surface La surface de la tarte à enfourner
   * 
   * La température de cuisson est fixe. Le temps dépend de la surface.
   */
	Tarte(int surface) : Plat(Date(0,5)*surface, 220), m_surface(surface) {
	};

 /**
   * @fn getSurface()
   * @brief Assesseur de l'attribut surface
   * @return La surface de la tarte
   */
  int getSurface() {
    return m_surface;
  }

  /**
   * @fn setSurface()
   * @brief assesseur de l'attribut surface
   * @param La surface à enregistrer
   */
  void setSurface(int surface) {
    if(surface >= 0) m_surface = surface;
  }


private:

	int m_surface; //!< Surface de la tarte


};




#endif
