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

IPAddress aiIP(192, 168, 4, 1);
IPAddress netMsk(255, 255, 255, 10;

int wifi_mode = WIFI_STA;

void startAP(){
    log("Info: Iniciando Modo AP");
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(1000);
    WiFi.softAPConfig(apID, apIP, netMsk);
    WiFi.setHostname(deviceID().c_str());
    WiFi.softAP(ap_nameap, ap_passwordap, ap_canalap, ap_hiddenap, ap_connetap);
    log("Info: WiFi AP" + deviceID() + " - IP " + ipStrc(WiFi.softAPIP()));
    dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);
    dnsServer.start(DNSSERVER_PORT, "*", apIP);
    wifi_mode = WIFI_AP;
}
//--------------------------------------------------------------
// Start Client, attempt to connect to WiFi network
//--------------------------------------------------------------
void startClient(){
    if (wifi_staticIp){
        if (!WiFi.config(CharToIP(wifi_staticIp), CharToIP(wifi_gateway), CharToIP(wifi_subnet), CharToIP(wifi_primaryDNS), CharToIP(wifi_secondaryDNS))){
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
            //blinkSingle(100, WIFILED);
        }
        if (WiFi.status() == WL_CONNECTED){
            //WiFi Station conectado
            log("Info: WiFi conectado (" + String(WiFi.RSSI()) + ") IP " + ipStr(WiFi.localIP()));
        }else{
            // WiFi Station NO conetado
            log(F("Error: WiFi no conectado"));
            //parpadeo Ramdon del led
            //blinkRamdonSingle(10,100, WIFILED);
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
        starAP();
        log("Info: WiFI Modo AP");
    }
    // 2) Caso contrario en Modo Station/Client mejor dicho Client
    else{
        WiFi.mode(WIFI_STA);
        starClient();
        log("Info: WiFi Modo Estacion");
    }
}