/*
 * uartlab.h
 *
 *  Created on: Sep 18, 2017
 *      Author: rehanashraf
 */

#ifndef L5_APPLICATION_UARTLAB_H_
#define L5_APPLICATION_UARTLAB_H_
#include "tasks.hpp"
#include "examples/examples.hpp"
#include "stdio.h"

class uart_lab : public scheduler_task {
public:
	uart_lab(): scheduler_task("uart",2000, PRIORITY_LOW) {};
		bool init(void);
		bool run(void *p);
		void put_char(char data);
		char get_char(void);

private:
	char DATA ='A';
};

#endif /* L5_APPLICATION_UARTLAB_H_ */
