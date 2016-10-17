/*
 * RecepcionistaProcess.cpp
 *
 *  Created on: Oct 15, 2016
 *      Author: gaston
 */

#include "RecepcionistaProcess.h"

#include <unistd.h>
#include <iostream>

namespace std {

RecepcionistaProcess::RecepcionistaProcess(Semaforo* semRecepcionistasLibres, Semaforo* semComensalesEnPuerta) {
	this->semRecepcionistasLibres = semRecepcionistasLibres;
	this->semComensalesEnPuerta = semComensalesEnPuerta;
}

void RecepcionistaProcess::run(){
	cout << getpid() << " " << "DEBUG: Iniciando recepcionista" << endl;

	//TODO Ver si hay mejor forma que while(true).
	while (true){
		semRecepcionistasLibres->v();
		cout << getpid() << " " << "INFO: Recepcionista esperando comensales." << endl;
		semComensalesEnPuerta->p();
		cout << getpid() << " " << "INFO: Recepcionista atendiendo grupo de comensales." << endl;
		sleep(TIEMPO_ANTENDIENDO);
	}


}

RecepcionistaProcess::~RecepcionistaProcess() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
