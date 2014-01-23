#ifndef POC_h
#define POC_h

#include <stdlib.h>
#include <Arduino.h>

#define _DEBUG
	
void timerInterrupt();
// Ecoute le r�cepteur pour l'arriv�e d'un signal
void listenSignal();

void printFrame();

class POC
{	
public:
	// Par d�faut, le r�cepteur est en 12, l'�metteur en 10 et le pin de recopie en 8
	POC();
	
	// Pour activer le mode d�bug
	void debugMode();

	int isSignal();

	void init_timer();
	
	
	
private:

};

#endif