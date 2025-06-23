#include <Arduino.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <WebServer.h>

int dhtPin = 26;
int redPin = 5;
int bluePin = 2;
int greenPin = 4;

DHT sensor(dhtPin, DHT22);
LiquidCrystal_I2C lcd(0x27, 20, 4);
WebServer server(80);

//Virtual Network provided by Wokwi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

void Homepage();
void Notfound();
String sendHTML();

void setup(){
  Serial.begin(9600);
  sensor.begin();

  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  //lcd setup
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Humidity:");
  lcd.setCursor(0, 2);
  lcd.print("Temperature:");

  //WiFi Setup
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, "");
  Serial.print("Connecting to WiFi");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println("Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  //server setup
  server.on("/", Homepage);
  server.begin();
  Serial.println("Web server started. Open http://localhost:8180 in your browser.");
}
