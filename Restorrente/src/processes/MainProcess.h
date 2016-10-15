/*
 * MainProcess.h
 *
 *  Created on: Oct 15, 2016
 *      Author: gaston
 */

#ifndef PROCESSES_MAINPROCESS_H_
#define PROCESSES_MAINPROCESS_H_

namespace std {

class MainProcess {

private:

	// TODO Deberia guardar referencias a IPCs, y tal vez tambien a los procesos hijos.
	int cantMozos;
	int cantRecepcionistas;
	int cantMesas;


public:
	MainProcess(const int cantRecepcionistas, const int cantMozos, const int cantMesas);
	void run();
	virtual ~MainProcess();
};

} /* namespace std */

#endif /* PROCESSES_MAINPROCESS_H_ */
