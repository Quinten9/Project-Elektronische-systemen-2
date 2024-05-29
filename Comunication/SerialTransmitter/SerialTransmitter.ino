#include <Arduino_HTS221.h>

String dataMSG = "";

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!HTS.begin()) {
    Serial.println("Failed to initialize humidity temperature sensor!");
    while (1);
  }
}

void loop() {
  dataMSG = "";
  // read all the sensor values
  float temperature = HTS.readTemperature();
  float humidity    = HTS.readHumidity();

  dataMSG += "Temp: ";
  dataMSG += temperature;
  dataMSG += "   Humi: ";   
  dataMSG += humidity; 

  Serial.print(dataMSG);

  // print an empty line
  Serial.println();

  // wait 1 second to print again
  delay(1000);
} 
