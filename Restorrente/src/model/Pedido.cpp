/*
 * Pedido.cpp
 *
 *  Created on: Oct 15, 2016
 *      Author: gaston
 */

#include "Pedido.h"

Pedido::Pedido(vector<Plato>* platos, int mesa) {
	this->platos = platos;
	this->mesa = mesa;
}

int Pedido::getMesa() {
	return mesa;
}

void Pedido::setMesa(int mesa) {
	this->mesa = mesa;
}

vector<Plato>* Pedido::getPlatos(){
	return platos;
}

void Pedido::setPlatos(vector<Plato>* platos){
	this->platos = platos;
}

Pedido::~Pedido() {
	// TODO Auto-generated destructor stub
}

