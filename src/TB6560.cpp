/*
  TB6560 - Library for controlling Stepper Motors from TB6560 3A CNC motor Driver.
  Created by Omkar N. Tulaskar, November 26, 2017.
  Released into the public domain.
*/

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include "TB6560.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//						Setting up the Arduino pins from the User

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TB6560::TB6560(int clock_pin,int direction_pin)
{
	this->clock_pin=clock_pin;
	this->direction_pin=direction_pin;
	this->last_step_time = 0; // time stamp in us of the last step taken
	
	//Setting Arduino pins connected to clock and direction as output
	pinMode(this->direction_pin,OUTPUT);
	pinMode(this->clock_pin,OUTPUT);
	
}

TB6560::TB6560(int clock_pin,int direction_pin,uint8_t number_of_steps)
{
	this->clock_pin=clock_pin;
	this->direction_pin=direction_pin;
	this->steps=number_of_steps;
	this->last_step_time = 0; // time stamp in us of the last step taken
	
	//Setting Arduino pins connected to clock and direction as output
	pinMode(this->direction_pin,OUTPUT);
	pinMode(this->clock_pin,OUTPUT);
	
}

//	For one particular direction setdirection =1 else keep it 0;
TB6560::TB6560(int clock_pin,int direction_pin,uint8_t number_of_steps,int setdirection)
{
	this->clock_pin=clock_pin;
	this->direction_pin=direction_pin;
	this->steps=number_of_steps;
	this->direction=setdirection;
	this->last_step_time = 0; // time stamp in us of the last step taken

	//Setting Arduino pins connected to clock and direction as output
	pinMode(this->direction_pin,OUTPUT);
	pinMode(this->clock_pin,OUTPUT);
	
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//											Functions for setting up the speed

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TB6560::setStepsPerRevolution(uint8_t stepsPerRevolution)
{
	this->steps=stepsPerRevolution;
}


void TB6560::setDirection(int motordirection)
{
	this-> direction=motordirection;
	
	if(this-> direction==1)
	{
		digitalWrite(this->direction_pin,HIGH);
	}
	else if(this-> direction==0)
	{
		digitalWrite(this->direction_pin,LOW);
	}
}

//		** This will set the speed in revolutions per minute **
	

void TB6560::setSpeed(long speed)
{
	this->speed=speed;
	this->clock_delay = (60L * 1000L * 1000L )/ this->steps / this->speed;
	this->clock_delay =this->clock_delay / 2;
	
}

void TB6560::start()
{
	
	 digitalWrite(this->clock_pin, HIGH);
	 delayMicroseconds(this->clock_delay);
	 digitalWrite(this->clock_pin, LOW);
	 delayMicroseconds(this->clock_delay);
}
void TB6560::stop()
{
	digitalWrite(this->clock_pin, LOW);
	delayMicroseconds(this->clock_delay);
	
}
/*
 * Moves the motor steps_to_move steps.  If the number is negative,
 * the motor moves in the reverse direction.
 */
 
 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//											  Stepping the motor

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 
 
void TB6560::step(int steps_to_move)
{
  int steps_left = abs(steps_to_move);  // how many steps to take
   // determine direction based on whether steps_to_mode is + or -:
   /*
  if (steps_to_move > 0) { 
  this->direction = 1;
  digitalWrite(this->direction_pin,HIGH);
  
	}
  if (steps_to_move < 0) { 
  this->direction = 0; 
  digitalWrite(this->direction_pin,LOW);
  }
  */

  // decrement the number of steps, moving one step each time:
  while (steps_left > 0)
  {
    unsigned long now = micros();
    // move only if the appropriate delay has passed:
    if (now - this->last_step_time >= this->clock_delay)
    {
      // get the timeStamp of when you stepped:
      this->last_step_time = now;
      // increment or decrement the step number,
      // depending on direction:
      if (this->direction == 1)
      {
        this->step_number++;
        if (this->step_number == this->number_of_steps) {
          this->step_number = 0;
        }
      }
      else
      {
        if (this->step_number == 0) {
          this->step_number = this->number_of_steps;
        }
        this->step_number--;
      }
      // decrement the steps left:
      steps_left--;
      // step the motor to step number 0, 1, ..., {3 or 10}
     start();
    }
  }
}


