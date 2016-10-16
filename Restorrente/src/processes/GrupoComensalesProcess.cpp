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
		Semaforo* semPersonasLivingB, MemoriaCompartida<int>* shmPersonasLiving, Semaforo* semMesasLibres) {
	this->cantPersonas = cantPersonas;
	this->semComensalesEnPuerta = semComensalesEnPuerta;
	this->semRecepcionistasLibres = semRecepcionistasLibres;
	this->semPersonasLivingB = semPersonasLivingB;
	this->shmPersonasLiving = shmPersonasLiving;
	this->semMesasLibres = semMesasLibres;

	this->shmPersonasLiving->crear(SHM_PERSONAS_LIVING, 0);
}

void GrupoComensalesProcess::run(){

	sleep(20);
	cout << "DEBUG: Iniciando grupo de comensales con pid: " << getpid() << endl;


	cout << getpid() << " " << "INFO: Llega grupo de comensales" <<  endl;
	semComensalesEnPuerta->v();
	cout << getpid() << " " << "INFO: Grupo de comensales esperando recepcionista libre" << endl;
	semRecepcionistasLibres->p();
	cout << getpid() << " " << "INFO: Grupo de comensales siendo atendido" << endl;
	sleep(TIEMPO_ANTENDIENDO);

	cout << getpid() << " " << "DEBUG: Esperando semaforo personas living " << endl;
	semPersonasLivingB->p();
	cout << getpid() << " " << "DEBUG: Leyendo personas living " << endl;
	int personasLiving = shmPersonasLiving->leer();
	cout << getpid() << " " << "DEBUG: Personas en living " << personasLiving << endl;
	cout << getpid() << " " << "DEBUG: Incrementando personas living " << endl;
	shmPersonasLiving->escribir(personasLiving + 1);
	semPersonasLivingB->v();

	semMesasLibres->p();
	cout << getpid() << " " << "INFO: Grupo de comensales llendo a la mesa" << endl;


	cout << getpid() << " " << "DEBUG: Esperando semaforo personas living " << endl;
	semPersonasLivingB->p();
	cout << getpid() << " " << "DEBUG: Leyendo personas living " << endl;
	personasLiving = shmPersonasLiving->leer();
	cout << getpid() << " " << "DEBUG: Personas en living " << personasLiving << endl;
	cout << getpid() << " " << "DEBUG: Decrementando personas living " << endl;
	shmPersonasLiving->escribir(personasLiving - 1);
	semPersonasLivingB->v();

	cout << getpid() << " " << "DEBUG: Liberando memoria personas living " << endl;
	shmPersonasLiving->liberar();

/*
	//TODO Ver si hay mejor forma que while(true).
	while(true){
		//Logica de procesos
		sleep(1);
	}

*/
	//comiendo.
	sleep(10);

	cout << getpid() << " " << "INFO: Grupo de comensales se va de la mesa" << endl;
	semMesasLibres->v();

}

GrupoComensalesProcess::~GrupoComensalesProcess() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
