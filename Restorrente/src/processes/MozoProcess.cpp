/*
 * MozoProcess.cpp
 *
 *  Created on: Oct 15, 2016
 *      Author: gaston
 */

#include "MozoProcess.h"

#include <unistd.h>
#include <iostream>

namespace std {

MozoProcess::MozoProcess(Pipe* pipeLlamadosAMozos, Pipe* pipePedidosACocinar, vector<Semaforo*>* semsComidaEnMesas,
		vector<MemoriaCompartida<Comida>*>* shmComidaEnMesas, vector<Semaforo*>* semsLlegoComida,
		vector<Semaforo*>* semsFacturas, vector<MemoriaCompartida<double>*>* shmFacturas,
		Semaforo* semCajaB, MemoriaCompartida<double>* shmCaja, vector<Semaforo*>* semsMesaPago) {

	this->pipeLlamadosAMozos = pipeLlamadosAMozos;
	this->pipePedidosACocinar = pipePedidosACocinar;
	this->semsComidaEnMesas = semsComidaEnMesas;
	this->shmComidaEnMesas = shmComidaEnMesas;
	this->semsLlegoComida = semsLlegoComida;
	this->semsFacturas = semsFacturas;
	this->shmFacturas = shmFacturas;
	this->semCajaB = semCajaB;
	this->shmCaja = shmCaja;
	this->semsMesaPago = semsMesaPago;

}

void MozoProcess::run(){
	cout << "Mozo con pid: " << getpid() << endl;

	//TODO Ver si hay mejor forma que while(true).
	while(true){
		//TODO Agregar logica de proceso
		sleep(1);
	}
}

MozoProcess::~MozoProcess() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
