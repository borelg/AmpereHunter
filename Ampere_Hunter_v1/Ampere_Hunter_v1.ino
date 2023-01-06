#include <Arduino.h>
#include <HX711.h>
#include "WiFiManager.h"
#include <WiFiClient.h>

#define SCALE_FACTOR  131.75 

#define OFFSET_TOT    1883 
#define OFFSET_uA     3.3

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 13;

HX711 scale;
float current_ua, raw_read;

WiFiClient client;
const char* server = "xxxxxxxxxx"; // INSERT YOUR IP
const int port = 9000;

void setup() {
  Serial.begin(115200);
  Serial.println("Ampere Hunter v1");

  Serial.println("Initializing HX711");

  WiFiManager wifiManager;
  wifiManager.autoConnect("AmpereHunter");
  if(client.connect(server, port))
    Serial.println("client connesso");
  else
    Serial.println("client NON connesso");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN,32);
  delay(5000);
  
}

void loop() {
  
  raw_read = scale.read();
  current_ua = (raw_read-OFFSET_TOT )/SCALE_FACTOR+OFFSET_uA;
  Serial.println(String(current_ua) + "\t" + String(raw_read));
  delay(100);

  client.println(String(current_ua) + "\t" + String(raw_read));

}