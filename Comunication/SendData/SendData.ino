#include "IRremote.hpp"
#include <Arduino_HTS221.h>

String dataMSG = "";
#define IR_RECEIVE_PIN 2

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); 
}

void loop() {
  dataMSG = "IR: ";
  if (IrReceiver.decode()) {
    uint16_t command = IrReceiver.decodedIRData.command;
    switch (command) { 
      case 24: 
        dataMSG += "AAN / UIT"; 
        break;
      case 13:
        dataMSG += "MODE"; 
        break;
      case 4:
        dataMSG += "SET";
        break;
      case 70: 
        dataMSG += "+ IN O"; 
        break;
      case 85:
        dataMSG += "ECO";
        break;  
      case 22: 
        dataMSG += "- IN O"; 
        break;
      case 64:
        dataMSG += "GRAFIEK";
        break;    
      case 25:
        dataMSG += "+";
        break;  
      case 23:
        dataMSG += "-";
        break;  
      case 30:
        dataMSG += "WEEK";
        break;
      default:  
        dataMSG += "UNDEFINED";    
    }      
    
    delay(100);
    IrReceiver.resume();
  }
  
  // read all the sensor values
  float temperature = HTS.readTemperature();
  float humidity    = HTS.readHumidity();
  dataMSG += "\t Temp:";
  dataMSG += temperature;
  dataMSG += "\t Humidity:";
  dataMSG += humidity;
}
