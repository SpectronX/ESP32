//This code is to setup the ESP32 in station mode

//Including the required libraries
#include <Arduino.h>
#include <WiFi.h>

void setup(){
  Serial.begin(115200); //Initializing the Serial Monitor
  
  WiFi.mode(WIFI_STA); // Setting up the microcontroller in STATION mode
  
  WiFi.begin("Wokwi-GUEST", ""); 
  /* The first argument is the WiFi network we are connecting to
  and the second is the password: no password in this case */

  Serial.println("Connecting to WiFi");
  while(WiFi.status() != WL_CONNECTED){ // Checking if connnection has succedded.
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
