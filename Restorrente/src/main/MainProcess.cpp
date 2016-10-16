/*
 * MainProcess.cpp
 *
 *  Created on: Oct 15, 2016
 *      Author: gaston
 */

#include "MainProcess.h"

#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>

#include "../processes/CocineroProcess.h"
#include "../processes/MozoProcess.h"
#include "../processes/RecepcionistaProcess.h"

namespace std {

const string SEM_COMENSALES_EN_PUERTA_INIT_FILE = "ipc-init-files/sem_comensales_en_puerta.txt";
const string SEM_RECEPCIONISTAS_LIBRES_INIT_FILE = "ipc-init-files/sem_recepcionistas_libres.txt";
const string SEM_MESAS_LIBRES_INIT_FILE = "ipc-init-files/sem_mesas_libres.txt";
const string SEM_PERSONAS_LIVING_INIT_FILE = "ipc-init-files/sem_personas_living.txt";
const string SEM_CAJA_INIT_FILE = "ipc-init-files/sem_caja.txt";
const string SEM_LLEGO_COMIDA_INIT_FILE = "ipc-init-files/sem_llego_comida.txt";
const string SEM_MESA_PAGO_INIT_FILE = "ipc-init-files/sem_mesa_pago.txt";
const string SEM_FACTURA_INIT_FILE = "ipc-init-files/sem_factura.txt";


MainProcess::MainProcess(int cantRecepcionistas, int cantMozos, int cantMesas) {
	this->cantRecepcionistas = cantRecepcionistas;
	this->cantMozos = cantMozos;
	this->cantMesas = cantMesas;
	inicializarIPCs();
}

void MainProcess::iniciarProcesoCocinero(){
	cout << "Iniciando cocinero"<< endl;
	pid_t idCocinero = fork();

	if (idCocinero == 0){
		CocineroProcess cocinero;
		cocinero.run();
		exit(0);
	}
}

void MainProcess::iniciarProcesosMozo(){
	for (int i = 0; i < cantMozos; i++){
		cout << "Iniciando mozo " << i << endl;

		pid_t idMozo = fork();

		if (idMozo == 0){
			MozoProcess mozo;
			mozo.run();
			exit(0);
		}

	}
}

void MainProcess::iniciarProcesosRecepcionista(){
	for (int i = 0; i < cantRecepcionistas; i++){
		cout << "Iniciando recepcionista " << i << endl;
		pid_t idRecepcionista = fork();

		if (idRecepcionista == 0){
			RecepcionistaProcess recepcionista(semRecepcionistasLibres, semComensalesEnPuerta);
			recepcionista.run();
			exit(0);
		}
	}
}

void MainProcess::inicializarProcesos(){
	iniciarProcesosRecepcionista();
	iniciarProcesosMozo();
	iniciarProcesoCocinero();
}

void MainProcess::inicializarIPCs(){
	semComensalesEnPuerta = new Semaforo(SEM_COMENSALES_EN_PUERTA_INIT_FILE, 0, 0);
	semRecepcionistasLibres = new Semaforo(SEM_RECEPCIONISTAS_LIBRES_INIT_FILE, cantRecepcionistas, 0);
	semMesasLibres = new Semaforo(SEM_MESAS_LIBRES_INIT_FILE, cantMesas, 0);
	semPersonasLivingB = new Semaforo(SEM_PERSONAS_LIVING_INIT_FILE, 0, 0);
	semCajaB = new Semaforo(SEM_CAJA_INIT_FILE, 0, 0);

	for(int i = 0; i < cantMesas; i++){
		semsLlegoComida.push_back(new Semaforo(SEM_LLEGO_COMIDA_INIT_FILE, 0, i));
		semsMesaPago.push_back(new Semaforo(SEM_MESA_PAGO_INIT_FILE, 0, i));
		semsFacturas.push_back(new Semaforo(SEM_FACTURA_INIT_FILE, 1, i));
	}

}

void MainProcess::run(){

	inicializarProcesos();


	cout << "Llega un comensal" << endl;
	semComensalesEnPuerta->v();
	semRecepcionistasLibres->p();
	cout << "Comensal siendo atendido" << endl;
	sleep(TIEMPO_ANTENDIENDO);


	for (int i = 0; i < cantRecepcionistas + cantMozos + 1; i++){
		pid_t idHijo = wait(NULL);
		cout << "Termino proceso hijo: " << idHijo << endl;
	}

}

MainProcess::~MainProcess() {

	semComensalesEnPuerta->eliminar();
	delete semComensalesEnPuerta;

	semRecepcionistasLibres->eliminar();
	delete semRecepcionistasLibres;

	semMesasLibres->eliminar();
	delete semMesasLibres;

	semPersonasLivingB->eliminar();
	delete semPersonasLivingB;

	semCajaB->eliminar();
	delete semCajaB;

	for(int i = 0; i < cantMesas; i++){
		semsLlegoComida[i]->eliminar();
		delete semsLlegoComida[i];

		semsMesaPago[i]->eliminar();
		delete semsMesaPago[i];

		semsFacturas[i]->eliminar();
		delete semsFacturas[i];
	}

}

} /* namespace std */
