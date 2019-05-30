//gauchard@laas.fr

//Bibliothèques "arduino" nécessaires
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

//Bibliothèques std
#include <list>

//Bibliothèques perso
#include "CONSTANTES.h"
#include "Four.h"
#include "Plat.h"

//Defines pour la connection
#define WIFI_SSID "DoomKiller98"
#define WIFI_PASS "ImBatman"
#define MQTT_SERV "io.adafruit.com"
#define MQTT_PORT 1883
#define MQTT_NAME "jeje98751"
#define MQTT_PASS "f4c77673e5404361aef1640152463e40"

//Set up MQTT and WiFi clients
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERV, MQTT_PORT, MQTT_NAME, MQTT_PASS);
//Set up the feed you're subscribing to
Adafruit_MQTT_Subscribe onoff = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/smartoven-feed.oven-onoff");
Adafruit_MQTT_Subscribe recevoirPlats = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/smartoven-feed.plat");
//On creer le feed auquel envoyer des données
Adafruit_MQTT_Publish listTemp = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/smartoven-feed.temperature-observed");


/**
 * Creation four (avec porte)
 * 
 * Variables mqt patati patata
 *  connexion wifi
 *  
 */
 bool sendTemp = false;

 Four * monFour = new Four();


void setup() {
   Serial.begin(9600);

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

   delay(500);
   //On initialise le four
   monFour->init(); 
}



void loop() {

  
  MQTT_connect();
  
    //On récupere les data relatives au on/off
    Adafruit_MQTT_Subscribe * subscription;
    while ((subscription = mqtt.readSubscription(2000)))
    {
       if (subscription == &recevoirPlats) {
        //Print the new value to the serial monitor
        String plat = (char*) recevoirPlats.lastread;
        //On met le string en minuscule
        std::transform(plat.begin(), plat.end(), plat.begin(), ::tolower);

        Serial.print("Recevoir Plats: ");
        Serial.println(plat);
        
        monFour->setPlat(plat);
      }

      
      //If we're in here, a subscription updated...
      if (subscription == &onoff) {
        //Print the new value to the serial monitor
        Serial.print("onoff: ");
        Serial.println((char*) onoff.lastread);
        
        //If the new value is  "ON", turn the light on.
        //Otherwise, turn it off.
        if (!strcmp((char*) onoff.lastread, "ON"))
        {
          monFour->allume();
        }
        else
        {
          monFour->eteint();
        }
      }
    }

    //On envoie les donnees sur la temperature
    monFour->mesureTemperature();
    if(listTemp.publish(monFour->getTemperatureFour())) {
        Serial.println("Temp sent !");
    } else {
        Serial.println("Failed to send temp");
    }


    //Le four joue son rôle
    monFour->routine();




}



/*
 * Fonction spéciale MQTT
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
