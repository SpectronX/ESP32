//This code is to setup the ESP32 in station mode
#include <Arduino.h>
#include <WiFi.h>

void setup(){
  WiFi.mode(WIFI_STA); //Setup of mode
    WiFi.begin("Wokwi-GUEST", "");
    Serial.println("Connecting to WiFi");
    while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(300);
    }
    Serial.println("Network is Up");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

void loop(){
  //Other codes go here
}
