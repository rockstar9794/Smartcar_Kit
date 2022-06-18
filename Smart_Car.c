#include <stdio.h>
#include <wiringPi.h>
#include <stdbool.h>
#include <softPwm.h>

#define LEFT_TRACER_PIN 10
#define RIGHT_TRACER_PIN 11


#define IN1_PIN		1
#define IN2_PIN		4
#define IN3_PIN		5
#define IN4_PIN		6

#define MAX_SPEED 60
#define MIN_SPEED 0

#define LEFT_IR_PIN 27
#define RIGHT_IR_PIN 26


#define TRIG_PIN		28
#define ECHO_PIN		29

void initIR();
void initLineTacer();
void initDCMotor();
void goForward();
void goBackward();
void smoothLeft();
void smoothRight();
void stopDCMotor();
void slow();
void smoothBackLeft();

void initUltrasonic();
void lineTracerDetect();

int dist;
int leftTracer;
int rightTracer;
bool test1;
int LValue, RValue; 

int k = 1;

int main(void) {

    if (wiringPiSetup() == -1)
        return 0;

    initLineTacer();
    
    initIR();
    initDCMotor();
    test1 = false;
    
    int k=1;

    
    while (1) {

       LValue = digitalRead(LEFT_IR_PIN);
             	
        if(LValue == 0 && test1 == false) {
				while(k<=1) {
					LValue = digitalRead(LEFT_IR_PIN);
					
					if(LValue == 0) {
						printf("STOP: Distance less then 15cm\n");
						stopDCMotor();
						delay(4500);
						test1 = true;
						
						k=2;
					} else {
					
					lineTracerDetect();	
					}
					
				}
				while(k==2) {
					LValue = digitalRead(LEFT_IR_PIN);
					
					if(LValue == 0) {
						printf("STOP: Distance less then 15cm\n");
						stopDCMotor();
						
						smoothRight();
						delay(470);
						
						goForward();
						delay(400);
						
						smoothLeft();
						delay(500);
						
						goForward();
						delay(1500);
						
						smoothLeft();
						delay(320);
						
						goForward();
						delay(300);
						
						
						test1 = true;
						break;
					} else {
					
					lineTracerDetect();	
					}
					
				}
				
        }  else if (LValue == 0 && test1 == true) {
			printf("STOP: Distance less then 15cm\n");
			stopDCMotor();
			delay(200);
			smoothLeft();
			delay(500);
			goForward();
			delay(1200);
			
			stopDCMotor();
			delay(90);
			printf("Parking is Done\n");
			break;
			return 0;
			
		} else if (LValue == 1) {
		lineTracerDetect();
		
	} else {
	
	return 0;	
	}
}
}

void initIR()
{
    pinMode(LEFT_IR_PIN, INPUT);
    pinMode(RIGHT_IR_PIN, INPUT);
		
}

void initLineTacer() {
    pinMode(LEFT_TRACER_PIN, INPUT);
    pinMode(RIGHT_TRACER_PIN, INPUT);
}


void initDCMotor()
{
pinMode(IN1_PIN,SOFT_PWM_OUTPUT);
pinMode(IN2_PIN,SOFT_PWM_OUTPUT);
pinMode(IN3_PIN,SOFT_PWM_OUTPUT);
pinMode(IN4_PIN,SOFT_PWM_OUTPUT);
 
softPwmCreate(IN1_PIN, MIN_SPEED, MAX_SPEED);
softPwmCreate(IN2_PIN, MIN_SPEED, MAX_SPEED);
softPwmCreate(IN3_PIN, MIN_SPEED, MAX_SPEED);
softPwmCreate(IN4_PIN, MIN_SPEED, MAX_SPEED);
}

void slow(){
  
softPwmWrite(IN1_PIN, 30);
softPwmWrite(IN2_PIN, MIN_SPEED);
softPwmWrite(IN3_PIN, 30);
softPwmWrite(IN4_PIN, MIN_SPEED);
printf("Slow\n");
  
  }

void goForward()
{	
softPwmWrite(IN1_PIN, MAX_SPEED);
softPwmWrite(IN2_PIN, MIN_SPEED);
softPwmWrite(IN3_PIN, MAX_SPEED);
softPwmWrite(IN4_PIN, MIN_SPEED);
}

void goBackward()	
{
softPwmWrite(IN1_PIN, MIN_SPEED);
softPwmWrite(IN2_PIN, MAX_SPEED);
softPwmWrite(IN3_PIN, MIN_SPEED);
softPwmWrite(IN4_PIN, MAX_SPEED);
printf("Back\n");
}
	
	
void smoothLeft()
{
softPwmWrite(IN1_PIN, MIN_SPEED);
softPwmWrite(IN2_PIN, MAX_SPEED);
softPwmWrite(IN3_PIN, MAX_SPEED);
softPwmWrite(IN4_PIN, MIN_SPEED);
//printf("SmoothLeft\n");
}

void smoothRight()
{
softPwmWrite(IN1_PIN, MAX_SPEED);
softPwmWrite(IN2_PIN, MIN_SPEED);
softPwmWrite(IN3_PIN, MIN_SPEED);
softPwmWrite(IN4_PIN, MAX_SPEED);
//printf("SmoothRight\n");
}

void smoothBackLeft(){
softPwmWrite(IN1_PIN, MIN_SPEED);
softPwmWrite(IN2_PIN, MAX_SPEED/2); 
softPwmWrite(IN3_PIN, MIN_SPEED);
softPwmWrite(IN4_PIN, MAX_SPEED);
}

void smoothBackRight(){
softPwmWrite(IN1_PIN, MIN_SPEED);
softPwmWrite(IN2_PIN, MAX_SPEED); 
softPwmWrite(IN3_PIN, MIN_SPEED);
softPwmWrite(IN4_PIN, MAX_SPEED/2);
printf("smoothBackRight\n");
}

void stopDCMotor()
{
softPwmWrite(IN1_PIN, MIN_SPEED);
softPwmWrite(IN2_PIN, MIN_SPEED);
softPwmWrite(IN3_PIN, MIN_SPEED);
softPwmWrite(IN4_PIN, MIN_SPEED);		
printf("Stop\n");
}


void lineTracerDetect(){
	
 leftTracer = digitalRead(LEFT_TRACER_PIN);
 rightTracer = digitalRead(RIGHT_TRACER_PIN);
	
	
	if (leftTracer == 0 && rightTracer == 1) {
            printf("Right\n");
			smoothRight();
			delay(1);


        }
        else if (rightTracer == 0 && leftTracer == 1) {
            printf("Left\n");
			smoothLeft();
			delay(1);


        }
       
			        
        else if (rightTracer == 1 && leftTracer == 1) {
            printf("Forward\n");
			goForward();
			delay(5);
			
        }
		
	
	}
