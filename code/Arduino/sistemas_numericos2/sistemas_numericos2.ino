void setup(){
	Serial.begin(9600);
}

int x = 0b11; // También válido B1111
int y = 0x15; // Hexadecimal
int z = 010;  // Octal

void loop(){
	Serial.println(x);
	Serial.println(y);
	Serial.println(z);
	x = 2*x;
	Serial.println(x, BIN);
	delay(2000);
}