void setup(){
	Serial.begin(9600);
	Serial.println("Conversor binario");
}

int x = 12;

void loop(){
	Serial.println(x);
	Serial.println(x, BIN);
	Serial.println(x, HEX);
	Serial.println(x, OCT);
	
	delay(2000);
}