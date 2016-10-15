/*
 * GrupoComensalesProcess.cpp
 *
 *  Created on: Oct 15, 2016
 *      Author: gaston
 */

#include "GrupoComensalesProcess.h"

#include <unistd.h>
#include <iostream>

namespace std {

GrupoComensalesProcess::GrupoComensalesProcess() {
	// TODO Auto-generated constructor stub

}

void GrupoComensalesProcess::run(){
	cout << "Grupo de comensales con pid: " << getpid() << endl;
	//TODO Logica del proceso.
}

GrupoComensalesProcess::~GrupoComensalesProcess() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
