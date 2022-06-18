#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

#define MAX_SPEED 60
#define MIN_SPEED 0

#define TRIG_PIN		28
#define ECHO_PIN		29

#define IN1_PIN		1
#define IN2_PIN		4
#define IN3_PIN		5
#define IN4_PIN		6


void initUltrasonic();

void initDCMotor();
void goForward();
void goBackward();
void goLeft();
void goRight();
void stopDCMotor();
int getDistance();

int dist;
 int k = 1;
int main(void)
{
	if(wiringPiSetup() == -1)
		return 0;
	
    initUltrasonic();
    initDCMotor();
   int k = 1;
//First Box	
	while(k<=1)
	{
        
	dist = getDistance();
	

               
        if(dist <= 25){
            stopDCMotor();
            printf("STOP: 1-distance is less than 25cm\n");
            delay(500);
          
            goRight();
            delay(350);
            goForward();          
            delay(800);
          
            goLeft();
            delay(510);
          
            goForward();
            delay(600);
            k=2;
                        
        } else {
          goForward(); 
		}								
	}
	
// Second Box	
	while(k<=2)
	{
        
	dist = getDistance();
	

               
        if(dist <= 25){
            stopDCMotor();
            printf("STOP: 2-distance is less than 25cm\n");
            delay(500);
            
            goRight();
            delay(350);
          
            goForward();
			      delay(400);
          
			      goLeft();
			      delay(510);
          
			      goForward();
			      delay(1400);
          
			      goLeft();
			      delay(510);
          
			      goForward();
			      k=3;
            
        } else {
          goForward();}								
	}
	
// Third Box
	while(k<=3)
	{
        
	dist = getDistance();
	

               
        if(dist <= 25){
            stopDCMotor();
            printf("STOP: 3-distance is less than 25cm\n");
            delay(500);
           
            goRight();
            delay(350);
          
            goForward();
			      delay(400);
          
			      goLeft();
			      delay(510);
          
			      goForward();
			      delay(1400);
          
			      goLeft();
			      delay(510);
          
			      goForward();
			      k=4;
          
        } else {
          goForward();}								
	}
	
// Fourth Box
	while(k<=4)
	{        
	dist = getDistance();
	               
        if(dist <= 25){
            stopDCMotor();
            printf("STOP: 4-distance is less than 25cm\n");
            delay(500);
            
            goRight();
            delay(350);
          
            goForward();
			      delay(400);
          
			      goLeft();
			      delay(510);
          
			      goForward();
			      delay(1400);
          
			      goLeft();
			      delay(510);
          
			      goForward();
            k=5;
            
        } else {
          goForward();}								
	}
	
//Fifth Box	
	while(k<=5)
	{
        
	dist = getDistance();
	               
        if(dist <= 25){
            stopDCMotor();
            printf("STOP: 5-distance is less than 25cm\n");
            delay(500);
            
            goRight();
            delay(350);
          
            goForward();
			      delay(400);
          
			      goLeft();
			      delay(510);
          
			      goForward();
			      delay(400);
          
			      goRight();
			      delay(350);
          
			      goForward();
			      delay(500);
			      stopDCMotor();			
            
        } else {
		    goForward();
        }
    break;								
	}			
	return 0;
}


void initUltrasonic(){
    pinMode(TRIG_PIN, OUTPUT);
	pinMode(ECHO_PIN, INPUT);

}

int getDistance()
{
	int 		start_time=0, end_time=0;
	float 	distance=0;

    digitalWrite(TRIG_PIN, LOW) ;
    delay(500) ;
    digitalWrite(TRIG_PIN, HIGH) ;
    delayMicroseconds(10) ;
    digitalWrite(TRIG_PIN, LOW) ;
    
    while (digitalRead(ECHO_PIN) == 0) ;
    start_time = micros() ;
    
    while (digitalRead(ECHO_PIN) == 1) ;
    end_time = micros() ;
    
    distance = (end_time - start_time) / 29. / 2. ;
	
	return (int)distance;
}

void initDCMotor()
{
    	
	pinMode(IN1_PIN, OUTPUT);
	pinMode(IN2_PIN, OUTPUT);
	pinMode(IN3_PIN, OUTPUT);
	pinMode(IN4_PIN, OUTPUT);
	
	digitalWrite(IN1_PIN, HIGH);
	digitalWrite(IN2_PIN, HIGH);
	digitalWrite(IN3_PIN, HIGH);
	digitalWrite(IN4_PIN, HIGH);						
}


void goForward()
{
		digitalWrite(IN1_PIN, HIGH);
		digitalWrite(IN2_PIN, LOW);
		digitalWrite(IN3_PIN, HIGH);
		digitalWrite(IN4_PIN, LOW);	
		printf("Forward\n");
}	

void goBackward()
{
		digitalWrite(IN1_PIN, LOW);
		digitalWrite(IN2_PIN, HIGH);
		digitalWrite(IN3_PIN, LOW);
		digitalWrite(IN4_PIN, HIGH);		
		printf("Backwrad\n");
}	
	
	
void goLeft()
{
		digitalWrite(IN1_PIN, LOW);
		digitalWrite(IN2_PIN, HIGH);
		digitalWrite(IN3_PIN, HIGH);
		digitalWrite(IN4_PIN, LOW);	
		printf("Left\n");
}	

void goRight()
{
		digitalWrite(IN1_PIN, HIGH);
		digitalWrite(IN2_PIN, LOW);
		digitalWrite(IN3_PIN, LOW);
		digitalWrite(IN4_PIN, HIGH);		
		printf("Right\n");
}	

void stopDCMotor()
{
		digitalWrite(IN1_PIN, LOW);
		digitalWrite(IN2_PIN, LOW);
		digitalWrite(IN3_PIN, LOW);
		digitalWrite(IN4_PIN, LOW);		
		printf("Stop\n");
}
