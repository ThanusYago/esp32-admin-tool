 /*-------------------------------------------
* AdimnESP - Grower High 2023
* Site WEB: https://growerhigh.com
* e-Mail: permiteteengresar@gmail.com
* Platform ESP32
* Project Admin Panel Tool for the ESP32
*/

#include <Arduino.h>

bool ioBlink = false;
unsigned long milOld;
int rndTemp = 0;

//-------------------------------------------
// Simple blinking function - Pestañeo para alarmas tiempo variables
//-------------------------------------------
void blinkSingle(int speed, int _pin){
    if ((milOld + speed) < millis()){
            milOld = millis();
        if (ioBlink == false){
            digitalWrite(_pin, HIGH);
            ioBlink = true;
        }
        else{
            digitalWrite(_pin, LOW);

        }
    }
}
//-------------------------------------------
// Parpadeo Asincrócno Tiempo On y Tiempo Off tiempo variable
//-------------------------------------------
void blinkSingleAsy(int timeHigh, int timeLow, int _pin){
    if (ioBlink == false){
        if((milOld + timeHigh) < millis()){
            milOld = millis();
            digitalWrite(_pin, LOW);
            ioBlink = true;
        }
    }
     else{
        if((milOld + timeLow) < millis()){
            milOld = millis();
            digitalWrite(_pin, HIGH);
            ioBlink = true;
        }
    }
}
//-------------------------------------------
// Blinking with ramdomised delay como para TX/RX de DATOS
//-------------------------------------------
void blinkRandomSingle(int minTime, int maxTime, int _pin){
    if((milOld + rndTemp) < millis()){
        milOld = millis();
        rndTemp = random(minTime, maxTime);
        if (ioBlink == false){
            digitalWrite(_pin, HIGH);
            ioBlink = true;
        }
        else{
            digitalWrite(_pin, LOW);
            ioBlink = false;
        }
    }
}
//-------------------------------------------
// On un led
//-------------------------------------------
void setOnsingle(int _pin){
    digitalWrite(_pin, HIGH);
}
//-------------------------------------------
// Off un led
//-------------------------------------------
void setOffsingle(int _pin){
    digitalWrite(_pin, LOW);
}