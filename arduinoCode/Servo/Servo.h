

//Servo -> Timer1 on PWM mode

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <string.h>


class Servo
{	
public: 
    int lastDuty;
    int baseAngle;
    int upperAngle;
    int init(void);   
    void on(void);
    void off(void);
    void test(void);
    int setAngle(int angle);//Angle is in degrees
    void begin();
    void end();
    void goUp();
    void goDown();
};
