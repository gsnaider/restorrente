/*
 * LlamadoAMozoSerializer.cpp
 *
 *  Created on: Oct 16, 2016
 *      Author: gaston
 */

#include "LlamadoAMozoSerializer.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

namespace std {

LlamadoAMozoSerializer::LlamadoAMozoSerializer() {
	// TODO Auto-generated constructor stub

}

string LlamadoAMozoSerializer::serializar(Pedido pedido){
	string pedidoStr = intToString(PEDIDO) + SEPARADOR;

	pedidoStr = pedidoStr + intToString(pedido.getMesa()) + SEPARADOR;
	pedidoStr = pedidoStr + intToString(pedido.getPlatos().size()) + SEPARADOR;

	for (unsigned int i = 0; i < pedido.getPlatos().size(); i++){
		pedidoStr = pedidoStr + pedido.getPlatos().at(i).getNombre() + SEPARADOR;
		pedidoStr = pedidoStr + doubleToString(pedido.getPlatos().at(i).getPrecio())  + SEPARADOR;
	}

	int length = pedidoStr.length();
	pedidoStr  = intToString(length) + SEPARADOR + pedidoStr;

	return pedidoStr;

}

string LlamadoAMozoSerializer::serializar(Comida comida) {

	string comidaStr = intToString(COMIDA) + SEPARADOR;

	comidaStr = comidaStr + intToString(comida.getMesa()) + SEPARADOR;
	comidaStr = comidaStr + intToString(comida.getPlatos().size()) + SEPARADOR;

	for (unsigned int i = 0; i < comida.getPlatos().size(); i++){
		comidaStr = comidaStr + comida.getPlatos().at(i).getNombre() + SEPARADOR;
		comidaStr = comidaStr + doubleToString(comida.getPlatos().at(i).getPrecio())  + SEPARADOR;
	}

	int length = comidaStr.length();
	comidaStr  = intToString(length) + SEPARADOR + comidaStr;

	return comidaStr;
}

string LlamadoAMozoSerializer::serializar(PedidoCuenta pedidoCuenta) {

	string pedidoCuentaStr = intToString(PEDIDO_CUENTA) + SEPARADOR;

	pedidoCuentaStr = pedidoCuentaStr + intToString(pedidoCuenta.getMesa()) + SEPARADOR;

	int length = pedidoCuentaStr.length();
	pedidoCuentaStr  = intToString(length) + SEPARADOR + pedidoCuentaStr;

	return pedidoCuentaStr;

}

Pedido LlamadoAMozoSerializer::deserializarPedido(string pedidoStr) {
}

Comida LlamadoAMozoSerializer::deserializarComida(string comidaStr) {
}

PedidoCuenta LlamadoAMozoSerializer::deserializarPedidoCuenta(
		string pedidoCuentaStr) {
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

