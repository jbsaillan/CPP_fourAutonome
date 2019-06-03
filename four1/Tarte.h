/**
 * 	@file 	Figure.h
 *
 *	@author Jean-Baptiste Saillan
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
     */
	Tarte(int surface) : Plat(Date(0,5)*surface, 220), m_surface(surface) {
	};

 /**
   * @fn getSurface()
   * @brief assesseur de l'attribut surface
     */
  int getSurface() {
    return m_surface;
  }

  /**
   * @fn setSurface()
   * @brief assesseur de l'attribut surface
     */
  void setSurface(int surface) {
    if(surface >= 0) m_surface = surface;
  }


private:

	int m_surface; //<! Surface de notre tarte


};




#endif
