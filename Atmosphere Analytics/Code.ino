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

void loop(){
  float humidity = sensor.readHumidity();
  float temperature = sensor.readTemperature();

  while (!isnan(humidity) && !isnan(temperature)) {
  // Clear previous RGB LED state
  digitalWrite(bluePin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(redPin, LOW);

  // Display humidity
  lcd.setCursor(0, 1);
  lcd.print("                ");  
  delay(300);
  lcd.setCursor(0, 1);
  lcd.print(humidity, 1);
  lcd.print(" %");

  if (humidity <= 30) {
    lcd.setCursor(9, 1);
    lcd.print("Too Dry");
  } else if (humidity <= 60) {
    lcd.setCursor(9, 1);
    lcd.print("Normal");
  } else if (humidity <= 80) {
    lcd.setCursor(9, 1);
    lcd.print("Humid");
  } else {
    lcd.setCursor(9, 1);
    lcd.print("Too Humid");
  }

  delay(500);

  // Display temperature
  lcd.setCursor(0, 3);
  lcd.print("                ");  
  delay(300);
  lcd.setCursor(0, 3);
  lcd.print(temperature, 1);
  lcd.print(" C");

  if (temperature < 18) {
    digitalWrite(bluePin, HIGH);
    lcd.setCursor(9, 3);
    lcd.print("Chilly");
  } else if (temperature < 28) {
    digitalWrite(greenPin, HIGH);
    lcd.setCursor(9, 3);
    lcd.print("Comfy");
  } else {
    digitalWrite(redPin, HIGH);
    lcd.setCursor(9, 3);
    lcd.print("Too hot");
  }

  delay(1000); 
  break;       
}

  server.handleClient();
}

void Homepage(){
  server.send(200, "text/html", sendHTML());
}

void Notfound(){
  server.send(404, "text/plain", "Not Found");
}

String sendHTML() {
  float humidity = sensor.readHumidity();
  float temperature = sensor.readTemperature();

  String html = "<!DOCTYPE html><html><head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<title>Weather Monitor</title>";
  html += "<style>";
  html += "body { font-family: Arial; text-align: center; background: #f0f0f0; padding: 30px; }";
  html += ".card { background: white; padding: 20px; border-radius: 10px; display: inline-block; box-shadow: 0 0 10px rgba(0,0,0,0.1); }";
  html += "h1 { margin-bottom: 20px; }";
  html += "p { font-size: 1.2em; }";
  html += "button { margin-top: 20px; padding: 10px 20px; font-size: 1em; }";
  html += "</style></head><body>";
  html += "<div class='card'>";
  html += "<h1>Weather Monitor</h1>";

  if (!isnan(humidity) && !isnan(temperature)) {
    html += "<p><strong>Humidity:</strong> " + String(humidity, 1) + " %</p>";
    html += "<p><strong>Temperature:</strong> " + String(temperature, 1) + " °C</p>";
  } else {
    html += "<p><strong>Sensor Error:</strong> Data not available</p>";
  }

  html += "<button onclick='location.reload()'>Refresh</button>";
  html += "</div></body></html>";
  return html;
}
