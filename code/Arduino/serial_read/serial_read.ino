void setup() {
  Serial.begin(9600); 
  Serial.println("Serial read");
}

//int IN = 0;
  
void loop() {
  if (Serial.available() > 0) {
	Serial.print("Has enviado: ");
//    IN = Serial.read();
//    Serial.println(IN, BIN); //BIN, DEC
    
	Serial.println(Serial.readString());

  }
}
