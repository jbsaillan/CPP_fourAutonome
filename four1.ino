//gauchard@laas.fr

//Bibliothèques "arduino" nécessaires
#include <ESP8266WiFi.h>
#include <Servo.h>
#include <Ticker.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

//Bibliothèques std
#include <list>
#include <string>

//Bibliothèques perso
#include "CONSTANTES.h"
#include "Four.h"
#include "Plat.h"

//Defines pour la connection
#define WIFI_SSID "hotspotjb"
#define WIFI_PASS "mdp110757"
#define MQTT_SERV "io.adafruit.com"
#define MQTT_PORT 1883
#define MQTT_NAME "jeje98751"
#define MQTT_PASS "f4c77673e5404361aef1640152463e40"

//Set up MQTT and WiFi clients
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERV, MQTT_PORT, MQTT_NAME, MQTT_PASS);

//Créations des feeds auxquels on s'abonne
Adafruit_MQTT_Subscribe onoff = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/smartoven-feed.oven-onoff");
Adafruit_MQTT_Subscribe recevoirPlats = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/smartoven-feed.plat");
Adafruit_MQTT_Subscribe recevoirTemperature = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/smartoven-feed.temperature-cible");

//Crétions des feeds auxquels on everra des données
//A noter que pour les data bidirectionnelles, on crée le "susbcribe" et le "publish"
Adafruit_MQTT_Publish listTemp = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/smartoven-feed.temperature-observed");
Adafruit_MQTT_Publish minuteur = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/smartoven-feed.minuteur");
Adafruit_MQTT_Publish temp_cible = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/smartoven-feed.temperature-cible");
Adafruit_MQTT_Publish p_onoff = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/smartoven-feed.oven-onoff");

//Objet ticker pour gérer le clignottement de la LED par interruption
Ticker blinker;

//Création de notre objet four
Four * monFour = new Four();


void setup() {
   Serial.begin(9600);
   
   Serial.println("Le capteur d'ouverture n'est pas utilisé pour l'allumage du four.\nVeuillez décommenter les lignes correspondantes dans le fichier Four.cpp");
   
   //Connect to WiFi
   Serial.print("\n\nConnecting Wifi... ");
   WiFi.begin(WIFI_SSID, WIFI_PASS);
   while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
   }
   Serial.println();
   Serial.println("WiFi connected");
   Serial.println("IP address: "); 
   Serial.println(WiFi.localIP());
  
   //Subscribe to the onoff feed
   mqtt.subscribe(&onoff);
   //Subscribe to the recevoirPlat feed
   mqtt.subscribe(&recevoirPlats);
   //Subscribe to the recevoirTemperature feed
   mqtt.subscribe(&recevoirTemperature);
   delay(500);
   
   //On initialise le four
   monFour->init();

   //On initialise le timer qui déclenche la fonction pour faire clignotter la LED
   blinker.attach(0.1, checkLEDFour);
}



void loop() {

  
    MQTT_connect();
  
    /*
     * On récupère, s'il y en a, les données venant de l'application web
     */
     
    Adafruit_MQTT_Subscribe * subscription;
    while ((subscription = mqtt.readSubscription(10000)))
    {
      
      //Si on reçoit une data concernant un plat à mettre au four
      if (subscription == &recevoirPlats) {
        
       //On met le string en minuscule
       String plat = (char*) recevoirPlats.lastread;
       std::transform(plat.begin(), plat.end(), plat.begin(), ::tolower);

       Serial.print("Recevoir Plats: ");
       Serial.println(plat);

       //On tente de mettre le plat dans le four
       //On tente ensuite d'allumer le four
       monFour->setPlat(plat); 
      }
      
      //Si on reçoit une data concernant l'allumage du four
      if (subscription == &onoff) {
        //On affiche la valeur reçue
        Serial.print("onoff: ");
        Serial.println((char*) onoff.lastread);
        
        //Si la valeur est ON, on allume le four
        //Si la valeur est OFF, on eteint le four
        if (!strcmp((char*) onoff.lastread, "ON")){
          //Attention, l'allumage peut aussi dépendre de l'etat de la porte du four
          monFour->allume();
        } else{
          monFour->eteint();
       }
      }
      
      //Si on reçoit une data concernant la temperature consigne du four
      if (subscription == &recevoirTemperature) {
        //On convertir la valeur reçue (string) en numérique (float)
        float tempRecue = (float)atof((char*)recevoirTemperature.lastread);
        Serial.print("Nouvelle temperature consigne: ");
        Serial.println(tempRecue);
        //On actualise la temperature consigne du four
        monFour->setTemperatureFour(tempRecue);
      }
      
    }


    /*
     * On simule le comportement du four
     */

    //Le four realise sa routine (mesure de temperature, decompte du temps de cuisson etc)
    monFour->routine();



    /*
     * On envoie à l'application web certaines données issues du four
     */
     
    //On envoie à l'pplication l'etat allumé/éteint du four
    //Cela est utile au cas où on veuille l'allumer mais que ce n'est pas possible (le bouton retourne en "off)
    char * etatFour = "OFF";
    if(monFour->m_porte->getOuverture()) etatFour = "ON";
    if(p_onoff.publish((char*)etatFour)){  
      Serial.println("Etat four sent !");
    } else {
      Serial.println("Failed to send etatFour");
    }
    
    //On envoie à l'application web la température réelle du four
    if(listTemp.publish(monFour->getTemperatureFour())) {
        Serial.println("Temp sent !");
    } else {
        Serial.println("Failed to send temp");
    }

    //S'il y a un plat, on envoie à l'application web le temps de cuisson restant
    if(monFour->m_plat != NULL) {
        if(minuteur.publish(monFour->m_plat->getTempsRestantMinutes())) {  
           Serial.println("Time sent !");
        } else {
           Serial.println("Failed to send time");
        }
    }
    
    //Envoie la temperature consigne elle est fixée par le plat dans le four ou directement par l'utilisateur
    if(temp_cible.publish(monFour->getDerniereTemperatureConsigne())) {  
      Serial.println("Temperature Consigne sent !");
    } else {
      Serial.println("Failed to send Temperature Consigne");
    }
    
    
}



//Fonction déclenchée sous interruption
void checkLEDFour() {
  //Permet d'assurer le clignottement de la LED 
  monFour->clignottementLED();
}



/*
 * Fonction spéciale MQTT
 * elle vient de l'exemple de code fourni
 */
void MQTT_connect() 
{
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) 
  {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) // connect will return 0 for connected
  { 
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) 
       {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
