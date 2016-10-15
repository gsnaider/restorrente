/*
 * GrupoComensalesProcess.h
 *
 *  Created on: Oct 15, 2016
 *      Author: gaston
 */

#ifndef PROCESSES_GRUPOCOMENSALESPROCESS_H_
#define PROCESSES_GRUPOCOMENSALESPROCESS_H_

namespace std {

class GrupoComensalesProcess {
private:
	int cantPersonas;

public:
	GrupoComensalesProcess();
	void run();
	virtual ~GrupoComensalesProcess();
};

} /* namespace std */

#endif /* PROCESSES_GRUPOCOMENSALESPROCESS_H_ */
