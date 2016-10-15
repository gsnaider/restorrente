/*
 * CocineroProcess.cpp
 *
 *  Created on: Oct 15, 2016
 *      Author: gaston
 */

#include "CocineroProcess.h"

#include <unistd.h>
#include <iostream>

namespace std {

CocineroProcess::CocineroProcess() {
	// TODO Auto-generated constructor stub

}

void CocineroProcess::run(){
	cout << "Cocinero con pid: " << getpid() << endl;
	//TODO Logica del proceso.
}

CocineroProcess::~CocineroProcess() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
