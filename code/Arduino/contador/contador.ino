void setup() {
  Serial.begin(9600);
  while(!Serial){
    }
  Serial.println("Programa contador");
  Serial.println("==================");
}

int t = 0;
String s = " s";


void loop() {
  
  String tmp = t + s;
  Serial.println(tmp);
  delay(1000);  // 1000ms = 1s
  t = t + 1;
  
}
