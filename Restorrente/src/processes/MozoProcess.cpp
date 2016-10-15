/*
 * MozoProcess.cpp
 *
 *  Created on: Oct 15, 2016
 *      Author: gaston
 */

#include "MozoProcess.h"

#include <unistd.h>
#include <iostream>

namespace std {

MozoProcess::MozoProcess() {
	// TODO Auto-generated constructor stub
}

void MozoProcess::run(){
	cout << "Mozo con pid: " << getpid() << endl;
	//TODO Logica del proceso.
}

MozoProcess::~MozoProcess() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
