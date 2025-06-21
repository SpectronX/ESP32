#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

int ledPin = 18;
bool ledStatus = LOW;

WebServer server(80);

void Homepage();
void ledon();
void ledoff();
void Notfound();
String SendHTML(bool status);

void setup(){
    Serial.begin(115200);
    pinMode(ledPin, OUTPUT);

    WiFi.mode(WIFI_STA);
    WiFi.begin("Wokwi-GUEST", "");
    Serial.println("Connecting to WiFi");
    while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(300);
    }
    Serial.println("Network is Up");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    server.on("/", Homepage);
    server.on("/ledon", ledon);
    server.on("/ledoff", ledoff);
    server.onNotFound(Notfound);

    server.begin();
    Serial.println("Web server started. Open http://localhost:8180 in your browser.");
}

void loop(){
    server.handleClient(); //Keeps listening for client request.

    if(ledStatus){
        digitalWrite(ledPin, HIGH);
    } else {
        digitalWrite(ledPin, LOW);
    }
}

String SendHTML(bool ledStat) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>LED Control</title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr += ".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr += ".button-on {background-color: #3498db;}\n";
  ptr += ".button-on:active {background-color: #2980b9;}\n";
  ptr += ".button-off {background-color: #34495e;}\n";
  ptr += ".button-off:active {background-color: #2c3e50;}\n";
  ptr += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<h1>ESP32 Web Server</h1>\n";
  ptr += "<h3>Using Station(STA) Mode</h3>\n";

  if (ledStat)
    ptr += "<p>LED Status: ON</p><a class=\"button button-off\" href=\"/ledoff\">OFF</a>\n";
  else
    ptr += "<p>LED Status: OFF</p><a class=\"button button-on\" href=\"/ledon\">ON</a>\n";

  ptr += "</body>\n";
  ptr += "</html>\n";

  return ptr;
}

void Homepage(){
    ledStatus = LOW;
    Serial.print("GPIO18 Status : OFF");
    server.send(200, "text/html", SendHTML(ledStatus));
}

void ledon(){
    ledStatus = HIGH;
    Serial.println("GPIO Status : ON");
    server.send(200, "text/html", SendHTML(ledStatus));
}

void ledoff(){
    ledStatus = LOW;
    Serial.println("GPIO Status : OFF");
    server.send(200, "text/html", SendHTML(ledStatus));
}

void Notfound(){
    server.send(404, "text/plain", "Not Found");
}
