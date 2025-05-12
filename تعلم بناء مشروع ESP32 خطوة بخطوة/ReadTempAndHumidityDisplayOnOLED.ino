
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Include the library for interfacing with the sensor.
#include <DHT22.h>

#define pinDATA 13 //Pin D13 on ESP32 Dev Board
DHT22 dht22(pinDATA); 

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
    // Initialize serial communication to allow debugging and data readout.
    // Using a baud rate of 9600 bps.
    Serial.begin(9600);

    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
  }
  display.clearDisplay();
  display.display();

  delay(1000);
}

void loop() {

    float t = dht22.getTemperature();
    float h = dht22.getHumidity();

  if (dht22.getLastError() != dht22.OK) {
    Serial.print("DHT22 Error");
  delay(100);
  }
    else{
  Serial.print("DHT22 h=");Serial.print(h,1);Serial.print("\t");
  Serial.print("t=");Serial.println(t,1);
  Serial.println("");

  display.clearDisplay();
  display.setTextSize(2);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.print("T: ");         // Use full 256 char 'Code Page 437' font
  display.println(t);
  display.print("H: ");         // Use full 256 char 'Code Page 437' font
  display.println(h);

  display.display();
  delay(100);
    }

}
