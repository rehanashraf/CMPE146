/*
 * sdcard.h
 *
 *  Created on: Nov 28, 2017
 *      Author: rehanashraf
 */

#ifndef L5_APPLICATION_SDCARD_H_
#define L5_APPLICATION_SDCARD_H_

#include "tasks.hpp"
#include "string.h"
#include "examples/examples.hpp"
#include "stdio.h"
#include "ff.h"

class sdcard : public scheduler_task
{
public:
	sdcard(char** list): scheduler_task("sdcard", 2000, PRIORITY_LOW) {  songlist = list;/* constructor code */ };

    bool init(void);
    bool run(void *p);
private:
    char** songlist= NULL;

};

#endif /* L5_APPLICATION_SDCARD_H_ */
