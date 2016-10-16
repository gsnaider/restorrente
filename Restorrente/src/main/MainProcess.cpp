/*
 * MainProcess.cpp
 *
 *  Created on: Oct 15, 2016
 *      Author: gaston
 */

#include "MainProcess.h"

#include <unistd.h>
#include <csignal>
#include <cstdlib>
#include <iostream>

#include "../processes/CocineroProcess.h"
#include "../processes/GrupoComensalesProcess.h"
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


MainProcess::MainProcess(int cantRecepcionistas, int cantMozos, int cantMesas, int cantComensales) {
	this->cantRecepcionistas = cantRecepcionistas;
	this->cantMozos = cantMozos;
	this->cantMesas = cantMesas;
	this->cantComensales = cantComensales;
	inicializarIPCs();
}

void MainProcess::iniciarProcesoCocinero(){
	cout << "Iniciando cocinero"<< endl;
	pid_t idCocinero = fork();

	if (idCocinero == 0){
		CocineroProcess cocinero;
		cocinero.run();
		exit(0);
	} else {
		this->idCocinero = idCocinero;
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
		} else {
			idsMozos.push_back(idMozo);
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
		} else {
			idsRecepcionistas.push_back(idRecepcionista);
		}
	}
}

void MainProcess::inicializarProcesosRestaurant(){
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

void MainProcess::finalizarProcesos(){

	for (unsigned int i = 0; i < idsRecepcionistas.size(); i++){
		kill(idsRecepcionistas[i], 9);
	}

	for (unsigned int i = 0; i < idsMozos.size(); i++){
		kill(idsMozos[i], 9);
	}

	for (unsigned int i = 0; i < idsComensales.size(); i++){
		kill(idsComensales[i], 9);
	}

	kill(idCocinero, 9);


}

void MainProcess::simularLlegadaComensales(){
	for (int i = 0; i < cantComensales; i++){

		cout << "Iniciando comensal " << i << endl;
		pid_t idComensal = fork();

		if (idComensal == 0){
			GrupoComensalesProcess grupoComensalesProcess(4, semRecepcionistasLibres, semComensalesEnPuerta);
			grupoComensalesProcess.run();
			exit(0);
		} else {
			idsComensales.push_back(idComensal);
		}

	}

}

void MainProcess::run(){

	inicializarProcesosRestaurant();


	simularLlegadaComensales();

	//TODO Habria que llevar la cuenta de los comensales que faltan por comer, y ahi hacer terminar todos los procesos.
	sleep(60);

	finalizarProcesos();

	/*
	for (int i = 0; i < cantRecepcionistas + cantMozos + 1; i++){
		pid_t idHijo = wait(NULL);
		cout << "Termino proceso hijo: " << idHijo << endl;
	}
	*/

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
