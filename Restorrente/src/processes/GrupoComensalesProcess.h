/*
 * GrupoComensalesProcess.h
 *
 *  Created on: Oct 15, 2016
 *      Author: gaston
 */

#ifndef PROCESSES_GRUPOCOMENSALESPROCESS_H_
#define PROCESSES_GRUPOCOMENSALESPROCESS_H_

#include "../utils/ipc/semaphore/Semaforo.h"
#include "RecepcionistaProcess.h"

namespace std {

class GrupoComensalesProcess {
private:
	int cantPersonas;

	Semaforo* semRecepcionistasLibres;
	Semaforo* semComensalesEnPuerta;

public:
	GrupoComensalesProcess(int cantPersonas, Semaforo* semRecepcionistasLibres, Semaforo* semComensalesEnPuerta);
	void run();
	virtual ~GrupoComensalesProcess();
};

} /* namespace std */

#endif /* PROCESSES_GRUPOCOMENSALESPROCESS_H_ */
