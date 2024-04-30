String Message;

void setup() {
  
  Serial.begin(9600);
  Serial.setTimeout(50); // default is 1 second
  delay(100);

}

void loop() { 
  if (Serial.available()) {
      Message = Serial.readString(); 
  }
 
  delay(4);

  Serial.println(Message);
  
}
