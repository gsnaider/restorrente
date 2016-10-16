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
#include "../utils/ipc/pipe/Pipe.h"
#include "../model/Menu.h"
#include "RecepcionistaProcess.h"
#include "../main/MainProcess.h"


namespace std {

const double PROBABILIDAD_IRSE = 0.25;

class GrupoComensalesProcess {
private:

	int cantPersonas;
	int mesa;

	Semaforo* semRecepcionistasLibres;
	Semaforo* semComensalesEnPuerta;
	Semaforo* semPersonasLivingB;
	Semaforo* semMesasLibres;

	MemoriaCompartida<int>* shmPersonasLiving;

	Pipe* pipeLlamadosAMozos;

	vector<Semaforo*>* semsLlegoComida;
	vector<Semaforo*>* semsComidaEnMesas;
	vector<Semaforo*>* semsMesaPago;

	Menu* menu;

	void llegar();
	void comer();
	void irse();


public:
	GrupoComensalesProcess(int cantPersonas, Semaforo* semRecepcionistasLibres, Semaforo* semComensalesEnPuerta,
			Semaforo* semPersonasLivingB, MemoriaCompartida<int>* shmPersonasLiving, Semaforo* semMesasLibres,
			Pipe* pipeLlamadosAMozos, vector<Semaforo*>* semsLlegoComida, vector<Semaforo*>* semsComidaEnMesas,
			vector<Semaforo*>* semsMesaPago, Menu* menu);

	void run();
	virtual ~GrupoComensalesProcess();
};

} /* namespace std */

#endif /* PROCESSES_GRUPOCOMENSALESPROCESS_H_ */
