/*

 * Parser.cpp
 *
 *  Created on: Oct 16, 2016
 *      Author: juampa_94


#include "Parser.h"


#include <iostream>
#include <string>

using namespace std;

Parser::Parser() {
}

Parser::~Parser() {
}

bool Parser::parse(string pathFile){
    ifstream data(pathFile);

    string line;
    getline(data,line);
    this->cantMozos = stoi(line);
    getline(data,line);
    this->cantRecepcionistas = stoi(line);
    getline(data,line);
    this->cantMesas = stoi(line);
    getline(data,line);
    this->cantComensales = stoi(line);
    return true;
 }

int Parser::getCantMozos(){
	return this->cantMozos;
}

int Parser::getCantRecepcionistas(){
	return this->cantRecepcionistas;
}
int Parser::getCantMesas(){
	return this->cantMesas;
}
int Parser::getCantComensales(){
	return this->cantComensales;
}
*/
