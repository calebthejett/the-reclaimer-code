#include "encoder.hpp"

volatile long enc_delta = 0;
volatile bool button_pressed = false;

void start_encoder()
{
  pinMode(ENC_A, INPUT_PULLUP);
  pinMode(ENC_B, INPUT_PULLUP);
  pinMode(ENC_SW, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ENC_A),isrEncoder,CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_SW),isrButton,FALLING);
}


void isrEncoder()
{
  if (((ENC_PULSE_PORT & ENC_A_MASK) == 0) == ((ENC_PULSE_PORT & ENC_B_MASK) == 0))
    enc_delta--;
  else
    enc_delta++;
}

void isrButton()
{
  button_pressed = true;
}
