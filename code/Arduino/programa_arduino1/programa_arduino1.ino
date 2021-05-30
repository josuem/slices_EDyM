void setup() {
  Serial.begin(9600);
  Serial.println("Programa 1");
}

int t = 0;
String s = " [s]";

void loop() {
  String tmp = t + s;
  Serial.println(tmp);
  delay(1000);
  t=t+1;
}
