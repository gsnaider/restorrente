/*
 * Comida.cpp
 *
 *  Created on: Oct 16, 2016
 *      Author: gaston
 */

#include "Comida.h"

Comida::Comida(vector<Plato>* platos, int mesa) {
	this->platos = platos;
	this->mesa = mesa;
}

int Comida::getMesa() {
	return mesa;
}

void Comida::setMesa(int mesa) {
	this->mesa = mesa;
}

vector<Plato>* Comida::getPlatos(){
	return platos;
}

void Comida::setPlatos(vector<Plato>* platos){
	this->platos = platos;
}

Comida::~Comida() {
	// TODO Auto-generated destructor stub
}

