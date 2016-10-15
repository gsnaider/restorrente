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

MainProcess::MainProcess(int cantRecepcionistas, int cantMozos, int cantMesas) {
	this->cantRecepcionistas = cantRecepcionistas;
	this->cantMozos = cantMozos;
	this->cantMesas = cantMesas;

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
			RecepcionistaProcess recepcionista;
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

void MainProcess::run(){

	//TODO inicializar IPCs

	inicializarProcesos();


	for (int i = 0; i < cantRecepcionistas + cantMozos + 1; i++){
		pid_t idHijo = wait(NULL);
		cout << "Termino proceso hijo: " << idHijo << endl;
	}

}

MainProcess::~MainProcess() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
