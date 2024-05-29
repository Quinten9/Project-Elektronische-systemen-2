#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "IRremote.hpp"

#define IR_RECEIVE_PIN 2
String msg = "";

#define lightSensor A0 
int sensorValue = 0;

//I2C pin declaratie
LiquidCrystal_I2C lcd(0x3F, 16, 2); //Opgelet met adres 0x27; 0x3F is voor de PCF8574A

uint32_t vorigeMillis = 0;
bool newPress = false;

int waitTime = 5000;

int modeCount = 0;
int SerialReadModeCount = 0;

int humidityVal = 0;
int tempVal = 0;

void Read_Light()
{ 
  //Lightsenor-read-mode is selected
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Light Value:");
  lcd.setCursor(0,1);
  sensorValue = analogRead(lightSensor);
  msg = "";
  msg += sensorValue;
  lcd.print(msg);
  delay(500);
}

void Read_Serial_Sens(){
  msg = "";
  lcd.clear();
  lcd.setCursor(0,0);
  msg +=  "Humidity: ";
  msg += humidityVal;
  lcd.print(msg);
  msg = "";
  lcd.setCursor(0,1);
  msg +=  "Temperature: ";
  msg += tempVal;
  lcd.print(msg);
  delay(500);
}

void setup()
{
  lcd.init(); //Initializing display
  lcd.backlight(); //To Power ON the back light

  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);  

  Serial.begin(9600);
}

void loop()
{
  if(modeCount > 0){
    Read_Light();
    if(modeCount >= 7){
      modeCount = 0;
    }
  }
  else if(SerialReadModeCount > 0){
    Read_Serial_Sens();
    if(SerialReadModeCount >= 7){
      SerialReadModeCount = 0;
    }
  }
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
        modeCount++;
        break;
      case 85:
        msg = "ECO";
        break;  
      case 22: 
        msg = "- IN O";
        modeCount--;
        if(modeCount < 0){
          modeCount = 0;
        }
        break;
      case 64:
        msg = "GRAFIEK";
        break;    
      case 25:
        msg = "+";
        SerialReadModeCount++;
        break;  
      case 23:
        msg = "-";
        SerialReadModeCount--;
        if(SerialReadModeCount < 0){
          SerialReadModeCount = 0;
        }
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
