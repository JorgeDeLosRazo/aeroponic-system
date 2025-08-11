#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3D ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define ADC_RES 4095
#define MQ137 A3

#define RELAY_PIN 26


void DisplayAmmoniaPercentage();
float AmmoniaPercentage();
void FansAndRelay();

unsigned long lastToggleTime = 0;
bool relay_on = false;

void setup() {
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.clearDisplay();

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);
  Serial.println("ESP32 Relay Controller Initialized");
}

void loop() {
  FansAndRelay();
  DisplayAmmoniaPercentage();
  
}

float AmmoniaPercentage(){
  float raw_analog_value = analogRead(A3);
  float ammonia_percentage = (raw_analog_value / (float)ADC_RES) * 100.0;
  return ammonia_percentage;
}

void DisplayAmmoniaPercentage(){
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.cp437(true);
  
  display.setTextSize(1); 
  display.setCursor(0, 5);     // Start at top-left corner is (0,0). Note: format is in (x,y)
  display.print("Ammonia (%): ");
  display.print(AmmoniaPercentage());
  display.println("%");

  display.setTextSize(1);

  display.setCursor(0,15);
  if(!relay_on){
    display.println("Fans       : ON");
  } else {
    display.println("Fans       : OFF");
  }

  display.setCursor(0,25);
  display.println("Plasma     : OFF");

  display.setCursor(0,35);
  display.println("Mister     : OFF");

  display.display();
  delay(100);
}

void FansAndRelay(){

  unsigned long currentMillis = millis();
  if (currentMillis - lastToggleTime >= 5000) { // every 5 seconds
    relay_on = !relay_on;
    digitalWrite(RELAY_PIN, relay_on ? LOW : HIGH); // active LOW
    lastToggleTime = currentMillis;
  }

}
