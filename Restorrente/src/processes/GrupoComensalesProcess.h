/*
 * GrupoComensalesProcess.h
 *
 *  Created on: Oct 15, 2016
 *      Author: gaston
 */

#ifndef PROCESSES_GRUPOCOMENSALESPROCESS_H_
#define PROCESSES_GRUPOCOMENSALESPROCESS_H_

#include "../utils/ipc/shared-memory/MemoriaCompartida.h"
#include "../utils/ipc/semaphore/Semaforo.h"
#include "RecepcionistaProcess.h"
#include "../main/MainProcess.h"


namespace std {

class GrupoComensalesProcess {
private:
	int cantPersonas;

	Semaforo* semRecepcionistasLibres;
	Semaforo* semComensalesEnPuerta;
	Semaforo* semPersonasLivingB;
	Semaforo* semMesasLibres;


	MemoriaCompartida<int>* shmPersonasLiving;

public:
	GrupoComensalesProcess(int cantPersonas, Semaforo* semRecepcionistasLibres, Semaforo* semComensalesEnPuerta,
			Semaforo* semPersonasLivingB, MemoriaCompartida<int>* shmPersonasLiving, Semaforo* semMesasLibres);
	void run();
	virtual ~GrupoComensalesProcess();
};

} /* namespace std */

#endif /* PROCESSES_GRUPOCOMENSALESPROCESS_H_ */
