void setup() {
  Serial.begin(9600); 
  Serial.println("Programa de lectura serial");
  Serial.println("==========================");
}

int IN = 0;
String mng = "iniciado";
  
void loop() {
  if (Serial.available() > 0) {
  mng = Serial.readString(); // 
  
  Serial.print("Has enviado: ");
  Serial.println(mng); //BIN, DEC
  }
}
