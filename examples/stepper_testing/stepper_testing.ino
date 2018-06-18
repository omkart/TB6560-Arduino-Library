
/*
 Stepper Motor Control - speed control

 This program drives a unipolar or bipolar stepper motor.
 Attach your CLK+ from TB6560 to pin 9 of Arduino and pin CW+ TO pin 8
 attach CLK- and CW- to GND of Arduino.
 Do not connect the enable pins anywhere.
   Upload the sketch 
   Open your Serial monitor
   Kepp the settings to Carrriage Return in Serial Monitor Window
   Type A and press enter to make the motor rotate
   
 Created 26 Nov. 2017
 by Omkar Tulaskar

 */

#include <TB6560.h>
int distance = 0;
int start_variable =0;
TB6560 mystepper(9,8,200);
void setup() {

   Serial.begin(9600);
   Serial.println(".........................STEPPER MOTOR CONTROL USING TB6560................................");
   Serial.println("Type A and press ENTER .");

}

void loop() {
	
mystepper.setDirection(0);    		//change this to 1 to make rotation in other direction    
mystepper.setSpeed(75);				//speed in RPM : Keep the limits between 50 RPM and 150 RPM to avoid heating at low speed and slipping at high speed
if(Serial.available()>0)
  {
  start_variable = Serial.read();

  
  }
if(start_variable==65)          //check if A is sent
 {
  Serial.println("Command sent to Driver Module");
  Serial.println("Stepper Rotating...");
  
  while(distance<=2000){            // this will make stepper to rotate for 10 revolutions as 200 * 10 where 200 is the no. of steps per revolution
    
      mystepper.start();
     distance++;
     }  
  Serial.println("Stepper stopped rotating.");
  distance=0;
  start_variable=0;
  }
}