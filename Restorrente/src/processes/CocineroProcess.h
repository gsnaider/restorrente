/*
 * CocineroProcess.h
 *
 *  Created on: Oct 15, 2016
 *      Author: gaston
 */

#ifndef PROCESSES_COCINEROPROCESS_H_
#define PROCESSES_COCINEROPROCESS_H_

namespace std {

class CocineroProcess {
public:
	CocineroProcess();
	void run();
	virtual ~CocineroProcess();
};

} /* namespace std */

#endif /* PROCESSES_COCINEROPROCESS_H_ */
