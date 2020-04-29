
#include "i2c.h"
#include "pins.h"
#include <TinyWireS.h>

//#ifndef TWI_RX_BUFFER_SIZE
//#define TWI_RX_BUFFER_SIZE ( 16 )
//#endif

volatile uint8_t message = 0xFF;
volatile uint8_t estop_triggered = false;
void setup() 
{
  pinMode(PIN_24VEN,OUTPUT);
  digitalWrite(PIN_24VEN,OFF_24VEN);
  pinMode(PIN_120VEN,OUTPUT);
  digitalWrite(PIN_24VEN,OFF_120VEN);
  pinMode(PIN_BUZZER,OUTPUT);
  digitalWrite(PIN_24VEN,OFF_BUZZER);
  delay(500);
  digitalWrite(PIN_BUZZER,ON_BUZZER);
  delay(100);
  digitalWrite(PIN_BUZZER,OFF_BUZZER);

  TinyWireS.begin(I2C_SLAVE_ADDRESS);
  TinyWireS.onReceive(receiveEvent);
  //estop();
}

void loop() 
{
    TinyWireS_stop_check();
}
void estop()
{
  digitalWrite(PIN_24VEN,OFF_24VEN);
  digitalWrite(PIN_120VEN,OFF_120VEN);
  digitalWrite(PIN_BUZZER,ON_BUZZER);
  delay(1000);
  digitalWrite(PIN_BUZZER,OFF_BUZZER);
  while(true)
  {
    //SOS
    //dit dit dit
    digitalWrite(PIN_BUZZER,ON_BUZZER);
    delay(100);
    digitalWrite(PIN_BUZZER,OFF_BUZZER);
    delay(100);
    digitalWrite(PIN_BUZZER,ON_BUZZER);
    delay(100);
    digitalWrite(PIN_BUZZER,OFF_BUZZER);
    delay(100);
    digitalWrite(PIN_BUZZER,ON_BUZZER);
    delay(100);
    digitalWrite(PIN_BUZZER,OFF_BUZZER);
    delay(500);
    
    //dah dah dah
    digitalWrite(PIN_BUZZER,ON_BUZZER);
    delay(400);
    digitalWrite(PIN_BUZZER,OFF_BUZZER);
    delay(100);
    digitalWrite(PIN_BUZZER,ON_BUZZER);
    delay(400);
    digitalWrite(PIN_BUZZER,OFF_BUZZER);
    delay(100);
    digitalWrite(PIN_BUZZER,ON_BUZZER);
    delay(400);
    digitalWrite(PIN_BUZZER,OFF_BUZZER);
    delay(500);
    
    //dit dit dit
    digitalWrite(PIN_BUZZER,ON_BUZZER);
    delay(100);
    digitalWrite(PIN_BUZZER,OFF_BUZZER);
    delay(100);
    digitalWrite(PIN_BUZZER,ON_BUZZER);
    delay(100);
    digitalWrite(PIN_BUZZER,OFF_BUZZER);
    delay(100);
    digitalWrite(PIN_BUZZER,ON_BUZZER);
    delay(100);
    digitalWrite(PIN_BUZZER,OFF_BUZZER);
    delay(500);

    //rest
    delay(1000);
  }
}


void receiveEvent(uint8_t howMany)
{
  if (!estop_triggered)
  {
    for(int i = 0; i < howMany; i++)
    {
      uint8_t recv = TinyWireS.receive();
      if (recv == MSG_ESTOP)
      {
        estop_triggered = true;
        estop();
      }
    }
  }
}
