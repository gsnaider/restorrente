/*
 * RandomUtil.cpp
 *
 *  Created on: Oct 16, 2016
 *      Author: gaston
 */

#include "RandomUtil.h"

#include <cstdlib>

namespace std {

RandomUtil::RandomUtil() {
	// TODO Auto-generated constructor stub

}

double RandomUtil::randomCeroUno(){
	return ((double) rand() / (RAND_MAX));
}

int RandomUtil::randomInt(int max){
	return (rand() % max);
}

RandomUtil::~RandomUtil() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
