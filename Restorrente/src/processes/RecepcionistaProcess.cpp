/*
 * RecepcionistaProcess.cpp
 *
 *  Created on: Oct 15, 2016
 *      Author: gaston
 */

#include "RecepcionistaProcess.h"

#include <unistd.h>
#include <iostream>

namespace std {

RecepcionistaProcess::RecepcionistaProcess() {
	// TODO Auto-generated constructor stub

}

void RecepcionistaProcess::run(){
	cout << "Recepcionista con pid: " << getpid() << endl;
	//TODO Logica del proceso.
}

RecepcionistaProcess::~RecepcionistaProcess() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
