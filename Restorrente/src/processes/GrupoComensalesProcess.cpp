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

GrupoComensalesProcess::GrupoComensalesProcess(int cantPersonas, Semaforo* semRecepcionistasLibres, Semaforo* semComensalesEnPuerta,
		Semaforo* semPersonasLivingB, MemoriaCompartida<int>* shmPersonasLiving) {
	this->cantPersonas = cantPersonas;
	this->semComensalesEnPuerta = semComensalesEnPuerta;
	this->semRecepcionistasLibres = semRecepcionistasLibres;
	this->semPersonasLivingB = semPersonasLivingB;
	this->shmPersonasLiving = shmPersonasLiving;

	this->shmPersonasLiving->crear(SHM_PERSONAS_LIVING, 0);
}

void GrupoComensalesProcess::run(){
	cout << "Grupo de comensales con pid: " << getpid() << endl;


	cout << "Llega grupo de comensales " << getpid() <<  endl;
	semComensalesEnPuerta->v();
	cout << "Grupo de comensales " << getpid() << " esperando recepcionista libre" << endl;
	semRecepcionistasLibres->p();
	cout << "Grupo de comensales "<< getpid() << " siendo atendido" << endl;
	sleep(TIEMPO_ANTENDIENDO);

	cout << getpid() << " Esperando semaforo personas living " << endl;
	semPersonasLivingB->p();
	cout << getpid() << " Leyendo personas living " << endl;
	int personasLiving = shmPersonasLiving->leer();
	cout << getpid() << " Personas en living " << personasLiving << endl;
	cout << getpid() << " Incrementando personas living " << endl;
	shmPersonasLiving->escribir(personasLiving + 1);
	semPersonasLivingB->v();

	// TODO Esperar mesa.

	cout << getpid() << " Esperando semaforo personas living " << endl;
	semPersonasLivingB->p();
	cout << getpid() << " Leyendo personas living " << endl;
	personasLiving = shmPersonasLiving->leer();
	cout << getpid() << " Personas en living " << personasLiving << endl;
	cout << getpid() << " Decrementando personas living " << endl;
	shmPersonasLiving->escribir(personasLiving - 1);
	semPersonasLivingB->v();

	cout << getpid() << " Liberando memoria personas living " << endl;
	shmPersonasLiving->liberar();

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
