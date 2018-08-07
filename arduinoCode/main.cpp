/*
Libreria para el uso del prototiopo de hodoscopio SiLab 
Versión enero 2018
*/

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include "i2c_master.h"
#include "imudof.h"
#include "communication/communication.h"
#include "Servo.h"
#include "us.h"
#include "stepper.h"
#include "fdcr.h"

bool a=0;
int i=0;
float angle, lastAngle;
char *setAngC;
char *setDistC;
int angleInit, dist, lastDist;
int gate = 5;
int tot_overflow;
char dataSerial_send[38]="#f:0.000a:00.00p:00.00d:00.00x:00.00*";   
double freq;
char freq_char[6];

SerialCom uart;     // Principal UART comms 
imudof imu;         // Accelerometer, Gyroscope and Magnetometer
ultraSonic us;      // Ultrasonic distance sensor
Servo servo;        // Servo motor

void timer3_init()
{
	TCCR3B |= (1 << CS32)|(1 << CS30);          							// Set 1024 prescaling
	tot_overflow = OVERFLOW(gate);              							// Set the total overflows for a given gate time
	TCNT3 = INIT_COUNT(gate-MAX_GATE*OVERFLOW(gate))*(tot_overflow==0);     // Counter value depends on overflow value
	TIMSK3 |= (1 << TOIE3);                                                 
	sei();																	// Enable global interrupts
	tot_overflow--;
}

void timer5_init()                              // ACTIVA TIMER5 COMO reloj externo ( 110 )
{
	TCCR5B |= (1 << CS52)|(1 << CS51);          // External clock mode ------> On Pin 47 in Arduino ATMEGA1280
	TCNT5 = 0;                                  // coincidence counter
}

int main(void){
/******Object declarations******/
  
   Fdcr finButton;     // End race sensor

/******Config initializations******/

   us.init();
   uart.init(57600);   
   finButton.init(); 
   imu.init();
   timer3_init();
   timer5_init();
    
   Stepper stepx(&PORTE, &PORTE, X_DIR, X_STP, X_FdC);
   Stepper stepy(&PORTH, &PORTE, Y_DIR, Y_STP, Y_FdC);
   Stepper stepz(&PORTH, &PORTG, Z_DIR, Z_STP, Z_FdC);
   Stepper stepa(&PORTB, &PORTB, A_DIR, A_STP, A_FdC);

   servo.init();

/******Verification rutines******/
   stepx.stop();                   //Se deshabilita el shield para controlar motores stepper
    
   if (imu.testConnection()) uart.sendData("IMU connection Ok\n");
   else {uart.sendData("IMU connection error\n"); return -1;}
    
   us.sendPulse();
   us.getDistance();
   uart.sendData("Distancia inicial MPPC: ");    
   uart.sendData(us.buff);
   uart.sendData("\n");

   imu.readData();
   uart.sendData("Ángulo inicial: ");    
   uart.sendData(imu.kAccelC[2]);
   uart.sendData("\n");
   angleInit = 180 - imu.kAccelF[2]; 
   servo.begin();
   _delay_ms(4000);
   imu.readData();
   servo.goUp();
   _delay_ms(4000);
   servo.baseAngle = imu.kAccelF[2];
   servo.goDown();
   _delay_ms(4000);
   servo.baseAngle = imu.kAccelF[2];
   while(1){
       
   
   }
   return 0;
}

ISR(TIMER3_OVF_vect)
{
	TCNT3 = INIT_COUNT(gate-MAX_GATE*OVERFLOW(gate))*(tot_overflow==0);    // Counter value depends on overflow value, same as the initialization  


	if(tot_overflow<0)                                                     // Condition for send the value (gate time is reached)
	{
		freq = (float)((TCNT5)/gate);                                    
		TCNT5=0;														   // Reset the coincidence counter
		dtostrf(freq,-5, 3, (char*)freq_char);    
       
      dataSerial_send[3] = freq_char[0];
      dataSerial_send[4] = freq_char[1];
      dataSerial_send[5] = freq_char[2];
      dataSerial_send[6] = freq_char[3];
      dataSerial_send[7] = freq_char[4];

      imu.readData();
      dataSerial_send[10] = imu.kAccelC[2][0];
      dataSerial_send[11] = imu.kAccelC[2][1];
      dataSerial_send[12] = imu.kAccelC[2][2];
      dataSerial_send[13] = imu.kAccelC[2][3];
      dataSerial_send[14] = imu.kAccelC[2][4];  

      us.sendPulse();
      us.getDistance();
      dataSerial_send[24] = us.buff[0];
      dataSerial_send[25] = us.buff[1];
      dataSerial_send[26] = us.buff[2];
      dataSerial_send[27] = us.buff[3];
      dataSerial_send[28] = us.buff[4];  
  
		uart.sendData(dataSerial_send);
	
		tot_overflow=OVERFLOW(gate);                                 
	}
	tot_overflow--;
}
