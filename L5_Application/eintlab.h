/*
 * eintlab.h
 *
 *  Created on: Sep 28, 2017
 *      Author: rehanashraf
 */

#ifndef L5_APPLICATION_EINTLAB_H_
#define L5_APPLICATION_EINTLAB_H_

#include "tasks.hpp"
#include "examples/examples.hpp"
#include "stdio.h"
#include "printf_lib.h"

class eint_lab : public scheduler_task {
public:
	eint_lab(): scheduler_task("eint",2000, PRIORITY_LOW) {};
	bool init(void);
	bool run(void *p);
//	extern void dosomething();
private:
	char * array = "hello";



};

#endif /* L5_APPLICATION_EINTLAB_H_ */
