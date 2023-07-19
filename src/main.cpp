/*-------------------------------------------
* AdimnESP - Grower High 2023
* Site WEB: https://growerhigh.com
* e-Mail: permiteteengresar@gmail.com
* Platform ESP32
* Project Admin Panel Tool for the ESP32
*/

//-------------------------------------------
// Libraries
//-------------------------------------------
#include <Arduino.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>

//ARCHIVOS *.hpp - Fragmentar el code

#include "settings.hpp"
#include "functions.hpp"
#include "settingsReset.hpp"
#include "settingsRead.hpp"
#include "settingsSave.hpp"
#include "esp32_wifi.hpp"

// Setup
// Baudrate
void setup() {
  Serial.begin(115200);
// CPU Freq:
  setCpuFrequencyMhz(240);
  // inciando el setup
  log("\nInfo: Iniciando el Setup");
  // confifiguraciones de pines
  settingsPines();
  // SPIFFS
  if(!SPIFFS.begin(true)){
    log("Erro: Falló la inicializacion del SPIFFS");
    while (true);
  }
  // Leer la configuracion WiF:
  settingsReadWiFi();
  // configuracion WIFI
  WiFi.disconnect(true);
  delay(1000);
  // Setup WiFi
  wifi_setup();

}


//-------------------------------------------
// Loop Principal Nucleo 0
//-------------------------------------------

void loop() {
  // put your main code here, to run repeatedly:
  yield();
  //-------------------------------------------
  // Libraries
  //-------------------------------------------
    if (wifi_mode == WIFI_STA){
      wifiLoop();
    }
    if (wifi_mode == WIFI_AP){
      wifiAPLoop();    } 
}

