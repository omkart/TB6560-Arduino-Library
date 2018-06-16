/*
  TB6560 - Library for controlling Stepper Motors from TB6560 3A CNC motor Driver.
  Created by Omkar N. Tulaskar, November 26, 2017.
  Released into the public domain.
*/

#ifndef TB6560_h
#define TB6560_h

#include "Arduino.h"


class TB6560{
	public:
	//constructors
	TB6560(int clock_pin,int direction_pin);
	TB6560(int clock_pin,int direction_pin,uint8_t number_of_steps);
	TB6560(int clock_pin,int direction_pin,uint8_t number_of_steps,int setdirection);
	void start();
	void stop();
	void setSpeed(long speed);
	void setStepsPerRevolution(uint8_t stepsPerRevolution);
	void setDirection(int motordirection);
	  void step(int number_of_steps);
	
	private :
	int clock_pin;
	int direction_pin;
	int number_of_steps; 
	int step_number; 
	
	long speed;
	uint8_t steps;
	unsigned long clock_delay;
	int direction;
	 unsigned long last_step_time;
};




#endif