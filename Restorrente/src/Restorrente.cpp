//============================================================================
// Name        : Restorrente.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "processes/MainProcess.h"

using namespace std;


int main() {
	//TODO Reemplazar todos los cout por el log.


	// TODO Leer de archivo de config.
	int cantMozos = 10;
	int cantRecepcionistas = 5;
	int cantMesas = 15;


	MainProcess mainProcess(cantRecepcionistas, cantMozos, cantMesas);
	mainProcess.run();


	return 0;
}
