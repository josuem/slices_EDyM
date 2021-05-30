/*
motor.cpp - funciones para moter motor paso a paso
Creada por Gabriel Fuentes
Lanzado bajo licencia Copyleft---
*/

#include "Arduino.h"
#include "motor.h"

motor::motor(int ENX, int STEPX, int DIRX, 
             int ENY, int STEPY, int DIRY, 
             int ENZ, int STEPZ, int DIRZ, 
             int STOPXi, int STOPXf, int STOPYi, int STOPYf, int STOPZi){
	pinMode(ENX, OUTPUT);  
	pinMode(DIRX, OUTPUT); 
	pinMode(STEPX, OUTPUT);
	pinMode(ENY, OUTPUT);  
	pinMode(DIRY, OUTPUT); 
	pinMode(STEPY, OUTPUT);
	pinMode(STOPYi, INPUT);
	pinMode(STOPYf, INPUT);
	pinMode(STOPXi, INPUT);
	pinMode(STOPXf, INPUT);
	pinMode(STOPZi, INPUT);
	pinMode(ENZ, OUTPUT);  
	pinMode(DIRZ, OUTPUT); 
	pinMode(STEPZ, OUTPUT);
	_ENX = ENX;
	_STEPX = STEPX;
	_DIRX = DIRX;
	_STOPYi = STOPYi;
	_STOPYf= STOPYf;
	_STOPXi = STOPXi;
	_STOPXf= STOPXf;
	_STOPZi = STOPZi;
	_ENY = ENY;
	_STEPY = STEPY;
	_DIRY = DIRY;
	_ENZ = ENZ;
	_STEPZ = STEPZ;
	_DIRZ = DIRZ;
}

void motor::test_topes(int PIN_STOP){
  /* funcion "test_topes"
   Revisa el correcto funcionamiento del tope ingresado, i.e., se revisa la estabilidad y estado de presión (0) del botón*/

  int estado_tope;
  int contador = 0;
  delay(1000);
  Serial.println("===============================");
  Serial.print("Revisión del estado del Tope ");
  
  if (PIN_STOP==48){
    Serial.println("Xi");
  }else if(PIN_STOP==46){
    Serial.println("Xf");
  }else if(PIN_STOP==44){
    Serial.println("Yi");
  }else if(PIN_STOP==42){
    Serial.println("Yf");
  }else if(PIN_STOP==40){
    Serial.println("Zi");
  }

  // Conteo de estados del tope, para revisar estabilidad del botón
  for (int i=0; i<10; i=i+1){
    estado_tope = digitalRead(PIN_STOP);
    contador = contador + estado_tope;
    delay(10);
    }
  
  if (contador==10){
    Serial.println("Tope de carrera estable\n");
  }else{
    Serial.println("Tope de carrea INESTABLE. Revisar conexión\n");
    while(Serial.available()==0){
        delayMicroseconds(100);
        }
  }
  // Revisa si cambia el estado desde 1 a 0 del tope
  Serial.println("Presiona el tope para comprobar funcionamiento");
  
  while(estado_tope==1){
    estado_tope = digitalRead(PIN_STOP);
    delayMicroseconds(10);
    }
  Serial.println("Funcionamiento correcto!!!");
  
  delay(100);  
  }

  





void motor::setupcero(int A){
	if(A == 4){
		delay(1000);
		Serial.println("Fijando cero en eje Y");
		digitalWrite(_ENY, LOW); 
		digitalWrite(_DIRY,HIGH);	
		
	do{ 
		if(Serial.read()=='D'){
			goto salir;
			} 
			
		if(digitalRead(_STOPYi)==HIGH && digitalRead(_ENY)== LOW){
            			digitalWrite(_STEPY,HIGH);
            			delayMicroseconds(100);
            			digitalWrite(_STEPY,LOW);
            			delayMicroseconds(100);
                       		}
		else{
				digitalWrite(_ENY, HIGH);
				}
	
	}while(digitalRead(_STOPYi)==HIGH);




	delay(1000);
		Serial.println("Fijando cero en eje X");
		digitalWrite(_ENX, LOW); 
		digitalWrite(_DIRX,LOW);
	do{
		if(Serial.read()=='D'){
			goto salir;
			}
			
		if(digitalRead(_STOPXi)==HIGH && digitalRead(_ENX)== LOW){
            			digitalWrite(_STEPX,HIGH);
            			delayMicroseconds(100);
            			digitalWrite(_STEPX,LOW);
            			delayMicroseconds(100);
                       		}
		else{
				digitalWrite(_ENX, HIGH);
				}
	
	}while(digitalRead(_STOPXi)==HIGH );
	
	
	delay(1000);
	Serial.println("Fijando cero en eje Z");
		digitalWrite(_ENZ, LOW); 
		digitalWrite(_DIRZ,HIGH);
	do{ 
		
		if(Serial.read()=='D'){
			goto salir;
					}
					
		if(digitalRead(_STOPZi)==HIGH && digitalRead(_ENZ)== LOW){
            			digitalWrite(_STEPZ,HIGH);
            			delayMicroseconds(1000);
            			digitalWrite(_STEPZ,LOW);
            			delayMicroseconds(1000);
                       		}
		else{
				digitalWrite(_ENZ, HIGH);
				}
	
	}while(digitalRead(_STOPZi)==HIGH);
	

}
salir: ;
delay(10);
return;
}

void motor::barridoy(int A, int puntos, int t, int distan){
		if(A=1){
		int contx=0;
		int contz=0;
		int conty=0;	
		int dist = (distan)/puntos;
		int dis=(320)*(dist);   
		int max=puntos;
		int tt=t*1000;	
		Serial.println("Ejecutando Barrido 1D Eje Y");
		Serial.print("Numero de puntos por eje:")+Serial.println(puntos,DEC);
		Serial.print("Distancia entre puntos:")+Serial.print(dist,DEC)+Serial.println("[mm]"); 
		Serial.print("Pausa entre puntos:")+Serial.print(t,DEC)+Serial.println("[s]");
		Serial.print("Distancia total del barrido:")+Serial.print(distan,DEC)+Serial.println("[cm]");
		Serial.println("Inicio en ");
		Serial.print("3.");
		delay(333);
		Serial.print(".");
		delay(333);
		Serial.print(".");
		delay(333);
		Serial.print("2.");
		delay(333);
		Serial.print(".");
		delay(333);
		Serial.print(".");
		delay(333);
		Serial.println("1");
		delay(1000);
		Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
		
		retrocedey: ;
		delay(tt);
		digitalWrite(_ENY, LOW); 
		digitalWrite(_DIRY,LOW);
		int q = 1;
		int w = 0;
		while(q<=max-1){
			  loop: ;		
			  while(Serial.available()==0){
				  	delayMicroseconds(10);
				  				  			 }
			  			 
					
    			 switch(Serial.read()){
					 case 'p':
					 while(w<=dis){
        	    		if(digitalRead(_STOPYf)==HIGH && digitalRead(_ENY)== LOW){
            			digitalWrite(_STEPY,HIGH);
            			delayMicroseconds(100);
            			digitalWrite(_STEPY,LOW);
            			delayMicroseconds(100);
                       		}
							else{
							digitalWrite(_ENY, HIGH);
							delay(tt);
							//~ goto adelantey;
								}
						w=w++;
							}
						w=0;
						q=q++;
						conty=conty++;
						Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
						goto loop;
						break;	
						
					case 'D':		
					delay(10);
				    goto fin;
				    break;	
			}
				
			
		}	
	}
fin: ;
return;
}	
		
		


void motor::modomanual(int A){
	if(A == 3){
		Serial.begin(9600);
		Serial.println(" Modo Manual ");
		do{
	
		if(analogRead(A15)>600 ){
						digitalWrite(_ENY, LOW);
						digitalWrite(_DIRY,HIGH);
			        	digitalWrite(_STEPY,HIGH);
            			delayMicroseconds(100);
            			digitalWrite(_STEPY,LOW);
            			delayMicroseconds(100);
					}
			
				
		
		if(analogRead(A15)<300){
						digitalWrite(_ENY, LOW);
						digitalWrite(_DIRY,LOW);
			        	digitalWrite(_STEPY,HIGH);
            			delayMicroseconds(100);
            			digitalWrite(_STEPY,LOW);
            			delayMicroseconds(100);
					}
						
		if(analogRead(A13)>600){
						digitalWrite(_ENZ, LOW);
						digitalWrite(_DIRZ,HIGH);
			            digitalWrite(_STEPZ,HIGH);
            		    delayMicroseconds(1000);
            			digitalWrite(_STEPZ,LOW);
            			delayMicroseconds(1000);
					}	
					
		if(analogRead(A13)<300){
						digitalWrite(_ENZ, LOW);
						digitalWrite(_DIRZ,LOW);
			        	digitalWrite(_STEPZ,HIGH);
            			delayMicroseconds(1000);
            			digitalWrite(_STEPZ,LOW);
            			delayMicroseconds(1000);
					}	
					
		 if(analogRead(A14)>600){
						digitalWrite(_ENX, LOW);
						digitalWrite(_DIRX,LOW);
			        	digitalWrite(_STEPX,HIGH);
            			delayMicroseconds(100);
            			digitalWrite(_STEPX,LOW);
						delayMicroseconds(100);
			}
			
		if(analogRead(A14)<300){
						digitalWrite(_ENX, LOW);
						digitalWrite(_DIRX,HIGH);
			        	digitalWrite(_STEPX,HIGH);
            			delayMicroseconds(100);
            			digitalWrite(_STEPX,LOW);
            			delayMicroseconds(100);
         			}			
								
}while(Serial.read()!='D');
}
delay(10);
return;
}

	
void motor::calibraciony(int A){
	if (A == 7 ){
		int cont=0;
		Serial.println("Ejecutando Barrido");
		Serial.println("Ejecutando adelante");
		digitalWrite(_ENY, LOW);
		digitalWrite(_DIRY,LOW);
		int k = 0;
		int m = 0;
		while(k<=3){
    			while(m<=100){
        	    		if(digitalRead(_STOPYf)==HIGH && digitalRead(_ENY)== LOW){
            			digitalWrite(_STEPY,HIGH);
            			delayMicroseconds(100);
            			digitalWrite(_STEPY,LOW);
            			delayMicroseconds(100);
                       		}
				else{
				digitalWrite(_ENY, HIGH);
				delay(2000);
					
					}
				m=m++;	
			}
			m=0;
			k=k++;
			delay(2000);
			
}
}
}

void motor::calibracionx(int A){
	if (A == 8 ){
		int cont=0;
		Serial.println("Ejecutando Barrido");
		Serial.println("Ejecutando adelante");
		digitalWrite(_ENX, LOW);
		digitalWrite(_DIRX,LOW);
		int k = 0;
		int m = 0;
		while(k<=3){
    			while(m<=800){
        	    		if(digitalRead(_STOPXf)==HIGH && digitalRead(_ENX)== LOW){
            			digitalWrite(_STEPX,HIGH);
            			delayMicroseconds(100);
            			digitalWrite(_STEPX,LOW);
            			delayMicroseconds(100);
                       		}
				else{
				digitalWrite(_ENX, HIGH);
				delay(2000);
					
					}
				m=m++;	
			}
			m=0;
			k=k++;
			delay(2000);
			
}
}
}

void motor::barrido(int A, int puntos, int t, int distan){
		
		int contx=0;      //variables globales de la funcion
		int contz=0;
		int conty=0;
		int maxx=puntos-1;
		int maxy=puntos-1;
		int maxz=puntos-1;
		int dist = (distan)/puntos;
		int dis=(320)*(dist);   
		int tt=t*1000;
		
			
		Serial.println("Ejecutando Barrido 3D");
		Serial.print("Numero de puntos por eje:")+Serial.println(puntos,DEC);
		Serial.print("Distancia entre puntos:")+Serial.print(dist,DEC)+Serial.println("[mm]"); 
		Serial.print("Pausa entre puntos:")+Serial.print(t,DEC)+Serial.println("[s]");
		Serial.print("Distancia total del barrido:")+Serial.print(distan,DEC)+Serial.println("[cm]");
		Serial.println("Inicio en ");
		Serial.print("3.");
		delay(333);
		Serial.print(".");
		delay(333);
		Serial.print(".");
		delay(333);
		Serial.print("2.");
		delay(333);
		Serial.print(".");
		delay(333);
		Serial.print(".");
		delay(333);
		Serial.println("1");
		delay(1000);
		Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
		delay(tt);
		
		//se debe identificar si en numero de puntos es par o impar.
		if(puntos & 0x01){//algoritmo para puntos impar
			plano1:
				adelante1:
					Serial.println("adelante1");
					digitalWrite(_ENY, LOW);
					digitalWrite(_DIRY,LOW);//Eje Y en sentido positivo
					int k = 1;
					int m = 1;
			
					while(k<=maxy+1){      //while que maneja el numero de puntos del barrido, +1 para poder ejecutar en z
						Serial.end();
						delay(10);
						Serial.begin(9600);
						
						while(Serial.available()==0){
								delayMicroseconds(10);		//pausa del programa esperando instruccion de moverse
													}
													
						switch(Serial.read()){  				  			 
						
						case 'p':  				  			 
							while(m<=dis){			//while que maneja la distancia que se recorrre en cada punto
									if(k <= maxy){ // da el paso de un punto a otro
									digitalWrite(_STEPY,HIGH);
									delayMicroseconds(100);
									digitalWrite(_STEPY,LOW);
									delayMicroseconds(100);
												}
						
									else{           // si se alcanzo el maximo de puntos en eje Y, mueve eje Z en una posicion
									digitalWrite(_ENY, HIGH);
									delay(tt);
									digitalWrite(_ENZ,LOW);
									digitalWrite(_DIRZ,LOW);
									int y=1;			
										while(y<=dis/8 && contz<=maxz){
										digitalWrite(_STEPZ,HIGH);
										delayMicroseconds(1000);
										digitalWrite(_STEPZ,LOW);
										delayMicroseconds(1000);
										y=y++;                       		              				
										}
				
									y=1;
									digitalWrite(_ENZ,HIGH);
									contz=contz++;
									Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
									goto retrocede1;	
									}
									m=m++;											
										}
			m=0;
			conty=conty++;
			Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
			k=k++;
			delay(tt);
			if(contx==maxx && conty==maxy && contz==maxz){
				goto fin;
							}
				
			if(conty==maxy && contz==maxz){
				
				Serial.end();
				delay(10);
				Serial.begin(9600);
				
				 while(Serial.available()==0){
								delayMicroseconds(10);		//pausa del programa esperando instruccion de moverse
									}
							
				digitalWrite(_ENX, LOW);
				digitalWrite(_DIRX,HIGH);
				while(m<=dis){
						digitalWrite(_STEPX,HIGH);
            			delayMicroseconds(100);
            			digitalWrite(_STEPX,LOW);
            			delayMicroseconds(100);
            			m=m++;
            			}
            contx=contx++;			
			Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
			
							
							
			k=1;
			m=1;
			delay(tt);
			goto plano2;
				
								
						}				
				
						
								
				
		 break;
			
			case 'D':
				goto fin;
				break;
			
			
		}
		}
			retrocede1:
			Serial.println("retrocede1");
					digitalWrite(_ENY, LOW);
					digitalWrite(_DIRY,HIGH);//Eje Y en sentido negativo
					k = 1;
					m = 1;
					while(k<=maxy+1){      //while que maneja el numero de puntos del barrido, +1 para poder ejecutar en z
						
						while(Serial.available()==0){
								delayMicroseconds(10);		//pausa del programa esperando instruccion de moverse
													}
													
						switch(Serial.read()){  
							
							case 'p':
								while(m<=dis){			//while que maneja la distancia que se recorrre en cada punto
									if(k <= maxy){ // da el paso de un punto a otro
									digitalWrite(_STEPY,HIGH);
									delayMicroseconds(100);
									digitalWrite(_STEPY,LOW);
									delayMicroseconds(100);
												}
						
									else{           // si se alcanzo el maximo de puntos en eje Y, mueve eje Z en una posicion
									digitalWrite(_ENY, HIGH);
									delay(tt);
									digitalWrite(_ENZ,LOW);
									digitalWrite(_DIRZ,LOW);
									int y=1;			
										while(y<=dis/8 && contz<=maxz){
										digitalWrite(_STEPZ,HIGH);
										delayMicroseconds(1000);
										digitalWrite(_STEPZ,LOW);
										delayMicroseconds(1000);
										y=y++;                       		              				
										}
				
									y=1;
									digitalWrite(_ENZ,HIGH);
									contz=contz++;
									Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
									goto adelante1;	
									}
									m=m++;											
										}
			m=1;
			conty=conty--;
			Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
			k=k++;
			delay(tt);
			break;				
				case 'D':			
						goto fin;	
						break;
					}			  			 
				}
				
			plano2:	
			Serial.println("plano2");
			retrocede2:
			Serial.println("retrocede2");
			Serial.end();
			delay(10);
			Serial.begin(9600);
					digitalWrite(_ENY, LOW);
					digitalWrite(_DIRY,HIGH);//Eje Y en sentido negativo
					k = 1;
					m = 1;
					while(k<=maxy+1){      //while que maneja el numero de puntos del barrido, +1 para poder ejecutar en z
						
						while(Serial.available()==0){
								delayMicroseconds(10);		//pausa del programa esperando instruccion de moverse
													}
													
						switch(Serial.read()){  
							
							case 'p':
								while(m<=dis){			//while que maneja la distancia que se recorrre en cada punto
									if(k <= maxy){ // da el paso de un punto a otro
									digitalWrite(_STEPY,HIGH);
									delayMicroseconds(100);
									digitalWrite(_STEPY,LOW);
									delayMicroseconds(100);
												}
						
									else{           // si se alcanzo el maximo de puntos en eje Y, mueve eje Z en una posicion
									digitalWrite(_ENY, HIGH);
									delay(tt);
									digitalWrite(_ENZ,LOW);
									digitalWrite(_DIRZ,HIGH);
									int y=1;			
										while(y<=dis/8 && contz<=maxz){
										digitalWrite(_STEPZ,HIGH);
										delayMicroseconds(1000);
										digitalWrite(_STEPZ,LOW);
										delayMicroseconds(1000);
										y=y++;                       		              				
										}
				
									y=1;
									digitalWrite(_ENZ,HIGH);
									contz=contz--;
									Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
									goto adelante2;	
									}
									m=m++;											
										}
			m=1;
			conty=conty--;
			Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
			k=k++;
			delay(tt);
			if(conty==0 && contz==0){
				Serial.end();
				delay(10);
				Serial.begin(9600);
				
								while(Serial.available()==0){
								delayMicroseconds(10);		//pausa del programa esperando instruccion de moverse
													}
						
				
				digitalWrite(_ENX, LOW);
				digitalWrite(_DIRX,HIGH);
				while(m<=dis){
						digitalWrite(_STEPX,HIGH);
            			delayMicroseconds(100);
            			digitalWrite(_STEPX,LOW);
            			delayMicroseconds(100);
            			m=m++;
            			}
            contx=contx++;			
			Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
			k=1;
			m=1;
			delay(tt);
				goto plano1;
				
				
				
				
				goto plano1;
				}
			break;				
				case 'D':			
						goto fin;	
						break;
					}			  			 
				}
				
				
				adelante2:
				Serial.println("adelante2");
					digitalWrite(_ENY, LOW);
					digitalWrite(_DIRY,LOW);//Eje Y en sentido positivo
					 k = 1; 
					 m = 1;
			
					while(k<=maxy+1){      //while que maneja el numero de puntos del barrido, +1 para poder ejecutar en z
						
						while(Serial.available()==0){
								delayMicroseconds(10);		//pausa del programa esperando instruccion de moverse
													}
													
						switch(Serial.read()){  				  			 
						
						case 'p':  				  			 
							while(m<=dis){			//while que maneja la distancia que se recorrre en cada punto
									if(k <= maxy){ // da el paso de un punto a otro
									digitalWrite(_STEPY,HIGH);
									delayMicroseconds(100);
									digitalWrite(_STEPY,LOW);
									delayMicroseconds(100);
												}
						
									else{           // si se alcanzo el maximo de puntos en eje Y, mueve eje Z en una posicion
									digitalWrite(_ENY, HIGH);
									delay(tt);
									digitalWrite(_ENZ,LOW);
									digitalWrite(_DIRZ,HIGH);
									int y=1;			
										while(y<=dis/8 && contz<=maxz){
										digitalWrite(_STEPZ,HIGH);
										delayMicroseconds(1000);
										digitalWrite(_STEPZ,LOW);
										delayMicroseconds(1000);
										y=y++;                       		              				
										}
				
									y=1;
									digitalWrite(_ENZ,HIGH);
									contz=contz--;
									Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
									goto retrocede2;	
									}
									m=m++;											
										}
			m=0;
			conty=conty++;
			Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
			k=k++;
			delay(tt);
			
			if(conty==maxy && contz==maxz){
				
				Serial.end();
				delay(10);
				Serial.begin(9600);
				
				 while(Serial.available()==0){
								delayMicroseconds(10);		//pausa del programa esperando instruccion de moverse
												}
													
						 
						
				digitalWrite(_ENX, LOW);
				digitalWrite(_DIRX,HIGH);
				while(m<=dis){
						digitalWrite(_STEPX,HIGH);
            			delayMicroseconds(100);
            			digitalWrite(_STEPX,LOW);
            			delayMicroseconds(100);
            			m=m++;
            			}
            contx=contx++;			
			Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
			k=1;
			m=1;
			delay(tt);
				goto plano1;
	
								
						}
								
			if(conty==0 && contz==0 && contx==maxx){
				goto fin;
								}					
								
								
								
								
			break;
			
			case 'D':
				goto fin;
				break;
			
			
		}
		}
				
						
			}
					
		else{ //algoritmo para puntos par
			plano1par:
				adelante1par:
					Serial.println("adelante1par");
					digitalWrite(_ENY, LOW);
					digitalWrite(_DIRY,LOW);//Eje Y en sentido negativo
					int k = 1;
            		int m = 1;
					while(k<=maxy+1){      //while que maneja el numero de puntos del barrido, +1 para poder ejecutar en z
						Serial.end();
						delay(10);
						Serial.begin(9600);
						while(Serial.available()==0){
								delayMicroseconds(10);		//pausa del programa esperando instruccion de moverse
													}
													
						switch(Serial.read()){  
							
							case 'p':
								while(m<=dis){			//while que maneja la distancia que se recorrre en cada punto
									if(k <= maxy){ // da el paso de un punto a otro
									digitalWrite(_STEPY,HIGH);
									delayMicroseconds(100);
									digitalWrite(_STEPY,LOW);
									delayMicroseconds(100);
												}
						
									else{           // si se alcanzo el maximo de puntos en eje Y, mueve eje Z en una posicion
									digitalWrite(_ENY, HIGH);
									delay(tt);
									digitalWrite(_ENZ,LOW);
									digitalWrite(_DIRZ,LOW);
									int y=1;			
										while(y<=dis/8 && contz<=maxz){
										digitalWrite(_STEPZ,HIGH);
										delayMicroseconds(1000);
										digitalWrite(_STEPZ,LOW);
										delayMicroseconds(1000);
										y=y++;                       		              				
										}
				
									y=1;
									digitalWrite(_ENZ,HIGH);
									contz=contz++;
									Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
									goto retrocede1par;	
									}
									m=m++;											
										}
			m=1;
			conty=conty++;
			Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
			k=k++;
			delay(tt);
			break;				
				case 'D':			
						goto fin;	
						break;
					}			  			 
				}
			
				retrocede1par:
					Serial.println("retrocede1par");
					digitalWrite(_ENY, LOW);
					digitalWrite(_DIRY,HIGH);//Eje Y en sentido negativo
					k = 1;
					m = 1;
			
					while(k<=maxy+1){      //while que maneja el numero de puntos del barrido, +1 para poder ejecutar en z
						Serial.end();
						delay(10);
						Serial.begin(9600);
						
						while(Serial.available()==0){
								delayMicroseconds(10);		//pausa del programa esperando instruccion de moverse
													}
													
						switch(Serial.read()){  				  			 
						
						case 'p':  				  			 
							while(m<=dis){			//while que maneja la distancia que se recorrre en cada punto
									if(k <= maxy){ // da el paso de un punto a otro
									digitalWrite(_STEPY,HIGH);
									delayMicroseconds(100);
									digitalWrite(_STEPY,LOW);
									delayMicroseconds(100);
												}
						
									else{           // si se alcanzo el maximo de puntos en eje Y, mueve eje Z en una posicion
									digitalWrite(_ENY, HIGH);
									delay(tt);
									digitalWrite(_ENZ,LOW);
									digitalWrite(_DIRZ,LOW);
									int y=1;			
										while(y<=dis/8 && contz<=maxz){
										digitalWrite(_STEPZ,HIGH);
										delayMicroseconds(1000);
										digitalWrite(_STEPZ,LOW);
										delayMicroseconds(1000);
										y=y++;                       		              				
										}
				
									y=1;
									digitalWrite(_ENZ,HIGH);
									contz=contz++;
									Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
									goto adelante1par;	
									}
									m=m++;											
										}
			m=0;
			conty=conty--;
			Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
			k=k++;
			delay(tt);
			
			
			if(conty==0 && contz==maxz){
				
				Serial.end();
				delay(10);
				Serial.begin(9600);
				
				 while(Serial.available()==0){
								delayMicroseconds(10);		//pausa del programa esperando instruccion de moverse
												}
													
						 
						
				digitalWrite(_ENX, LOW);
				digitalWrite(_DIRX,HIGH);
				while(m<=dis){
						digitalWrite(_STEPX,HIGH);
            			delayMicroseconds(100);
            			digitalWrite(_STEPX,LOW);
            			delayMicroseconds(100);
            			m=m++;
            			}
            contx=contx++;			
			Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
			
							
							
			k=1;
			m=1;
			delay(tt);
			goto plano2par;
				
								
						}				
				
						
								
				
		 break;
			
			case 'D':
				goto fin;
				break;
			
			
		}
		}
			
				
			plano2par:	
				
				Serial.println("plano2par");
				adelante2par:
				Serial.println("adelante2par");
					digitalWrite(_ENY, LOW);
					digitalWrite(_DIRY,LOW);//Eje Y en sentido positivo
					 k = 1;
					 m = 1;
			
					while(k<=maxy+1){      //while que maneja el numero de puntos del barrido, +1 para poder ejecutar en z
						Serial.end();
						delay(10);
						Serial.begin(9600);
						while(Serial.available()==0){
								delayMicroseconds(10);		//pausa del programa esperando instruccion de moverse
													}
													
						switch(Serial.read()){  				  			 
						
						case 'p':  				  			 
							while(m<=dis){			//while que maneja la distancia que se recorrre en cada punto
									if(k <= maxy){ // da el paso de un punto a otro
									digitalWrite(_STEPY,HIGH);
									delayMicroseconds(100);
									digitalWrite(_STEPY,LOW);
									delayMicroseconds(100);
												}
						
									else{           // si se alcanzo el maximo de puntos en eje Y, mueve eje Z en una posicion
									digitalWrite(_ENY, HIGH);
									delay(tt);
									digitalWrite(_ENZ,LOW);
									digitalWrite(_DIRZ,HIGH);
									int y=1;			
										while(y<=dis/8 && contz<=maxz){
										digitalWrite(_STEPZ,HIGH);
										delayMicroseconds(1000);
										digitalWrite(_STEPZ,LOW);
										delayMicroseconds(1000);
										y=y++;                       		              				
										}
				
									y=1;
									digitalWrite(_ENZ,HIGH);
									contz=contz--;
									Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
									goto retrocede2par;	
									}
									m=m++;											
										}
			m=0;
			conty=conty++;
			Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
			k=k++;
			delay(tt);
											
								
								
			break;
			
			case 'D':
				goto fin;
				break;
			
			
		}
		}
			
			
			retrocede2par:
			Serial.println("retrocede2par");
			Serial.end();
			delay(10);
			Serial.begin(9600);
					digitalWrite(_ENY, LOW);
					digitalWrite(_DIRY,HIGH);//Eje Y en sentido negativo
					k = 1;
					m = 1;
					while(k<=maxy+1){      //while que maneja el numero de puntos del barrido, +1 para poder ejecutar en z
						
						while(Serial.available()==0){
								delayMicroseconds(10);		//pausa del programa esperando instruccion de moverse
													}
													
						switch(Serial.read()){  
							
							case 'p':
								while(m<=dis){			//while que maneja la distancia que se recorrre en cada punto
									if(k <= maxy){ // da el paso de un punto a otro
									digitalWrite(_STEPY,HIGH);
									delayMicroseconds(100);
									digitalWrite(_STEPY,LOW);
									delayMicroseconds(100);
												}
						
									else{           // si se alcanzo el maximo de puntos en eje Y, mueve eje Z en una posicion
									digitalWrite(_ENY, HIGH);
									delay(tt);
									digitalWrite(_ENZ,LOW);
									digitalWrite(_DIRZ,HIGH);
									int y=1;			
										while(y<=dis/8 && contz<=maxz){
										digitalWrite(_STEPZ,HIGH);
										delayMicroseconds(1000);
										digitalWrite(_STEPZ,LOW);
										delayMicroseconds(1000);
										y=y++;                       		              				
										}
				
									y=1;
									digitalWrite(_ENZ,HIGH);
									contz=contz--;
									Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
									goto adelante2par;	
									}
									m=m++;											
										}
			m=1;
			conty=conty--;
			Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
			k=k++;
			delay(tt);
			if(conty==0 && contz==0 && contx==maxx){
			goto fin;
		}
			
			
			if(conty==0 && contz==0){
				Serial.end();
				delay(10);
				Serial.begin(9600);
				
								while(Serial.available()==0){
								delayMicroseconds(10);		//pausa del programa esperando instruccion de moverse
													}
						
				
				digitalWrite(_ENX, LOW);
				digitalWrite(_DIRX,HIGH);
				while(m<=dis){
						digitalWrite(_STEPX,HIGH);
            			delayMicroseconds(100);
            			digitalWrite(_STEPX,LOW);
            			delayMicroseconds(100);
            			m=m++;
            			}
            contx=contx++;			
			Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
			k=1;
			m=1;
			delay(tt);
				goto plano1par;
				
				
				
				

				}
			break;				
				case 'D':			
						goto fin;	
						break;
					}			  			 
				}
				
				
		
				
			
			
		}
		
		
			
fin:		
return;
}

void motor::planos(int A, int puntos, int t, int distan){
		
		int contx=0;      //variables globales de la funcion
		int contz=0;
		int conty=0;
		int maxx=puntos-1;
		int maxy=puntos-1;
		int maxz=puntos-1;
		int dist = (distan)/puntos;
		int dis=(320)*(dist);   
		int tt=t*1000;
		
			
		Serial.println("Ejecutando Barrido XZ-YZ");
		Serial.print("Numero de puntos por eje:")+Serial.println(puntos,DEC);
		Serial.print("Distancia entre puntos:")+Serial.print(dist,DEC)+Serial.println("[mm]"); 
		Serial.print("Pausa entre puntos:")+Serial.print(t,DEC)+Serial.println("[s]");
		Serial.print("Distancia total del barrido:")+Serial.print(distan,DEC)+Serial.println("[mm]");
		Serial.println("Barrido iniciado");
		Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
		delay(tt);
		
		//se debe identificar si en numero de puntos es par o impar.
		if(puntos & 0x01){//algoritmo para puntos impar
			planoYZ:
			Serial.println("Fijando plano YZ");
					digitalWrite(_ENX, LOW);
					digitalWrite(_DIRX,HIGH);//Eje X en sentido positivo
					int k = 1;
					int m = 1;
					while(k<=40){
					while(m<=320){											
									digitalWrite(_STEPX,HIGH);
									delayMicroseconds(100);
									digitalWrite(_STEPX,LOW);
									delayMicroseconds(100);
									m=m++;
												}
									m=0;			
									k=k++;
									contx=contx++;
																				}
																				
			Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
			digitalWrite(_ENX, HIGH);
			delay(1000);
	        Serial.println("Fijando cero en eje Z");
		    digitalWrite(_ENZ, LOW); 
		    digitalWrite(_DIRZ,HIGH);
		    
  	      do{ 
		
		    if(Serial.read()=='D'){
			            goto fin;
					              }
					
		if(digitalRead(_STOPZi)==HIGH && digitalRead(_ENZ)== LOW){
            			digitalWrite(_STEPZ,HIGH);
            			delayMicroseconds(1000);
            			digitalWrite(_STEPZ,LOW);
            			delayMicroseconds(1000);
                       		}
                       		
		else{
				digitalWrite(_ENZ, HIGH);
				}
	
			}while(digitalRead(_STOPZi)==HIGH);
		Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
					
		Serial.println("ya");								
		delay(1000);							
		
		adelanteYZ:
		delay(500);
					Serial.println("adelanteYZ");
					digitalWrite(_ENY, LOW);
					digitalWrite(_DIRY,LOW);//Eje Y en sentido positivo
					k = 1;
					m = 1;
			
					while(k<=maxy+1){      //while que maneja el numero de puntos del barrido, +1 para poder ejecutar en z
						Serial.end();
						delay(10);
						Serial.begin(9600);
						
						while(Serial.available()==0){
								delayMicroseconds(10);		//pausa del programa esperando instruccion de moverse
													}
													
						switch(Serial.read()){  				  			 
						
						case 'p':  				  			 
							while(m<=dis){			//while que maneja la distancia que se recorrre en cada punto
									if(k <= maxy){ // da el paso de un punto a otro
									digitalWrite(_STEPY,HIGH);
									delayMicroseconds(100);
									digitalWrite(_STEPY,LOW);
									delayMicroseconds(100);
												}
						
									else{           // si se alcanzo el maximo de puntos en eje Y, mueve eje Z en una posicion
									digitalWrite(_ENY, HIGH);
									delay(tt);
									digitalWrite(_ENZ,LOW);
									digitalWrite(_DIRZ,LOW);
									int y=1;			
										while(y<=dis/8 && contz<=maxz){
										digitalWrite(_STEPZ,HIGH);
										delayMicroseconds(1000);
										digitalWrite(_STEPZ,LOW);
										delayMicroseconds(1000);
										y=y++;                       		              				
										}
				
									y=1;
									digitalWrite(_ENZ,HIGH);
									contz=contz++;
									Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
									Serial.println("ya");
									goto retrocedeYZ;	
									}
									m=m++;											
										}
			m=0;
			conty=conty++;
			Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
			
			k=k++;
			delay(tt);
			Serial.println("ya");	
			
			
			if(conty==maxy && contz==maxz){
				
				Serial.end();
				delay(10);
				Serial.begin(9600);
				
				 while(Serial.available()==0){
								delayMicroseconds(10);		//pausa del programa esperando instruccion de moverse
												}
													
			//tengo que llevarlo al cero del plano XZ, (0,45,0)	
				do{ //lleva Y a cero
		if(Serial.read()=='D'){
			goto fin;
			} 
		digitalWrite(_DIRY,HIGH);	
		if(digitalRead(_STOPYi)==HIGH && digitalRead(_ENY)== LOW){
            			digitalWrite(_STEPY,HIGH);
            			delayMicroseconds(100);
            			digitalWrite(_STEPY,LOW);
            			delayMicroseconds(100);
                       		}
		else{
				digitalWrite(_ENY, HIGH);
				}
	
	}while(digitalRead(_STOPYi)==HIGH);	 	
	delay(500);
	conty=0;
	digitalWrite(_ENY, LOW);
	digitalWrite(_DIRY,LOW);//Eje Y en sentido positivo
					int k = 1;
					int m = 1;
					while(k<=40){
					while(m<=320){											
									digitalWrite(_STEPY,HIGH);
									delayMicroseconds(100);
									digitalWrite(_STEPY,LOW);
									delayMicroseconds(100);
									m=m++;
												}
									m=0;			
									k=k++;
									conty=conty++;
									Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
									Serial.println("ya");		
											}
			digitalWrite(_ENY, HIGH);
			delay(1000);
	     	goto planoXZ;// en realidad debe cambiar a plano XZ
										
						}				
							
								
				
		 break;
			
			case 'D':
				goto fin;
				break;
			
			
		}
		}
		
			retrocedeYZ:
			delay(500);
			Serial.println("retrocedeYZ");
					digitalWrite(_ENY, LOW);
					digitalWrite(_DIRY,HIGH);//Eje Y en sentido negativo
					k = 1;
					m = 1;
					while(k<=maxy+1){      //while que maneja el numero de puntos del barrido, +1 para poder ejecutar en z
						
						while(Serial.available()==0){
								delayMicroseconds(10);		//pausa del programa esperando instruccion de moverse
													}
													
						switch(Serial.read()){  
							
							case 'p':
								while(m<=dis){			//while que maneja la distancia que se recorrre en cada punto
									if(k <= maxy){ // da el paso de un punto a otro
									digitalWrite(_STEPY,HIGH);
									delayMicroseconds(100);
									digitalWrite(_STEPY,LOW);
									delayMicroseconds(100);
												}
						
									else{           // si se alcanzo el maximo de puntos en eje Y, mueve eje Z en una posicion
									digitalWrite(_ENY, HIGH);
									delay(tt);
									digitalWrite(_ENZ,LOW);
									digitalWrite(_DIRZ,LOW);
									int y=1;			
										while(y<=dis/8 && contz<=maxz){
										digitalWrite(_STEPZ,HIGH);
										delayMicroseconds(1000);
										digitalWrite(_STEPZ,LOW);
										delayMicroseconds(1000);
										y=y++;                       		              				
										}
				
									y=1;
									digitalWrite(_ENZ,HIGH);
									contz=contz++;
									Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
									Serial.println("ya");
									goto adelanteYZ;	
									}
									m=m++;											
										}
			m=1;
			conty=conty--;
			Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
			k=k++;
			delay(tt);
			Serial.println("ya");
			break;				
				case 'D':			
						goto fin;	
						break;
					}			  			 
				}
				
			planoXZ:
			delay(500);
			Serial.println("Fijando plano XZ");
					digitalWrite(_ENX, LOW);
					digitalWrite(_DIRX,LOW);//Eje X en sentido negativo
					k = 1;
					m = 1;
					while(k<=40){
					while(m<=320){											
									digitalWrite(_STEPX,HIGH);
									delayMicroseconds(100);
									digitalWrite(_STEPX,LOW);
									delayMicroseconds(100);
									m=m++;
												}
									
									m=0;			
									k=k++;
									contx=contx--;
									
											
											}
			Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
			delay(1000);								
			digitalWrite(_ENX, HIGH);
			Serial.println("Fijando cero en eje Z");
		    digitalWrite(_ENZ, LOW); 
		    digitalWrite(_DIRZ,HIGH);
		    
  	      do{ 
		
		    if(Serial.read()=='D'){
			            goto fin;
					              }
					
		if(digitalRead(_STOPZi)==HIGH && digitalRead(_ENZ)== LOW){
            			digitalWrite(_STEPZ,HIGH);
            			delayMicroseconds(1000);
            			digitalWrite(_STEPZ,LOW);
            			delayMicroseconds(1000);
                       		}
		else{
				digitalWrite(_ENZ, HIGH);
				}
	
			}while(digitalRead(_STOPZi)==HIGH);
		contz=0;							
											
											
			
		adelanteXZ:
		delay(500);
					Serial.println("adelanteXZ");
					digitalWrite(_ENX, LOW);
					digitalWrite(_DIRX,HIGH);//Eje X en sentido positivo
					k = 1;
					m = 1;
			
					while(k<=maxy+1){      //while que maneja el numero de puntos del barrido, +1 para poder ejecutar en z
						Serial.end();
						delay(10);
						Serial.begin(9600);
						
						while(Serial.available()==0){
								delayMicroseconds(10);		//pausa del programa esperando instruccion de moverse
													}
													
						switch(Serial.read()){  				  			 
						
						case 'p':  				  			 
							while(m<=dis){			//while que maneja la distancia que se recorrre en cada punto
									if(k <= maxy){ // da el paso de un punto a otro
									digitalWrite(_STEPX,HIGH);
									delayMicroseconds(100);
									digitalWrite(_STEPX,LOW);
									delayMicroseconds(100);
												}
						
									else{           // si se alcanzo el maximo de puntos en eje Y, mueve eje Z en una posicion
									digitalWrite(_ENX, HIGH);
									delay(tt);
									digitalWrite(_ENZ,LOW);
									digitalWrite(_DIRZ,LOW);
									int y=1;			
										while(y<=dis/8 && contz<=maxz){
										digitalWrite(_STEPZ,HIGH);
										delayMicroseconds(1000);
										digitalWrite(_STEPZ,LOW);
										delayMicroseconds(1000);
										y=y++;                       		              				
										}
				
									y=1;
									digitalWrite(_ENZ,HIGH);
									contz=contz++;
									Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
									Serial.println("ya");
									goto retrocedeXZ;	
									}
									m=m++;											
										}
			m=0;
			contx=contx++;
			Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
			k=k++;
			delay(tt);
			Serial.println("ya");	
			
			
			if(contx==maxx && contz==maxz){
				
				Serial.end();
				delay(10);
				Serial.begin(9600);
				
				 while(Serial.available()==0){
								delayMicroseconds(10);		
												}
													
					 	
	
	     	goto fin;
										
						}				
							
								
				
		 break;
			
			case 'D':
				goto fin;
				break;
			
			
		}
		}
		   
			retrocedeXZ:
			
			delay(500);
			Serial.println("retrocedeXZ");
					digitalWrite(_ENX, LOW);
					digitalWrite(_DIRX,LOW);//Eje X en sentido negativo
					k = 1;
					m = 1;
					while(k<=maxy+1){      //while que maneja el numero de puntos del barrido, +1 para poder ejecutar en z
						
						while(Serial.available()==0){
								delayMicroseconds(10);		//pausa del programa esperando instruccion de moverse
													}
													
						switch(Serial.read()){  
							
							case 'p':
								while(m<=dis){			//while que maneja la distancia que se recorrre en cada punto
									if(k <= maxy){ // da el paso de un punto a otro
									digitalWrite(_STEPX,HIGH);
									delayMicroseconds(100);
									digitalWrite(_STEPX,LOW);
									delayMicroseconds(100);
												}
						
									else{           // si se alcanzo el maximo de puntos en eje Y, mueve eje Z en una posicion
									digitalWrite(_ENX, HIGH);
									delay(tt);
									digitalWrite(_ENZ,LOW);
									digitalWrite(_DIRZ,LOW);
									int y=1;			
										while(y<=dis/8 && contz<=maxz){
										digitalWrite(_STEPZ,HIGH);
										delayMicroseconds(1000);
										digitalWrite(_STEPZ,LOW);
										delayMicroseconds(1000);
										y=y++;                       		              				
										}
				
									y=1;
									digitalWrite(_ENZ,HIGH);
									contz=contz++;
									Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
									Serial.println("ya");
									goto adelanteXZ;	
									}
									m=m++;											
										}
			m=1;
			contx=contx--;
			Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
			k=k++;
			delay(tt);
			Serial.println("ya");
			break;				
				case 'D':			
						goto fin;	
						break;
					}			  			 
				}
				
						
			}
			
		else{
			
			planoparYZ:
			Serial.println("Fijando plano par YZ");
					digitalWrite(_ENX, LOW);
					digitalWrite(_DIRX,HIGH);//Eje X en sentido positivo
					int k = 1;
					int m = 1;
					while(k<=40){
					while(m<=320){											
									digitalWrite(_STEPX,HIGH);
									delayMicroseconds(100);
									digitalWrite(_STEPX,LOW);
									delayMicroseconds(100);
									m=m++;
												}
									m=0;			
									k=k++;
									contx=contx++;
																				}
			Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
		    delay(1000);													
			digitalWrite(_ENX, HIGH);
			Serial.println("Fijando cero en eje Z");
		    digitalWrite(_ENZ, LOW); 
		    digitalWrite(_DIRZ,HIGH);
		    
  	      do{ 
		
		    if(Serial.read()=='D'){
			            goto fin;
					              }
					
		if(digitalRead(_STOPZi)==HIGH && digitalRead(_ENZ)== LOW){
            			digitalWrite(_STEPZ,HIGH);
            			delayMicroseconds(1000);
            			digitalWrite(_STEPZ,LOW);
            			delayMicroseconds(1000);
                       		}
                       		
		else{
				digitalWrite(_ENZ, HIGH);
				}
	
			}while(digitalRead(_STOPZi)==HIGH);
									
											
		Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);									
		delay(500);
		Serial.println("ya");	
		adelanteparYZ:
		           delay(500);
					Serial.println("adelanteparYZ");
					digitalWrite(_ENY, LOW);
					digitalWrite(_DIRY,LOW);//Eje Y en sentido positivo
					k = 1;
					m = 1;
			
					while(k<=maxy+1){      //while que maneja el numero de puntos del barrido, +1 para poder ejecutar en z
						Serial.end();
						delay(10);
						Serial.begin(9600);
						
						while(Serial.available()==0){
								delayMicroseconds(10);		//pausa del programa esperando instruccion de moverse
													}
													
						switch(Serial.read()){  				  			 
						
						case 'p':  				  			 
							while(m<=dis){			//while que maneja la distancia que se recorrre en cada punto
									if(k <= maxy){ // da el paso de un punto a otro
									digitalWrite(_STEPY,HIGH);
									delayMicroseconds(100);
									digitalWrite(_STEPY,LOW);
									delayMicroseconds(100);
												}
						
									else{           // si se alcanzo el maximo de puntos en eje Y, mueve eje Z en una posicion
									digitalWrite(_ENY, HIGH);
									delay(tt);
									digitalWrite(_ENZ,LOW);
									digitalWrite(_DIRZ,LOW);
									int y=1;			
										while(y<=dis/8 && contz<=maxz){
										digitalWrite(_STEPZ,HIGH);
										delayMicroseconds(1000);
										digitalWrite(_STEPZ,LOW);
										delayMicroseconds(1000);
										y=y++;                       		              				
										}
				
									y=1;
									digitalWrite(_ENZ,HIGH);
									contz=contz++;
									Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
									Serial.println("ya");
									goto retrocedeparYZ;	
									}
									m=m++;											
										}
			m=0;
			conty=conty++;
			Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
			k=k++;
			delay(tt);
			Serial.println("ya");
				
					
							
								
				
		 break;
			
			case 'D':
				goto fin;
				break;
			
			
		}
		} 	
			
			retrocedeparYZ:
			delay(500);
			Serial.println("retrocedeparYZ");
					digitalWrite(_ENY, LOW);
					digitalWrite(_DIRY,HIGH);//Eje Y en sentido negativo
					k = 1;
					m = 1;
					while(k<=maxy+1){      //while que maneja el numero de puntos del barrido, +1 para poder ejecutar en z
						
						while(Serial.available()==0){
								delayMicroseconds(10);		//pausa del programa esperando instruccion de moverse
													}
													
						switch(Serial.read()){  
							
							case 'p':
								while(m<=dis){			//while que maneja la distancia que se recorrre en cada punto
									if(k <= maxy){ // da el paso de un punto a otro
									digitalWrite(_STEPY,HIGH);
									delayMicroseconds(100);
									digitalWrite(_STEPY,LOW);
									delayMicroseconds(100);
												}
						
									else{           // si se alcanzo el maximo de puntos en eje Y, mueve eje Z en una posicion
									digitalWrite(_ENY, HIGH);
									delay(tt);
									digitalWrite(_ENZ,LOW);
									digitalWrite(_DIRZ,LOW);
									int y=1;			
										while(y<=dis/8 && contz<=maxz){
										digitalWrite(_STEPZ,HIGH);
										delayMicroseconds(1000);
										digitalWrite(_STEPZ,LOW);
										delayMicroseconds(1000);
										y=y++;                       		              				
										}
				
									y=1;
									digitalWrite(_ENZ,HIGH);
									contz=contz++;
									Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
									Serial.println("ya");
									goto adelanteparYZ;	
									}
									m=m++;											
										}
			m=1;
			conty=conty--;
			Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
			k=k++;
			delay(tt);
			Serial.println("ya");
			
			if(conty==0 && contz==maxz){
				
				Serial.end();
				delay(10);
				Serial.begin(9600);
				
				 while(Serial.available()==0){
								delayMicroseconds(10);		//pausa del programa esperando instruccion de moverse
												}
														 	
	delay(500);
	conty=0;
	digitalWrite(_ENY, LOW);
	digitalWrite(_DIRY,LOW);//Eje Y en sentido positivo
					int k = 1;
					int m = 1;
					while(k<=40){
					while(m<=320){											
									digitalWrite(_STEPY,HIGH);
									delayMicroseconds(100);
									digitalWrite(_STEPY,LOW);
									delayMicroseconds(100);
									m=m++;
												}
									m=0;			
									k=k++;
									conty=conty++;
									Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
											Serial.println("ya");
											}
			digitalWrite(_ENY, HIGH);
			delay(1000);
	     	goto planoparXZ;
										
						}	
			break;				
				case 'D':			
						goto fin;	
						break;
					}			  			 
				}
				
			planoparXZ:
			Serial.println("ya");
			delay(500);
			Serial.println("Fijando plano XZ");
					digitalWrite(_ENX, LOW);
					digitalWrite(_DIRX,LOW);//Eje X en sentido negativo
					k = 1;
					m = 1;
					while(k<=40){
					while(m<=320){											
									digitalWrite(_STEPX,HIGH);
									delayMicroseconds(100);
									digitalWrite(_STEPX,LOW);
									delayMicroseconds(100);
									m=m++;
												}
									
									m=0;			
									k=k++;
									contx=contx--;
									
											}
			Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
							
			digitalWrite(_ENX, HIGH);
			delay(1000);
	        Serial.println("Fijando cero en eje Z");
		    digitalWrite(_ENZ, LOW); 
		    digitalWrite(_DIRZ,HIGH);
		    
  	      do{ 
		
		    if(Serial.read()=='D'){
			            goto fin;
					              }
					
		if(digitalRead(_STOPZi)==HIGH && digitalRead(_ENZ)== LOW){
            			digitalWrite(_STEPZ,HIGH);
            			delayMicroseconds(1000);
            			digitalWrite(_STEPZ,LOW);
            			delayMicroseconds(1000);
                       		}
		else{
				digitalWrite(_ENZ, HIGH);
				}
	
			}while(digitalRead(_STOPZi)==HIGH);
		contz=0;							
		Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
													
											
			
		adelanteparXZ:
		
		delay(500);
					Serial.println("adelanteparXZ");
					digitalWrite(_ENX, LOW);
					digitalWrite(_DIRX,HIGH);//Eje X en sentido positivo
					k = 1;
					m = 1;
			
					while(k<=maxy+1){      //while que maneja el numero de puntos del barrido, +1 para poder ejecutar en z
						Serial.end();
						delay(10);
						Serial.begin(9600);
						
						while(Serial.available()==0){
								delayMicroseconds(10);		//pausa del programa esperando instruccion de moverse
													}
													
						switch(Serial.read()){  				  			 
						
						case 'p':  				  			 
							while(m<=dis){			//while que maneja la distancia que se recorrre en cada punto
									if(k <= maxy){ // da el paso de un punto a otro
									digitalWrite(_STEPX,HIGH);
									delayMicroseconds(100);
									digitalWrite(_STEPX,LOW);
									delayMicroseconds(100);
												}
						
									else{           // si se alcanzo el maximo de puntos en eje Y, mueve eje Z en una posicion
									digitalWrite(_ENX, HIGH);
									delay(tt);
									digitalWrite(_ENZ,LOW);
									digitalWrite(_DIRZ,LOW);
									int y=1;			
										while(y<=dis/8 && contz<=maxz){
										digitalWrite(_STEPZ,HIGH);
										delayMicroseconds(1000);
										digitalWrite(_STEPZ,LOW);
										delayMicroseconds(1000);
										y=y++;                       		              				
										}
				
									y=1;
									digitalWrite(_ENZ,HIGH);
									contz=contz++;
									Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
									Serial.println("ya");
									goto retrocedeparXZ;	
									}
									m=m++;											
										}
			m=0;
			contx=contx++;
			Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
			k=k++;
			delay(tt);
			Serial.println("ya");			
			
							
							
								
				
		 break;
			
			case 'D':
				goto fin;
				break;
			
			
		}
		}
			retrocedeparXZ:
			
			delay(500);
			Serial.println("retrocedeparXZ");
					digitalWrite(_ENX, LOW);
					digitalWrite(_DIRX,LOW);//Eje X en sentido negativo
					k = 1;
					m = 1;
					while(k<=maxy+1){      //while que maneja el numero de puntos del barrido, +1 para poder ejecutar en z
						
						while(Serial.available()==0){
								delayMicroseconds(10);		//pausa del programa esperando instruccion de moverse
													}
													
						switch(Serial.read()){  
							
							case 'p':
								while(m<=dis){			//while que maneja la distancia que se recorrre en cada punto
									if(k <= maxy){ // da el paso de un punto a otro
									digitalWrite(_STEPX,HIGH);
									delayMicroseconds(100);
									digitalWrite(_STEPX,LOW);
									delayMicroseconds(100);
												}
						
									else{           // si se alcanzo el maximo de puntos en eje Y, mueve eje Z en una posicion
									digitalWrite(_ENX, HIGH);
									delay(tt);
									digitalWrite(_ENZ,LOW);
									digitalWrite(_DIRZ,LOW);
									int y=1;			
										while(y<=dis/8 && contz<=maxz){
										digitalWrite(_STEPZ,HIGH);
										delayMicroseconds(1000);
										digitalWrite(_STEPZ,LOW);
										delayMicroseconds(1000);
										y=y++;                       		              				
										}
				
									y=1;
									digitalWrite(_ENZ,HIGH);
									contz=contz++;
									Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
									Serial.println("ya");
									goto adelanteparXZ;	
									}
									m=m++;											
										}
			m=1;
			contx=contx--;
			Serial.print(contx)+Serial.print(",")+Serial.print(conty)+Serial.print(",")+Serial.println(contz);
			k=k++;
			delay(tt);
			Serial.println("ya");
			
			if(contx==0 && contz==maxz){
				
				Serial.end();
				delay(10);
				Serial.begin(9600);
				
				 while(Serial.available()==0){
								delayMicroseconds(10);		
												}
													
					 	
	
	     	goto fin;
										
						}
			break;				
				case 'D':			
						goto fin;	
						break;
					}			  			 
				}
				
			}		
					
fin:		
return;
}

void motor::setupplano(int A){
	if(A == 7){
		paso1:
		delay(1000);
		Serial.println("Setup para medicion en planos XZ-YZ");
		delay(10);
		Serial.println("Paso 1: Sacar sonda de la camara de cavitacion manualmente");
		digitalWrite(_ENZ, LOW); 
		digitalWrite(_DIRZ,HIGH);
		do{
		if(analogRead(A13)>600){
						digitalWrite(_ENZ, LOW);
						digitalWrite(_DIRZ,HIGH);
			            digitalWrite(_STEPZ,HIGH);
            		    delayMicroseconds(1000);
            			digitalWrite(_STEPZ,LOW);
            			delayMicroseconds(1000);
					}	
					
		if(analogRead(A13)<300){
						digitalWrite(_ENZ, LOW);
						digitalWrite(_DIRZ,LOW);
			        	digitalWrite(_STEPZ,HIGH);
            			delayMicroseconds(1000);
            			digitalWrite(_STEPZ,LOW);
            			delayMicroseconds(1000);
					}
				}while(Serial.read()!='n');
				
	Serial.println("Configurando cero del Sistema camara de cavitacion en plano XY");
	delay(10);
	Serial.println("Fijando cero en eje Y");
	delay(1000);
	digitalWrite(_ENY, LOW); 
	digitalWrite(_DIRY,HIGH);	
		
	do{ 
		if(Serial.read()=='D'){
			goto salir;
			} 
			
		if(digitalRead(_STOPYi)==HIGH && digitalRead(_ENY)== LOW){
            			digitalWrite(_STEPY,HIGH);
            			delayMicroseconds(100);
            			digitalWrite(_STEPY,LOW);
            			delayMicroseconds(100);
                       		}
		else{
				digitalWrite(_ENY, HIGH);
				}
	
	}while(digitalRead(_STOPYi)==HIGH);
	 
	
	
		Serial.println("Fijando cero en eje X");
		delay(1000);
		digitalWrite(_ENX, LOW); 
		digitalWrite(_DIRX,LOW);
	do{
		if(Serial.read()=='D'){
			goto salir;
			}
			
		if(digitalRead(_STOPXi)==HIGH && digitalRead(_ENX)== LOW){
            			digitalWrite(_STEPX,HIGH);
            			delayMicroseconds(100);
            			digitalWrite(_STEPX,LOW);
            			delayMicroseconds(100);
                       		}
		else{
				digitalWrite(_ENX, HIGH);
				}
	
	}while(digitalRead(_STOPXi)==HIGH );
	

}
salir: ;
delay(10);
return;
}
