/*
 * MozoProcess.h
 *
 *  Created on: Oct 15, 2016
 *      Author: gaston
 */

#ifndef PROCESSES_MOZOPROCESS_H_
#define PROCESSES_MOZOPROCESS_H_

namespace std {

class MozoProcess {
public:
	MozoProcess();
	void run();
	virtual ~MozoProcess();
};

} /* namespace std */

#endif /* PROCESSES_MOZOPROCESS_H_ */
