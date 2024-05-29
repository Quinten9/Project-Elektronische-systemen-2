#include <Wire.h>
#include <LiquidCrystal_I2C.h> 

#define lightSensor A0

int sensorValue = 0;

//I2C pin declaratie
LiquidCrystal_I2C lcd(0x3F, 16, 2); //Opgelet met adres 0x27; 0x3F is voor de PCF8574A

void setup() {
  lcd.init(); //Initializing display
  lcd.backlight(); //To Power ON the back light
}

void loop() {
  lcd.clear();
  lcd.setCursor(0,0); //Defining positon to write from first row,first column.
  lcd.print("Light Value:"); //You can write 16 Characters per line.
  lcd.setCursor(0,1); //Defining positon to write from first row,first column.

  sensorValue = analogRead(lightSensor);

  lcd.print(sensorValue);
  delay(1000);
}
