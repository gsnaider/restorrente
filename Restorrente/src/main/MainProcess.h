/*
 * MainProcess.h
 *
 *  Created on: Oct 15, 2016
 *      Author: gaston
 */

#ifndef PROCESSES_MAINPROCESS_H_
#define PROCESSES_MAINPROCESS_H_

#include <string>
#include <vector>

#include "../utils/ipc/semaphore/Semaforo.h"

namespace std {

class MainProcess {

private:

	int cantMozos;
	int cantRecepcionistas;
	int cantMesas;
	int cantComensales;

	// TODO Deberia guardar referencias a IPCs, y tal vez tambien a los procesos hijos.
	Semaforo* semComensalesEnPuerta;
	Semaforo* semRecepcionistasLibres;
	Semaforo* semMesasLibres;
	Semaforo* semPersonasLivingB;
	Semaforo* semCajaB;
	vector<Semaforo*> semsLlegoComida;
	vector<Semaforo*> semsMesaPago;
	vector<Semaforo*> semsFacturas;

	vector<pid_t> idsRecepcionistas;
	vector<pid_t> idsMozos;
	vector<pid_t> idsComensales;
	pid_t idCocinero;

	void inicializarIPCs();

	void inicializarProcesosRestaurant();
	void iniciarProcesosMozo();
	void iniciarProcesosRecepcionista();
	void iniciarProcesoCocinero();

	void simularLlegadaComensales();

	void finalizarProcesos();


public:
	MainProcess(int cantRecepcionistas, int cantMozos, int cantMesas, int cantComensales);
	void run();
	virtual ~MainProcess();
};

} /* namespace std */

#endif /* PROCESSES_MAINPROCESS_H_ */
