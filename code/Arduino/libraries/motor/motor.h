/*
  motor.h - - funciones para moter motor paso a paso

Lanzado bajo licencia Copyleft---
*/

#ifndef motor_h
#define motor_h
#include "Arduino.h"

class motor{
	public:
	 	motor(int ENX, int STEPX, int DIRX ,int ENY, int STEPY, int DIRY, int ENZ, int STEPZ, int DIRZ, 
	 	int STOPXi, int STOPXf, int STOPYi, int STOPYf, int STOPZi);

    void test_topes(int PIN_STOP);
    void barrido(int A, int puntos, int t, int distan);
		void setupx(int A);
		void setupcero(int A);
		void setupplano(int A);
  	void detener(int A);
		void barridoy(int A, int puntos, int t, int distan);
		void planos(int A, int puntos, int t, int distan);
		void modomanual(int A);
		void manualz(int A);
		void calibraciony(int A);
		void calibracionx(int A);
   
	private:  
		int _ENX;
		int _STEPX;
		int _DIRX;
		int _STOPYi;
		int _STOPYf;
		int _STOPXi;
		int _STOPXf;
		int _STOPZi;
		int _ENY;
		int _STEPY;
		int _DIRY;
		int _ENZ;
		int _STEPZ;
		int _DIRZ;
	
		
		
		
};
#endif
