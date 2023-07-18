/*-------------------------------------------
* AdimnESP - Grower High 2023
* Site WEB: https://growerhigh.com
* e-Mail: permiteteengresar@gmail.com
* Platform ESP32
* Project Admin Panel Tool for the ESP32
*/

#include "LedBlink.hpp"
//-------------------------------------------
// Genera un log en el puerto Serial
//-------------------------------------------
void log(String s){
    Serial.println(s);
}
//-------------------------------------------
// Definir la Plataforma
//-------------------------------------------
String platform(){
// Optien la plataforma de hardware
#ifdef ARDUINO_ESP32_DEV
    return "ESP32";
#endif
}
IPAddress CharToIP(const char *str){
     sscanf(str, "%hhu.%hhu.%hhu.%hhu", &ip[0], &ip[1], &ip[2], &ip[3]);
     return IPAddress(ip[0], ip[1], ip[2], ip[3]);
}
//-------------------------------------------
// Retorna IPAddress en formato "n.n.n.n" de IP a String
//-------------------------------------------
String ipStr(const IPAddress &ip){
    String sFn = "";
    for (byte bFn= 0; bFn < 3; bFn++)
    {
        sFn += String((ip >> (8 * bFn)) & 0xFF) + ".";
    }
    sFn += String(((ip >> 8 * 3) & 0xFF));
    return sFn;
}
//-------------------------------------------
// De Hex a String
//-------------------------------------------
String hexStrc(const unsigned long &h, const byte &l = 8){
    String s;
    s = String(h, HEX);
    s.toUpperCase();
    s = (00000000 + s).substring(s.length() + 8 -l);
    return s;
}
//-------------------------------------------
// Crear un ID unico desde la direccion MAC
//-------------------------------------------
String idUnique(){
    // Retorna los ultimos 4 Bytes del MAC rotados
    char idunique[15];
    uint64_t chipid = ESP.getEfuseMac();
    uint16_t chip = (uint16_t)(chipid >> 32);
    snprintf(idunique, 15, "%04X", chip);
    return idunique;
}


String deviceID(){
    return String(platform()) + hexStrc(ESP.getEfuseMac()) + String(idUnique());
}

void settingsPines(){
    pinMode(WIFILED, OUTPUT);
    pinMode(MQTTLED, OUTPUT);
    pinMode(RELAY1, OUTPUT);
    pinMode(RELAY2, OUTPUT);
    
    digitalWrite(RELAY1, LOW);
    digitalWrite(RELAY2, LOW);
    digitalWrite(MQTTLED, LOW);
    digitalWrite(WIFILED, LOW);
}