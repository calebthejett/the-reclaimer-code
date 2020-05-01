
#include "i2c.h"
#include "pins.h"
#include <TinyWireS.h>

//#ifndef TWI_RX_BUFFER_SIZE
//#define TWI_RX_BUFFER_SIZE ( 16 )
//#endif

volatile uint8_t message = 0xFF;
volatile bool estop_triggered = false;
volatile bool en_120v = false;
volatile bool en_24v = false;
void setup() 
{
  TinyWireS.begin(I2C_SLAVE_ADDRESS);
  TinyWireS.onReceive(receiveEvent);
  
  pinMode(PIN_120VEN,OUTPUT);
  digitalWrite(PIN_120VEN,OFF_120VEN);
  
  pinMode(PIN_24VEN,OUTPUT);
  digitalWrite(PIN_24VEN,OFF_24VEN);
  
  pinMode(PIN_BUZZER,OUTPUT);
  digitalWrite(PIN_BUZZER,OFF_BUZZER);
  delay(500);
  digitalWrite(PIN_BUZZER,ON_BUZZER);
  delay(100);
  digitalWrite(PIN_BUZZER,OFF_BUZZER);

}

void loop() 
{
  static uint8_t beep_count = 0;
  static bool mainboard_ok = true;
  static bool ifboard_ok = true;
  static bool spoolboard_ok = true;
  
  switch (message)
  {
    case MSG_MAINBOARD_OK:
      mainboard_ok = true;
      break;
      
    case MSG_IFBOARD_OK:
      ifboard_ok = true;
      break;
      
    case MSG_SPOOLBOARD_OK:
      spoolboard_ok = true;
      break;

    case MSG_120V_ON:
      if (mainboard_ok && spoolboard_ok && ifboard_ok)
      {
        digitalWrite(PIN_120VEN,ON_120VEN);
      }
      break;
    
    case MSG_24V_ON:
      if (mainboard_ok && spoolboard_ok && ifboard_ok)
      {
        digitalWrite(PIN_24VEN,ON_24VEN);
      }
      break;

      
    case MSG_120V_OFF:
      digitalWrite(PIN_120VEN,OFF_120VEN);
      break;
      
    case MSG_24V_OFF:
      digitalWrite(PIN_24VEN,OFF_24VEN);
      break;
      
    case 0xFF:
      break;
      
    default:
      if (message >= MSG_BEEP_OFFSET)
      {
        if (message <= MSG_BEEP_OFFSET + 10)
        {
          step = 0;
          beep_count = message - MSG_BEEP_OFFSET;
        }
        else
        {
          estop();
        }
      }
      else
      {
        estop();
      }
  }
  if (beep_count)
  {
    //step 0: turn on buzzer, wait 100 msec
    //step 1: turn off buzzer, wait 400 msec
    //step 2: if == beep_count/2, wait 500 msec and set step to 0, otherwise turn on buzzer and wait 100 msec
    // repeat step 1 and 2
    static long next_time = millis();
    static uint8_t step = 0;
    if(millis() >= next_time)
    {
      if (step % 2)
      {
        digitalWrite(PIN_BUZZER,OFF_BUZZER);
        step++;
        next_time = millis()+100;
      }
      else
      {
        if (step>>1 == beep_count)
        {
          step = 0;
          next_time = millis()+500;
        }
        else
        {
          digitalWrite(PIN_BUZZER,ON_BUZZER);
          step++;
          next_time = millis()+100;
        }
      }
    }
  }
  TinyWireS_stop_check();
  
}
void estop()
{
  estop_triggered = true;
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
        estop();
      }
      else
      {
        message = min(message,recv);
      }
    }
  }
}
