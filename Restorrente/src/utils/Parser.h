/*
 * Parser.h
 *
 *  Created on: Oct 16, 2016
 *      Author: juampa_94
 */

#ifndef PARSER_H_
#define PARSER_H_



#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

class Parser {

private:
	int cantMozos;
	int cantRecepcionistas;
	int cantMesas;
	int cantComensales;

public:
	Parser();
	virtual ~Parser();
	bool parse(std::string Pathfile);
	int getCantMozos();
	int getCantRecepcionistas();
	int getCantMesas();
	int getCantComensales();
};

#endif /* PARSER_H_ */
