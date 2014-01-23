#include "POC.h"
#include "TimerOne.h"

POC *p;
long start = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println("init complete");
  delay(250);
  p->init_timer();
}

void loop()
{
  listenSignal();
  if((start + 3000) <= millis())
  {
      start = millis();
      Serial.println("top");
  }
}

