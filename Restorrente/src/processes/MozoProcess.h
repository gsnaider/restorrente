/*
 * MozoProcess.h
 *
 *  Created on: Oct 15, 2016
 *      Author: gaston
 */

#ifndef PROCESSES_MOZOPROCESS_H_
#define PROCESSES_MOZOPROCESS_H_

#include <vector>

#include "../model/Pedido.h"
#include "../model/Comida.h"
#include "../model/PedidoCuenta.h"
#include "../utils/ipc/semaphore/Semaforo.h"
#include "../utils/ipc/pipe/Pipe.h"
#include "../utils/ipc/shared-memory/MemoriaCompartida.h"
#include "../main/MainProcess.h"

class Pipe;

namespace std {

class MozoProcess {
private:

	Semaforo* semLlamadosAMozos;
	Pipe* pipeLlamadosAMozos;
	Pipe* pipePedidosACocinar;

	vector<Semaforo*>* semsComidaEnMesas;
	vector<MemoriaCompartida<Comida>*>* shmComidaEnMesas;
	vector<Semaforo*>* semsLlegoComida;

	vector<Semaforo*>* semsFacturas;
	vector<MemoriaCompartida<double>*>* shmFacturas;

	Semaforo* semCajaB;
	MemoriaCompartida<double>* shmCaja;

	vector<Semaforo*>* semsMesaPago;

	void procesarPedido(Pedido pedido);
	void procesarComida(Comida comida);
	void procesarPedidoCuenta(PedidoCuenta pedidoCuenta);


	void inicializarMemoriasCompartidas();

	int leerTamanioLlamado();
	string leerLlamado(int tamanioLlamado);

	void liberarMemoriasCompartidas();

public:
	MozoProcess(Pipe* pipeLlamadosAMozos, Pipe* pipePedidosACocinar, Semaforo* semLlamadosAMozos, vector<Semaforo*>* semsComidaEnMesas,
	vector<MemoriaCompartida<Comida>*>* shmComidaEnMesas, vector<Semaforo*>* semsLlegoComida,
	vector<Semaforo*>* semsFacturas, vector<MemoriaCompartida<double>*>* shmFacturas,
	Semaforo* semCajaB, MemoriaCompartida<double>* shmCaja, vector<Semaforo*>* semsMesaPago);
	void run();
	virtual ~MozoProcess();
};

} /* namespace std */

#endif /* PROCESSES_MOZOPROCESS_H_ */
