// NOTE Driver Windows : http://en.doit.am/CH341SER.zip

#include <Arduino.h>

/*
// Explications sur la structure du code Arduino
// Les fonctions setup() et loop(), équivalent à :

  void main() {
    setup();
    while (1) {
      loop();
    }
  }

*/

// Définition du pinout de la demoboard
// Entrée analogique
#define A0                    0
// Entrée/Sortie numérique
#define D0                    16
#define D1                    5
#define D2                    4
#define D3                    0
#define D4                    2
#define D5                    14
#define D6                    12
#define D7                    13
#define D8                    15

// NOTE : Installer la bibliothèque Adafruit Unified Sensor Library: https://github.com/adafruit/Adafruit_Sensor
#include <Adafruit_Sensor.h>
// NOTE : Installer la bibliothèque DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
#include <DHT.h>
#include <DHT_U.h>

#define LED_EXTERN            D0

#define DHTPIN                D1         // Pin which is connected to the DHT sensor.
#define DHTTYPE               DHT11      // DHT 11

// Initialisation du capteur de température & humidité
DHT_Unified DHT_SENSOR(DHTPIN, DHTTYPE);

// Fonction executée lors du démarrage de la carte
void setup() {
  // Initialisation de la communication série pour les retours de texte
  DEBUG_ESP_PORT.begin(115200);

  // Mise en SORTIE de la pin D0
  pinMode(LED_EXTERN, OUTPUT);

  // Initialisation du capteur de température & humidité
  DHT_SENSOR.begin();
  DEBUG_ESP_PORT.println("DHTxx Unified Sensor Example");

  // Print temperature sensor details.
  sensor_t sensor;
  DHT_SENSOR.temperature().getSensor(&sensor);
  DEBUG_ESP_PORT.println("------------------------------------");
  DEBUG_ESP_PORT.println("Temperature");
  DEBUG_ESP_PORT.print  ("Sensor:       "); DEBUG_ESP_PORT.println(sensor.name);
  DEBUG_ESP_PORT.print  ("Driver Ver:   "); DEBUG_ESP_PORT.println(sensor.version);
  DEBUG_ESP_PORT.print  ("Unique ID:    "); DEBUG_ESP_PORT.println(sensor.sensor_id);
  DEBUG_ESP_PORT.print  ("Max Value:    "); DEBUG_ESP_PORT.print(sensor.max_value); DEBUG_ESP_PORT.println(" *C");
  DEBUG_ESP_PORT.print  ("Min Value:    "); DEBUG_ESP_PORT.print(sensor.min_value); DEBUG_ESP_PORT.println(" *C");
  DEBUG_ESP_PORT.print  ("Resolution:   "); DEBUG_ESP_PORT.print(sensor.resolution); DEBUG_ESP_PORT.println(" *C");
  DEBUG_ESP_PORT.println("------------------------------------");
  // Print humidity sensor details.
  DHT_SENSOR.humidity().getSensor(&sensor);
  DEBUG_ESP_PORT.println("------------------------------------");
  DEBUG_ESP_PORT.println("Humidity");
  DEBUG_ESP_PORT.print  ("Sensor:       "); DEBUG_ESP_PORT.println(sensor.name);
  DEBUG_ESP_PORT.print  ("Driver Ver:   "); DEBUG_ESP_PORT.println(sensor.version);
  DEBUG_ESP_PORT.print  ("Unique ID:    "); DEBUG_ESP_PORT.println(sensor.sensor_id);
  DEBUG_ESP_PORT.print  ("Max Value:    "); DEBUG_ESP_PORT.print(sensor.max_value); DEBUG_ESP_PORT.println("%");
  DEBUG_ESP_PORT.print  ("Min Value:    "); DEBUG_ESP_PORT.print(sensor.min_value); DEBUG_ESP_PORT.println("%");
  DEBUG_ESP_PORT.print  ("Resolution:   "); DEBUG_ESP_PORT.print(sensor.resolution); DEBUG_ESP_PORT.println("%");
  DEBUG_ESP_PORT.println("------------------------------------");
}

void loop() {
  DEBUG_ESP_PORT.printf("Loop!\n");

  // Pause de 2 secondes
  delay(2000);

  // Mise à l'état HAUT de la LED (elle s'eteint!)
  digitalWrite(LED_EXTERN, HIGH);

  // Get temperature event and print its value.
  sensors_event_t event;
  DHT_SENSOR.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    DEBUG_ESP_PORT.println("Error reading temperature!");
  } else {
    DEBUG_ESP_PORT.print("Temperature: ");
    DEBUG_ESP_PORT.print(event.temperature);
    DEBUG_ESP_PORT.println(" *C");
  }

  // Get humidity event and print its value.
  DHT_SENSOR.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    DEBUG_ESP_PORT.println("Error reading humidity!");
  } else {
    DEBUG_ESP_PORT.print("Humidity: ");
    DEBUG_ESP_PORT.print(event.relative_humidity);
    DEBUG_ESP_PORT.println("%");
  }

  // Mise à l'état BAS de la LED (elle s'allume!)
  digitalWrite(LED_EXTERN, LOW);
}
