//Simple code for setting up the ESP32 in Access Point Mode

//Including the required Libraries
#include <Arduino.h>
#include <WiFi.h>

const char* ssid = "Access Point";      // Name of the Wi-Fi network to create
const char* password = "1234";    // Password for the network

void setup(){
  Serial.begin(115200);
  
  WiFi.mode(WIFI_AP); // Setting up in Acess Point Mode
  WiFi.softAp(ssid, password); // Start the AP with the given SSID and Password

  Serial.println("Access Point Started");
  Serial.print("Network Name (SSID): ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP()); // Show IP assigned to the AP
}

void loop(){
  //Main Code goes here
}
