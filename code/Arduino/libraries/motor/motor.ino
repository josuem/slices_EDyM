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
  Serial.println("Prueba funcionamiento Tope x inicial");
  }
  
  int cont_ini = 0;
  
  while (cont_ini == 0){
   
    cont_ini = 1;
  }

}
