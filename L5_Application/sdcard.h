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
#include "string.h"
#include "storage.hpp"

class sdcard : public scheduler_task
{
public:
//	sdcard(char** list): scheduler_task("sdcard", 2000, PRIORITY_HIGH) {  songlist = list;/* constructor code */
//	printf("In sdcard constructor\n");};
	sdcard(int size=0) : scheduler_task("sdcard", 2000, PRIORITY_HIGH) {printf("In sdcard constructor\n"); buffersize = size;};


    bool init(void);
    bool run(void *p);
private:
    char** songlist= NULL;
    int buffersize;
//    FRESULT scan_files (char* path);


};

#endif /* L5_APPLICATION_SDCARD_H_ */
