void setup(){
  // D0 como pin de salida
  pinMode(0, OUTPUT); 
}

void loop(){
	encender_led(2000);
	apagar_led(1000);
}

void encender_led(int t){
  digitalWrite(0, HIGH);
  delay(t);
}

void apagar_led(int t){
  digitalWrite(0, LOW);
  delay(t);
}