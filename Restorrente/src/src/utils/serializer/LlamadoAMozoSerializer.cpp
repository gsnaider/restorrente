/*
 * LlamadoAMozoSerializer.cpp
 *
 *  Created on: Oct 16, 2016
 *      Author: gaston
 */

#include "LlamadoAMozoSerializer.h"

#include <stdlib.h>

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

#include "../../model/Plato.h"

namespace std {

LlamadoAMozoSerializer::LlamadoAMozoSerializer() {
	// TODO Auto-generated constructor stub

}

string LlamadoAMozoSerializer::serializar(Pedido pedido){
	string pedidoStr = SEPARADOR + intToString(PEDIDO) + SEPARADOR;

	pedidoStr = pedidoStr + intToString(pedido.getMesa()) + SEPARADOR;
	pedidoStr = pedidoStr + intToString(pedido.getPlatos().size()) + SEPARADOR;

	for (unsigned int i = 0; i < pedido.getPlatos().size(); i++){
		pedidoStr = pedidoStr + pedido.getPlatos().at(i).getNombre() + SEPARADOR;
		pedidoStr = pedidoStr + doubleToString(pedido.getPlatos().at(i).getPrecio())  + SEPARADOR;
	}

	int length = pedidoStr.length();
	pedidoStr  = intToString(length) + pedidoStr;

	return pedidoStr;

}

string LlamadoAMozoSerializer::serializar(Comida comida) {

	string comidaStr = SEPARADOR + intToString(COMIDA) + SEPARADOR;

	comidaStr = comidaStr + intToString(comida.getMesa()) + SEPARADOR;
	comidaStr = comidaStr + intToString(comida.getPlatos().size()) + SEPARADOR;

	for (unsigned int i = 0; i < comida.getPlatos().size(); i++){
		comidaStr = comidaStr + comida.getPlatos().at(i).getNombre() + SEPARADOR;
		comidaStr = comidaStr + doubleToString(comida.getPlatos().at(i).getPrecio())  + SEPARADOR;
	}

	int length = comidaStr.length();
	comidaStr  = intToString(length) + comidaStr;

	return comidaStr;
}

string LlamadoAMozoSerializer::serializar(PedidoCuenta pedidoCuenta) {

	string pedidoCuentaStr = SEPARADOR + intToString(PEDIDO_CUENTA) + SEPARADOR;

	pedidoCuentaStr = pedidoCuentaStr + intToString(pedidoCuenta.getMesa()) + SEPARADOR;

	int length = pedidoCuentaStr.length();
	pedidoCuentaStr  = intToString(length) + pedidoCuentaStr;

	return pedidoCuentaStr;

}

Pedido LlamadoAMozoSerializer::deserializarPedido(string pedidoStr) {
	istringstream ss(pedidoStr);
	string aux;
	string mesaStr;
	string cantPlatosStr;
	string nombrePlato;
	string precioPlato;

	getline(ss, aux, SEPARADOR); //Primer separador
	getline(ss, aux, SEPARADOR); //Tipo de dato
	getline(ss, mesaStr, SEPARADOR);

	Pedido pedido(stoi(mesaStr));

	getline(ss, cantPlatosStr, SEPARADOR);
	int cantPlatos = stoi(cantPlatosStr);

	for (int i = 0; i < cantPlatos; i++){
		getline(ss, nombrePlato, SEPARADOR);
		getline(ss, precioPlato, SEPARADOR);
		Plato plato(nombrePlato, atof(precioPlato.c_str()));
		pedido.agregarPlato(plato);
	}


	return pedido;

}

Comida LlamadoAMozoSerializer::deserializarComida(string comidaStr) {
	istringstream ss(comidaStr);
	string aux;
	string mesaStr;
	string cantPlatosStr;
	string nombrePlato;
	string precioPlato;

	getline(ss, aux, SEPARADOR); //Primer separador
	getline(ss, aux, SEPARADOR); //Tipo de dato
	getline(ss, mesaStr, SEPARADOR);

	Comida comida(stoi(mesaStr));

	getline(ss, cantPlatosStr, SEPARADOR);
	int cantPlatos = stoi(cantPlatosStr);

	for (int i = 0; i < cantPlatos; i++){
		getline(ss, nombrePlato, SEPARADOR);
		getline(ss, precioPlato, SEPARADOR);
		Plato plato(nombrePlato, atof(precioPlato.c_str()));
		comida.agregarPlato(plato);
	}


	return comida;

}

PedidoCuenta LlamadoAMozoSerializer::deserializarPedidoCuenta(
		string pedidoCuentaStr) {
	istringstream ss(pedidoCuentaStr);
	string aux;
	string mesaStr;

	getline(ss, aux, SEPARADOR); //Primer separador
	getline(ss, aux, SEPARADOR); //Tipo de dato
	getline(ss, mesaStr, SEPARADOR);

	PedidoCuenta pedidoCuenta(stoi(mesaStr));

	return pedidoCuenta;

}

int LlamadoAMozoSerializer::getTipoDato(string data) {

	string aux;
	string tipoDatoStr;
	istringstream ss(data);

	getline(ss, aux, SEPARADOR);
	getline(ss, tipoDatoStr, SEPARADOR);

	return stoi(tipoDatoStr);
}

string std::LlamadoAMozoSerializer::doubleToString(double d) {
	stringstream stream;
	stream << fixed << setprecision(2) << d;
	return stream.str();
}

string std::LlamadoAMozoSerializer::intToString(int i) {
	stringstream stream;
	stream <<  i;
	return stream.str();
}



LlamadoAMozoSerializer::~LlamadoAMozoSerializer() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */

