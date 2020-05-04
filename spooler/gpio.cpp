#include "gpio.hpp"
#include "pins.h"
#include "common.hpp"

#include <Servo.h>


volatile long encoder_delta = 0;
Servo servo;
void init_gpio()
{
  pinMode(PIN_SERVO,OUTPUT);
  servo.attach(PIN_SERVO);
  
  pinMode(PIN_MSPIN,OUTPUT);
  digitalWrite(PIN_MSPIN,LOW);
  
  pinMode(PIN_D2,OUTPUT);
  digitalWrite(PIN_D2,LOW);
  
  pinMode(PIN_D5,OUTPUT);
  digitalWrite(PIN_D5,LOW);
  
  pinMode(PIN_ENC_A,INPUT);
  pinMode(PIN_ENC_B,INPUT);
  attachInterrupt(digitalPinToInterrupt(PIN_ENC_A),isr_enc_a,CHANGE);
  
  pinMode(PIN_24VFB,INPUT);
}


float get_24vfb()
{
  return (analogRead(PIN_24VFB)/1024.0)*MAX_24VFB;
}


void write_motor(float pct)
{
  analogWrite(PIN_MSPIN,255*min(1,max(0,pct)));
}

void isr_enc_a()
{
  encoder_delta += 1-2*(digitalRead(PIN_ENC_A) xor digitalRead(PIN_ENC_B));
}

#define SERVO_ARM 50.0 //mm
#define FILAMENT_D 1.75 //mm


bool going_up = true;
float theta = 0;
float r = 0;
float y = 0;
long last_time = millis();

void reset()
{
  going_up = true;
  theta = 0;
  r = 0;
  y = 0;
  last_time = millis();
}

void run()
{
  digitalWrite(PIN_D2,running);
  write_motor(motor_speed); //without having an encoder for the motor, we'll just map speed in rpm to pwm percent...
  servo.write(servo_angle);
  
  digitalWrite(PIN_D5,!(status==STAT_OK)); //red warning light if all is not well
}

bool just_started = true;
void calculate()
{
  if (running)
  {
    if (just_started)
    {
      last_time = micros();
    }
    just_started = false;
    long dt = micros()-last_time;
    last_time = micros();
    r = max(r, spool_id);
    //filament is 1.75mm in diameter. We'll call it a square for easy math.
    

    //given a time delta in msec and a filament feed rate in mm/s, the circumferential distance traveled is (rate/dt)/1000
    float travel = (spool_speed*((float)dt))/1000000.0;
    // this means an angle of travel/r has been traveled
    theta += (travel * 360.0)/(2.0*PI*r);
    if (theta >= 360)
    {
      theta -= 360;
      //a full rotation has occurred
      if (going_up)
      {
        if (y+FILAMENT_D > spool_height)
        {
          //we're at the top
          going_up = false;
          r += FILAMENT_D;
        }
        else
        {
          y += FILAMENT_D;
        }
      }
      else
      {
        if (y - FILAMENT_D < 0)
        {
          //we're at the bottom
          going_up = true;
          r += FILAMENT_D;
        }
        else
        {
          y -= FILAMENT_D;
        }
        
      }
      if (r > spool_od)
      {
        status = STAT_FULL;
        running = false;
        motor_speed = 0;
        servo_angle = 90;
      }
    }
    motor_speed = 360.0*spool_speed/(2.0*PI*r*60.0)/50.0;
    servo_angle = degrees(atan((y-spool_height/2.0)/SERVO_ARM))+90;
  }
  else
  {
    just_started = true;
  }
  
}
