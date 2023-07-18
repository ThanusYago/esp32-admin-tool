/*-------------------------------------------
* AdimnESP - Grower High 2023
* Site WEB: https://growerhigh.com
* e-Mail: permiteteengresar@gmail.com
* Platform ESP32
* Project Admin Panel Tool for the ESP32
*/

//-------------------------------------------
// Definitions
//-------------------------------------------
#define RELAY1 27     //GPIO RELAY1 27 
#define RELAY2 26     //GPIO RELAY2 26
#define WIFILED 12    //GPIO WIFI LED  12 
#define MQTTLED 13    //GPIO MQTT LED   13
//-------------------------------------------
// Version of Hardware
//-------------------------------------------
#define HW "ADMINESP32 v1 00000000"
//-------------------------------------------
// Zone WIFI
//-------------------------------------------
boolean wifi_staticIp;
char    wifi_ssid[30];
char    wifi_password[30];
char    wifi_ip_static[15];
char    wifi_gateway[15];
char    wifi_subnet[15];
char    wifi_primaryDNS[15];
char    wifi_secondaryDNS[15];
//-------------------------------------------
// Zone Geral Configurations 
//-------------------------------------------
char    id[30];             //id device
int     bootCount;          //restart restarts

//-------------------------------------------
// Zone AP - acess point
//-------------------------------------------
boolean ap_acessPoint;
char    ap_nameap[31];
char    ap_passwordap[63];
int     ap_canalap;
int     ap_hiddenap;
int     ap_connetap;
//-------------------------------------------
// Zone Others  */
//-------------------------------------------
uint_t ip[4];               //variables function convert String to IP 