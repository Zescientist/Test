#ifndef POC_h
#define POC_h

#include <stdlib.h>
#include <Arduino.h>

#define _DEBUG
	
void timerInterrupt();
// Ecoute le récepteur pour l'arrivée d'un signal
void listenSignal();

void printFrame();

class POC
{	
public:
	// Par dŽfaut, le rŽcepteur est en 12, l'Žmetteur en 10 et le pin de recopie en 8
	POC();
	
	// Pour activer le mode débug
	void debugMode();

	int isSignal();

	void init_timer();
	
	
	
private:

};

#endif