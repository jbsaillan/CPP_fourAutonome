//gauchard@laas.fr

#include <ESP8266WiFi.h>

#include <list>

#include "CONSTANTES.h"
#include "Four.h"
#include "Plat.h"


/**
 * Creation four (avec porte)
 * 
 * Variables mqt patati patata
 *  connexion wifi
 *  
 */

 Four * monFour = new Four();


void setup() {
  /*
   * Initialiser four et porte
   * 
   * Initialiser les connections
   *  wifi
   *  mqtt
   *  feed
   */
   monFour->init();

   Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  monFour->allume();
  delay(500);
  monFour->eteint();
  delay(500);

  bool a = monFour->m_porte->getOuverture();
  Serial.println(a);

}
