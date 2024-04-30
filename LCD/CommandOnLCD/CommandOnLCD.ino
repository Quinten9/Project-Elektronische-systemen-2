#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "IRremote.hpp"

#define IR_RECEIVE_PIN 2
String msg = "";

//I2C pin declaratie
LiquidCrystal_I2C lcd(0x3F, 16, 2); //Opgelet met adres 0x27; 0x3F is voor de PCF8574A

uint32_t vorigeMillis = 0;
bool newPress = false;

int waitTime = 5000;

//Zie gegevens PCF8574 of PCF8574A

void setup()
{
  lcd.init(); //Initializing display
  lcd.backlight(); //To Power ON the back light

  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);  
}

void loop()
{
  lcd.setCursor(0,0); //Defining positon to write from first row,first column .
  lcd.print("Pressed:"); //You can write 16 Characters per line.

  //Clear de screen om de 5sec en reset de clear tijd elke keer dat er eens nieuwe knop ingedrukt wordt
  if(millis() - vorigeMillis >= waitTime){
    lcd.clear();
    vorigeMillis = millis();
  }
  
  if (IrReceiver.decode()) {
    vorigeMillis = millis();
    lcd.clear();
    lcd.setCursor(0,0); //Defining positon to write from first row,first column .
    lcd.print("Pressed:"); //You can write 16 Characters per line.
    lcd.setCursor(0,1);
    
    uint16_t command = IrReceiver.decodedIRData.command;
    
    switch (command) { 
      case 24: 
        //Display uit en na 1sec weer aan
        lcd.noDisplay();
        delay(1000);
        lcd.display();
        msg = "AAN / UIT";
        break;
      case 13:
        msg = "MODE";
        break;
      case 4:
        msg = "SET";
        break;
      case 70: 
        msg = "+ IN O"; 
        break;
      case 85:
        msg = "ECO";
        break;  
      case 22: 
        msg = "- IN O"; 
        break;
      case 64:
        msg = "GRAFIEK";
        break;    
      case 25:
        msg = "+";
        break;  
      case 23:
        msg = "-";
        break;  
      case 30:
        msg = "WEEK";
        break;
      default:  
        msg = "UNDEFINED";    
    }  

    lcd.print(msg); 
    IrReceiver.resume();
  }
} 
