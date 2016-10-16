/*
 * MainProcess.h
 *
 *  Created on: Oct 15, 2016
 *      Author: gaston
 */

#ifndef PROCESSES_MAINPROCESS_H_
#define PROCESSES_MAINPROCESS_H_

#include <sched.h>
#include <vector>

#include "../utils/ipc/semaphore/Semaforo.h"
#include "../utils/ipc/shared-memory/MemoriaCompartida.h"

namespace std {

const string SEM_COMENSALES_EN_PUERTA_INIT_FILE = "ipc-init-files/sem_comensales_en_puerta.txt";
const string SEM_COMENSALES_PENDIENTES_INIT_FILE = "ipc-init-files/sem_comensales_pendientes.txt";
const string SEM_RECEPCIONISTAS_LIBRES_INIT_FILE = "ipc-init-files/sem_recepcionistas_libres.txt";
const string SEM_MESAS_LIBRES_INIT_FILE = "ipc-init-files/sem_mesas_libres.txt";
const string SEM_PERSONAS_LIVING_INIT_FILE = "ipc-init-files/sem_personas_living.txt";
const string SEM_CAJA_INIT_FILE = "ipc-init-files/sem_caja.txt";
const string SEM_LLEGO_COMIDA_INIT_FILE = "ipc-init-files/sem_llego_comida.txt";
const string SEM_MESA_PAGO_INIT_FILE = "ipc-init-files/sem_mesa_pago.txt";
const string SEM_FACTURA_INIT_FILE = "ipc-init-files/sem_factura.txt";

const string SHM_PERSONAS_LIVING = "ipc-init-files/shm_personas_living.txt";


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

	MemoriaCompartida<int>* shmPersonasLiving;

	void inicializarIPCs();

	void inicializarProcesosRestaurant();
	void iniciarProcesosMozo();
	void iniciarProcesosRecepcionista();
	void iniciarProcesoCocinero();

	void simularLlegadaComensales();

	void finalizarProcesosRestaurant();


public:
	MainProcess(int cantRecepcionistas, int cantMozos, int cantMesas, int cantComensales);
	void run();
	virtual ~MainProcess();
};

} /* namespace std */

#endif /* PROCESSES_MAINPROCESS_H_ */
