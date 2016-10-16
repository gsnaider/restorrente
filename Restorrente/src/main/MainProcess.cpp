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
#include <sys/types.h>
#include <sys/wait.h>

#include "../processes/CocineroProcess.h"
#include "../processes/GrupoComensalesProcess.h"
#include "../processes/MozoProcess.h"
#include "../processes/RecepcionistaProcess.h"

namespace std {

MainProcess::MainProcess(int cantRecepcionistas, int cantMozos, int cantMesas, int cantComensales) {
	this->cantRecepcionistas = cantRecepcionistas;
	this->cantMozos = cantMozos;
	this->cantMesas = cantMesas;
	this->cantComensales = cantComensales;
	inicializarIPCs();
}

void MainProcess::iniciarProcesoCocinero(){
	cout << "DEBUG: Iniciando cocinero"<< endl;
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
		cout << "DEBUG: Iniciando mozo " << i << endl;

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
		cout << "DEBUG: Iniciando recepcionista " << i << endl;
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

void MainProcess::inicializarSemaforos(){
	semComensalesEnPuerta = new Semaforo(SEM_COMENSALES_EN_PUERTA_INIT_FILE, 0, 0);
	semRecepcionistasLibres = new Semaforo(SEM_RECEPCIONISTAS_LIBRES_INIT_FILE, 0, 0); //cada recepcionista suma uno al semaforo cuando se inicia.
	semMesasLibres = new Semaforo(SEM_MESAS_LIBRES_INIT_FILE, cantMesas, 0);
	semPersonasLivingB = new Semaforo(SEM_PERSONAS_LIVING_INIT_FILE, 1, 0);
	semCajaB = new Semaforo(SEM_CAJA_INIT_FILE, 1, 0);

	for(int i = 0; i < cantMesas; i++){
		semsLlegoComida.push_back(new Semaforo(SEM_LLEGO_COMIDA_INIT_FILE, 0, i));
		semsMesaPago.push_back(new Semaforo(SEM_MESA_PAGO_INIT_FILE, 0, i));
		semsFacturas.push_back(new Semaforo(SEM_FACTURA_INIT_FILE, 1, i));
	}
}

void MainProcess::inicializarMemoriasCompartidas(){
	semPersonasLivingB->p();
	shmPersonasLiving = new MemoriaCompartida<int>();
//	shmPersonasLiving->crear(SHM_PERSONAS_LIVING, 0);
//	shmPersonasLiving->escribir(0);

	semCajaB->p();
	shmCaja = new MemoriaCompartida<double>();
//	shmCaja->crear(SHM_CAJA, 0);
//	shmCaja->escribir(0);

	for(int i = 0; i < cantMesas; i++){
		semsFacturas[i]->p();
		shmFacturas.push_back(new MemoriaCompartida<double>());
//		shmFacturas[i]->crear(SHM_FACTURAS, i);
//		shmFacturas[i]->escribir(0);
	}
}

void MainProcess::crearMemoriasCompartidas(){
	shmPersonasLiving->crear(SHM_PERSONAS_LIVING, 0);
	shmPersonasLiving->escribir(0);
	semPersonasLivingB->v();

	shmCaja->crear(SHM_CAJA, 0);
	shmCaja->escribir(0);
	semCajaB->v();

	for(int i = 0; i < cantMesas; i++){
		shmFacturas[i]->crear(SHM_FACTURAS, i);
		shmFacturas[i]->escribir(0);
		semsFacturas[i]->v();
	}
}

void MainProcess::inicializarPipesFifos(){

}


void MainProcess::inicializarIPCs(){
	inicializarSemaforos();
	inicializarMemoriasCompartidas();
	inicializarPipesFifos();

}

void MainProcess::finalizarProcesosRestaurant(){

	for (unsigned int i = 0; i < idsRecepcionistas.size(); i++){
		kill(idsRecepcionistas[i], 9);
	}

	for (unsigned int i = 0; i < idsMozos.size(); i++){
		kill(idsMozos[i], 9);
	}

	kill(idCocinero, 9);


}

void MainProcess::inicializarComensalesComensales(){
	for (int i = 0; i < cantComensales; i++){

		cout << "DEBUG: Iniciando comensal " << i << endl;
		pid_t idComensal = fork();

		if (idComensal == 0){
			GrupoComensalesProcess grupoComensalesProcess(4,
					semRecepcionistasLibres, semComensalesEnPuerta,
					semPersonasLivingB, shmPersonasLiving, semMesasLibres);
			grupoComensalesProcess.run();
			exit(0);
		} else {
			idsComensales.push_back(idComensal);
		}

	}

}

void MainProcess::run(){

	inicializarProcesosRestaurant();
	inicializarComensalesComensales();

	crearMemoriasCompartidas();

	// Estoy asumiendo que los unicos que pueden terminar "por su cuenta" son los comensales cuando se van.
	for (int i = 0; i < cantComensales; i++){
		pid_t idHijo = wait(NULL);
		cout << "DEBUG: Termino proceso hijo: " << idHijo << endl;
	}

	finalizarProcesosRestaurant();

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

	shmPersonasLiving->liberar();
	delete shmPersonasLiving;

	shmCaja->liberar();
	delete shmCaja;

	for(int i = 0; i < cantMesas; i++){

		shmFacturas[i]->liberar();
		delete shmFacturas[i];
	}

}

} /* namespace std */
