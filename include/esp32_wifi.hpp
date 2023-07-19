/*-------------------------------------------
* AdimnESP - Grower High 2023
* Site WEB: https://growerhigh.com
* e-Mail: permiteteengresar@gmail.com
* Platform ESP32
* Project Admin Panel Tool for the ESP32
*/
#include <WiFi.h>
#include <DNSServer.h>
#include <ESPmDNS.h>

const byte DNSSERVER_PORT = 53;
DNSServer dnsServer;

IPAddress apIP(192, 168, 4, 1);
IPAddress netMsk(255, 255, 255, 0);

int wifi_mode = WIFI_STA;

unsigned long previousMillisWIFI = 0;
unsigned long intervalWIFI = 30000;

// --> recorrendo esse id de settingsResetWiFi.hpp -->  strlcpy(id, "adminesp32", sizeof(id));
// hotname for ESPmDNS. Should work at least on windows. Try http://adminesp32.local
const char *esp_hostname = id;

void startAP(){
    log("Info: Iniciando Modo AP");
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(1000);
    WiFi.softAPConfig(apIP, apIP, netMsk);
    WiFi.setHostname(deviceID().c_str());
    WiFi.softAP(ap_nameap, ap_passwordap, ap_canalap, ap_hiddenap, ap_connetap);
    log("Info: WiFi AP" + deviceID() + " - IP " + ipStr(WiFi.softAPIP()));
    dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);
    dnsServer.start(DNSSERVER_PORT, "*", apIP);
    wifi_mode = WIFI_AP;
}
//--------------------------------------------------------------
// Start Client, attempt to connect to WiFi network
//--------------------------------------------------------------
void startClient(){
    if (wifi_staticIp){
        if (!WiFi.config(CharToIP(wifi_ip_static), CharToIP(wifi_gateway), CharToIP(wifi_subnet), CharToIP(wifi_primaryDNS), CharToIP(wifi_secondaryDNS))){
            log("Error: Falló al conectar el modo Station");
        }
        WiFi.hostname(deviceID());
        WiFi.begin(wifi_ssid, wifi_password);
        log("Info: Conectando WiFi " +  String(wifi_ssid));
        delay(50);
        byte b = 0;
        while (WiFi.status() != WL_CONNECTED && b < 60){
            b++;
            log("Warnig: Intentando conecion WiFi...");
            //para parpadear led WiFi cuando esta conectandoal WiF no bloqueante
            //Parpadeeo Simple del led cada 100 ms     
            blinkSingle(100, WIFILED);
        }
        if (WiFi.status() == WL_CONNECTED){
            //WiFi Station conectado
            log("Info: WiFi conectado (" + String(WiFi.RSSI()) + ") IP " + ipStr(WiFi.localIP()));
        }else{
            // WiFi Station NO conetado
            log(F("Error: WiFi no conectado"));
            //parpadeo Ramdon del led
            blinkRandomSingle(10,100, WIFILED);
            delay(100); 
        }
    }
}
//WiF.mode(WIFI_STA) - station mode:  the ESP32 connects to an access point
//WiF.mode(WIFI_STA) - access point mode: stations can connect to the ESP32
//WiF.mode(WIFI_STA) - access point and a station connected to another access point
 
void wifi_setup(){
    WiFi.disconnect();
    // 1) Si esta em Mode AP
    if(ap_accessPoint){
        startAP();
        log("Info: WiFI Modo AP");
    }
    // 2) Caso contrario en Modo Station/Client mejor dicho Client
    else{
        WiFi.mode(WIFI_STA);
        startClient();
        log("Info: WiFi Modo Estacion");
    }
    // Iniciar hostname broadcast en modo STA o AP --> solucion interesante para no ter que escribir todas las vezes la direcion IP
    if (wifi_mode == WIFI_STA || wifi_mode == WIFI_AP){
        if (MDNS.begin(esp_hostname)){
            MDNS.addService("http", "tcp", 80);
            //log(esp_hostname);
            //MDNS.addService("ws", "tcp", 81);
        }
    }
}
//--------------------------------------------------------------
// Loop Mode Client
//--------------------------------------------------------------
void wifiLoop(){

    unsigned long currentMillis = millis();
    
    if (wifi.status() != WL_CONNECTED && (currentMillis - previousMillisWIFI >= intervalWIFI)){
        //parpadear un led cuando conectandose  al wifi no bloqueante
        //parpadeo simples de 0.1% de segundoblinkSingle(100, WIFILED);
        blinkSingle(100, WIFILED);

        WiFi.disconnect();
        WiFi.reconnect();
        previusMillisWIFI = currentMillis;
    }else{
    blinkSingleAsy(10,,500,WIFILED);
    }
}
//--------------------------------------------------------------
// Loop Mode AP
//--------------------------------------------------------------void wifiAPLoop(){
    //parpadeo variable en con transferencia de Datos
    blinkRandomSingle(50, 100, WIFILED);
    dnsServer.processNextRequest(); //Captive portal DNS re-direct
} 