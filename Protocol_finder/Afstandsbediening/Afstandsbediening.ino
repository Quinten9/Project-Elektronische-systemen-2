#include "IRremote.hpp"

#define IR_RECEIVE_PIN 2

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); 
}

void loop() {
  if (IrReceiver.decode()) {
    uint16_t command = IrReceiver.decodedIRData.command;
    switch (command) { 
      case 24: 
        Serial.println("AAN / UIT"); 
        break;
      case 13:
        Serial.println("MODE");
        break;
      case 4:
        Serial.println("SET");
        break;
      case 70: 
        Serial.println("+ IN O"); 
        break;
      case 85:
        Serial.println("ECO");
        break;	
      case 22: 
        Serial.println("- IN O"); 
        break;
      case 64:
        Serial.println("GRAFIEK");
        break;		
      case 25:
        Serial.println("+");
        break;	
      case 23:
        Serial.println("-");
        break;  
      case 30:
        Serial.println("WEEK");
        break;
      default:	
        Serial.println("UNDEFINED");	  
    } 	   
		
    delay(100);
    IrReceiver.resume();
  }
}
