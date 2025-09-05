#include <Wire.h>
#include <Arduino.h>
#include <DHT.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

int dhtpin = 12;
int redpin = 19;
int bluepin = 2;
int greenpin = 4;

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire ,OLED_RESET);

DHT dht(dhtpin, DHT22);

void drawSmoothWaterDrop(int x, int y) {
  display.fillCircle(x, y + 3, 3, SSD1306_WHITE);      

  display.fillCircle(x, y + 8, 6, SSD1306_WHITE);      

  display.drawLine(x - 2, y + 1, x, y - 2, SSD1306_WHITE); 
  display.drawLine(x + 2, y + 1, x, y - 2, SSD1306_WHITE); 
  display.drawLine(x - 1, y - 1, x + 1, y - 1, SSD1306_WHITE); 
  display.drawPixel(x, y - 2, SSD1306_WHITE); 
};

void drawsun(int centerX, int centerY, int sunRadius, int rayLength){
  display.fillCircle(centerX, centerY, sunRadius, SSD1306_WHITE);

  for (int i = 0; i < 360; i += 45) {
    float angle = radians(i);
    int x1 = centerX + sunRadius * cos(angle);
    int y1 = centerY + sunRadius * sin(angle);
    int x2 = centerX + (sunRadius + rayLength) * cos(angle);
    int y2 = centerY + (sunRadius + rayLength) * sin(angle);
    display.drawLine(x1, y1, x2, y2, SSD1306_WHITE);
  };
};

void setup() {
  pinMode(redpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
  pinMode(greenpin, OUTPUT);

  Serial.begin(115200);

  dht.begin();

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)){
    Serial.print("Failed to setup OLED....");
    for(;;);
  } else {
    Serial.print("Success");
  }
}

void loop() {

  //digitalWrite(redpin, LOW);
  //digitalWrite(bluepin, LOW);
  //digitalWrite(greenpin, LOW);

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("  Weather Monitoring  ");
  display.setCursor(0, 8);
  display.print("       Station         ");

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 20);
  display.print("Relative Humidity");
  display.setCursor(0, 30);
  display.print("-> ");
  display.print(humidity);
  display.print(" %");

  display.setCursor(0, 45);
  display.print("Temperature");
  display.setCursor(0, 55);
  display.print("-> ");
  display.print(temperature);
  display.print(" C");

  drawSmoothWaterDrop(112 , 23);
  drawsun(90, 53, 5, 5);

  display.display();

  if(temperature < 10){
    digitalWrite(bluepin, HIGH);
  } else if(temperature >= 10 || temperature <= 30){
    digitalWrite(greenpin, HIGH);
  } else if(temperature > 30){
    digitalWrite(redpin, HIGH);
  }

  delay(200);
 
}
