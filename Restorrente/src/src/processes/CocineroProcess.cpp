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

	//TODO Ver si hay mejor forma que while(true).
	while(true){
		//TODO Agregar logica de proceso
		sleep(1);
	}
}

CocineroProcess::~CocineroProcess() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
