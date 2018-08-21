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

#define DIRECCTION_UP 1
#define DIRECCTION_DOWN 0

bool a=0;
int i=0;
float angle, lastAngle;
char *setAngC;
char *setDistC;
int angleInit, dist, lastDist;
float gate = 5;
char gateC[10];
int tot_overflow;
char dataSerial_send[38]="#f:0.000a:00.00p:00.00d:00.00x:00.00*";   
double freq;
char freq_char[6];
bool movingServo = true;
bool movingServoSend = true;
bool changeMovingServo = false;
bool canSendData = false;
char newAngleServoC[10];
float newAngleServo = 0;

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
   uart.sendData(imu.angleC);
   uart.sendData("\n");
   servo.begin();
   _delay_ms(4000);
   imu.readData();
   if(imu.angleF < -1.0){
      while(imu.angleF < -1.0){
         servo.goUp();  
         _delay_ms(200);   
         imu.readData();
      }
   }else if(imu.angleF > 1.0){
      while(imu.angleF < 179.0){
         servo.goDown();  
         _delay_ms(200);   
         imu.readData();
      }
   }
   _delay_ms(4000); 
   movingServo = false;
   while(1){
      //uart.sendData("whike") ;
      _delay_ms(100);
      if(movingServo){
         uart.sendData("moving") ;
         imu.readData();
         if(newAngleServo < imu.angleF){
            while (newAngleServo < imu.angleF && movingServo){
               servo.goDown();  
               _delay_ms(100);   
               imu.readData();
            }
            if(!changeMovingServo)movingServo = false;
            else changeMovingServo = false;
         }else{
            while (newAngleServo > imu.angleF && movingServo){
               servo.goUp();  
               _delay_ms(100);   
               imu.readData();
            }
            if(!changeMovingServo)movingServo = false;
            else changeMovingServo = false;
         }
      }
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
      
      if(!movingServoSend)   uart.sendData(dataSerial_send);
      else if(!movingServo)  movingServoSend = false; 
      uart_flush();
	
		tot_overflow=OVERFLOW(gate);                                 
	}
	tot_overflow--;
   uart_flush(); 
   _delay_ms(200); 
   uart.sendData("R") ;
   uart.readData();
   if(uart.kBuffer[0] == 'a'){
      if(movingServo) changeMovingServo = true;
      else movingServo = true;
      int i = 2;
      while (uart.kBuffer[i] != '\0'){
         newAngleServoC[i-2] = uart.kBuffer[i];
         i++; 
      }
      newAngleServoC[i-2] = '\0';
      newAngleServo = atof(newAngleServoC);
      if(newAngleServo < 0.0 || newAngleServo > 90.0){
         movingServo = false;
      }
   }
   if(movingServo) movingServoSend = movingServo;

   if(uart.kBuffer[0] == 'g'){
      int i = 2;
      while (uart.kBuffer[i] != '\0'){
         gateC[i-2] = uart.kBuffer[i];
         i++; 
      }
      gateC[i-2] = '\0';
      if(atoi(gateC) > 0){
         gate = atoi(gateC);
         tot_overflow=OVERFLOW(gate);
         tot_overflow--;
      }
   }
}
