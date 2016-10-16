/*
 * GrupoComensalesProcess.cpp
 *
 *  Created on: Oct 15, 2016
 *      Author: gaston
 */

#include "GrupoComensalesProcess.h"


#include <unistd.h>
#include <iostream>

namespace std {

GrupoComensalesProcess::GrupoComensalesProcess(int cantPersonas, Semaforo* semRecepcionistasLibres, Semaforo* semComensalesEnPuerta) {
	this->cantPersonas = cantPersonas;
	this->semComensalesEnPuerta = semComensalesEnPuerta;
	this->semRecepcionistasLibres = semRecepcionistasLibres;

}

void GrupoComensalesProcess::run(){
	cout << "Grupo de comensales con pid: " << getpid() << endl;


	cout << "Llega grupo de comensales " << getpid() <<  endl;
	semComensalesEnPuerta->v();
	cout << "Grupo de comensales " << getpid() << " esperando recepcionista libre" << endl;
	semRecepcionistasLibres->p();
	cout << "Grupo de comensales "<< getpid() << "siendo atendido" << endl;
	sleep(TIEMPO_ANTENDIENDO);

	//TODO Ver si hay mejor forma que while(true).
	while(true){
		//Logica de procesos
		sleep(1);
	}
}

GrupoComensalesProcess::~GrupoComensalesProcess() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
