/*
  Prueba topes de carrera

  Programa utilizado para probar el funcionamiento de los topes de carrera del posicionador tridimensional, 
  utilizando la librería creada para el control de los motores.

  @autor    : Josué Meneses Díaz
  @fecha    : 22-08-2019
  @versión  : 1.0
*/  

#include <motor.h>
motor m(4,2,3,7,5,6,10,8,9,
        48,46,44,42,40);

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("hola");
  //m.test_topes(48);
  /*m.test_topes(46);
  m.test_topes(44);
  m.test_topes(42);
  m.test_topes(40);
  delay(500);*/
}
