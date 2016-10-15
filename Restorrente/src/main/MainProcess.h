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

	const string SEM_COMENSALES_EN_PUERTA_INIT_FILE = "../../ipc-init-files/sem_comensales_en_puerta.txt";
	const string SEM_RECEPCIONISTAS_LIBRES_INIT_FILE = "../../ipc-init-files/sem_recepcionistas_libres.txt";
	const string SEM_MESAS_LIBRES_INIT_FILE = "../../ipc-init-files/sem_mesas_libres.txt";
	const string SEM_CAJA_INIT_FILE = "../../ipc-init-files/sem_caja.txt";

	const string SEM_LLEGO_COMIDA_INIT_FILE = "../../ipc-init-files/sem_llego_comida.txt";
	const string SEM_MESA_PAGO_INIT_FILE = "../../ipc-init-files/sem_mesa_pago.txt";
	const string SEM_FACTURA_INIT_FILE = "../../ipc-init-files/sem_factura.txt";

	int cantMozos;
	int cantRecepcionistas;
	int cantMesas;

	// TODO Deberia guardar referencias a IPCs, y tal vez tambien a los procesos hijos.
	Semaforo* semHayComensalesEnPuerta;
	Semaforo* semRecepcionistasLibres;
	Semaforo* semMesasLibres;
	Semaforo* semPersonasLivingB;
	Semaforo* semCajaB;
	vector<Semaforo*> semsLlegoComida;
	vector<Semaforo*> semsMesaPago;
	vector<Semaforo*> semsFacturas;


	void inicializarIPCs();

	void inicializarProcesos();
	void iniciarProcesosMozo();
	void iniciarProcesosRecepcionista();
	void iniciarProcesoCocinero();




public:
	MainProcess(int cantRecepcionistas, int cantMozos, int cantMesas);
	void run();
	virtual ~MainProcess();
};

} /* namespace std */

#endif /* PROCESSES_MAINPROCESS_H_ */
