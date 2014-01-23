#include "TimerOne.h"

#include "POC.h"
#include <avr/eeprom.h>

// Le numéro de la broche IO utilisée pour le module récepteur
//static uint8_t pinRx = 12;

// Le numéro de la broche IO utilisée pour le module émetteur
//static uint8_t pinTx = 10;

// Le numéro de la broche IO utilisée pour la Led de statut
//static uint8_t pinLed = 13;

// Permet la recopie du signal sur une sortie pour vérification à l'oscilloscope
//static uint8_t pinCop = 8;

// Variable d'incrementation ˆ chaque bit
static uint16_t i = 0;

// Pour activer le mode debug
static bool debugActivated = false;

// Nombre de samples sur la période en cours
volatile uint16_t counter = 0;

// La valeur du dernier sample reçu
volatile bool last_sample_value = 1;

// Le nombre de bits récupérés
static uint16_t length = 0;

// Flag pour indiquer la réception d'une trame
static uint8_t rx_active = 0;

// Indique si le bit actuel est valide
static uint8_t bit_ok = 0;

// Indique si le bit prŽcŽdent Žtait valide
static uint8_t last_bit_ok = 0;

// Tableau des valeurs
static uint16_t signal[256][2];

// Flag nouveau bit
volatile bool new_value = 0;


// Initialisation des IO avec les valeurs par défaut
POC::POC()
{
  	/*pinMode(pinRx, INPUT);
  	pinMode(pinTx, OUTPUT);
  	pinMode(pinLed, OUTPUT);
  	// Permet la recopie du signal sur une sortie pour vérification à l'oscilloscope
  	pinMode(pinCop, OUTPUT);
  	*/
  	DDRB = B00100101;
}

void timerInterrupt(){
	if(bitRead(PINB, 4) != last_sample_value)
	{
		new_value = 1;
		last_sample_value != last_sample_value;
	}
	else
	{
		counter++;
		new_value = 0;
	}
}

void POC::init_timer(){
	Timer1.initialize(10); // set a timer of length 170 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
	Timer1.attachInterrupt( timerInterrupt ); // attach the service routine here
}

void listenSignal()
{
	if(new_value == 1)
	{
		if(counter > 50)
		{
			Serial.println(counter);
			bit_ok = 1;
			//Serial.println("b");
			if(last_bit_ok == 1)
			{
				
				signal[i][0] = !last_sample_value;
				signal[i][1] = counter;
				i++;
				length = i;
				bitWrite(PORTB, 0, !last_sample_value);
				if (i == 255)
				{
					Serial.println("error");
					i = 0;
					length = i;
				}
			}
		}
		else
		{
			bit_ok = 0;
			if(length > 32)
			{
				// Fin de trame?
				//printFrame();
				Serial.println("fin");
				i = 0;
				length = i;
				return;
			}
		}
		counter = 0;
		last_bit_ok = bit_ok;
		new_value = 0;
	}
}


// Fonction pour activer le mode débug
void POC::debugMode()
{
	debugActivated = true;
}


int POC::isSignal()
{
	return rx_active;
}


void printFrame()
{
	// So, stop the interruption while sending
	Timer1.stop();
	Serial.println("Signal recorded :");
    Serial.println("--------------------------------------------");
    for (i = 0; i < length; i++)
    {
      Serial.print(signal[i][0]);
      Serial.print(":");
      Serial.print(signal[i][1]);
      if ((i+1) % 6 != 0)
      {
        Serial.print(" - ");
      }
      else
      {
        Serial.println("");
      }
    }
    Serial.println("");
    Serial.println("--------------------------------------------");
    Serial.println("Done.");
    Serial.println("");
    
    // On rŽ-initialise les variables
    i = 0;
	length = 0;
	last_bit_ok = bit_ok;
	counter = 0;
    
    // Restart the timer task
	Timer1.start();
}