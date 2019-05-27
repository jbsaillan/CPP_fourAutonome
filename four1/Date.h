/**
 * 	@file 	Figure.h
 *
 *	@author Jean-Baptiste Saillan
 *
 *  @date 	15 mai 2019
 *
 *  @brief 	Fichier d'entete de la classe Date
 */
#ifndef DATE_H
#define DATE_H


/**
 * @class Date
 * @brief Classe representant une date
 */
class Date {

public:

	/**
	 * @fn Date()
	 * @brief Constructeur par défaut de la classe Date
     */
	Date(int h, int m) {
		m_minutes = m;
		m_heures = h;
	};


  /**
   * @fn operator*()
   * @brief On surcharge l'operation d emultiplication avec un entier
     */
  Date operator*(int x) {
    int j = 0;
    //On multiplie les minutes
    m_minutes = x*m_minutes;
    //Si ca depasse 60, on calcule le nombre d'heures associees
    j = m_minutes / 60;
    m_minutes = m_minutes % 60;
    //On calcule le nombre d'heures
    m_heures = x*m_heures + j;
  };


  /**
   * @fn operator-()
   * @brief On surcharge l'operation de soustraction avec des millisecondes
   */
  Date operator-(const int& milli) {
    int heures = milli/(1000*3600);
    int minutes = (milli - heures*(1000*3600))/(1000*60);

    m_minutes = m_minutes - minutes;
    if(m_minutes < 0) {
      m_heures -= 1; 
      m_minutes = 60 + m_minutes;
    }
    m_heures -= heures;  
  };

//private:

	int m_minutes; //<! Nombre de minutes
	int m_heures; //<! Nombre d'heures

};




#endif
