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
	cout << "Iniciando recepcionista con pid: " << getpid() << endl;

	//TODO Ver si hay mejor forma que while(true).
//	while (true){
		cout << "Recepcionista " << getpid() << " esperando comensales." << endl;
		semComensalesEnPuerta->p();
		cout << "Recepcionista " << getpid() << " atendiendo grupo de comensales." << endl;
		sleep(TIEMPO_ANTENDIENDO);
		semRecepcionistasLibres->v();
//	}


}

RecepcionistaProcess::~RecepcionistaProcess() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
