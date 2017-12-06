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
	sdcard(int bsize=0, uint8_t* slsize=NULL, char** slist=NULL, char** splist=NULL ) : scheduler_task("sdcard", 2000, PRIORITY_HIGH)
	{
		printf("In sdcard constructor\n");
		buffersize = bsize;
		songlistsize=slsize;
		songlist= slist;
		songpathlist=splist;
		result = FR_OK;
	};

    void opensongfile(uint8_t songnumber);
    void readsong();
    void closesongfile(uint8_t songnumber);
    FRESULT scan_files (char* path);

    bool init(void);
    bool run(void *p);
private:
    char** songlist;
    char** songpathlist;
    int buffersize;
    uint8_t *songlistsize;

    FIL fil ;        /* File object */
    FRESULT result;     /* FatFs return code */
    static FILINFO finfo ;

    UINT offset = 0;

    uint8_t endReadeSize = 0;//totalsize%buffersize;
    uint8_t loopsize = 0;//totalsize/buffersize;
//    uint8_t data[buffersize] = { 0 };
    uint8_t data[512] = { 0 };

    uint8_t * songsendbuffer = (uint8_t*)malloc(sizeof(uint8_t)*32);



};

#endif /* L5_APPLICATION_SDCARD_H_ */
