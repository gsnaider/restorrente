/*
 * Comida.h
 *
 *  Created on: Oct 16, 2016
 *      Author: gaston
 */

#ifndef MODEL_COMIDA_H_
#define MODEL_COMIDA_H_

#include <vector>

#include "LlamadoAMozo.h"
#include "Plato.h"

using namespace std;

class Comida : public LlamadoAMozo{

private:
	int mesa;
	vector<Plato>* platos;

public:
	Comida(vector<Plato>* platos, int mesa);

	int getMesa();
	void setMesa(int mesa);
	vector<Plato>* getPlatos();
	void setPlatos(vector<Plato>* platos);

	virtual ~Comida();

};

#endif /* MODEL_COMIDA_H_ */
