/*
 * sdcard.cpp
 *
 *  Created on: Nov 28, 2017
 *      Author: rehanashraf
 */

#include "sdcard.h"

FRESULT scan_files (
    char* path        /* Start node to be scanned (***also used as work area***) */
)
{
    FRESULT res;
    DIR dir;
    UINT i;
    static FILINFO fno;


    res = f_opendir(&dir, path);                       /* Open the directory */
    if (res == FR_OK) {
        for (;;) {
            res = f_readdir(&dir, &fno);                   /* Read a directory item */
            if (res != FR_OK || fno.fname[0] == 0) break;  /* Break on error or end of dir */
            if (fno.fattrib & AM_DIR) {                    /* It is a directory */
                i = strlen(path);
                sprintf(&path[i], "/%s", fno.fname);
                res = scan_files(path);                    /* Enter the directory */
                if (res != FR_OK) break;
                path[i] = 0;
            } else {                                       /* It is a file. */
                printf("%s%s\n", path, fno.fname);
            }
        }
        f_closedir(&dir);
    }

    return res;
}


bool sdcard::init(void)
{


    FIL fil;        /* File object */
//    FRESULT res;     /* FatFs return code */
    static FILINFO fno;
//    FATFS fs;
    char path[256];
//    res = f_mount(&fs, "1:", 1);
//    if (res == FR_OK) {
        strcpy(path, "1:");
//        res = scan_files(path);

//    }
    FRESULT fr;
    fr = f_stat("1:3Peg.mp3", &fno);
    long int totalsize = fno.fsize;
//    int totalsize = 1024;
    printf("total size of the file is %i. \n", totalsize);
    printf("buffersize is %i.\n", buffersize);
	uint8_t data[buffersize] = { 0 };
	    fr = f_open(&fil, "1:3Peg.mp3", FA_READ);
//	    Storage::read("1:newtext.txt", data, sizeof(data)-1);
	    UINT size=0;
	    UINT offset = 0;
	    int endReadeSize = totalsize%buffersize;
	    int loopsize = totalsize/buffersize;
	    int readsize = buffersize;
	    for(int i = 0; i < loopsize +1 ; i++)
	    {
	    	f_lseek(&fil, offset);
//	    	printf("offset is %u, \n", offset);
	    	f_read(&fil,data, readsize, &size);
	    	char hhh;
//	    	printf("size is %u.\n", size);
	    		    		for (UINT j =0; j < size ; j++)
	    		    		{
//	    		    			if (j%4==0)
//	    		    			{
////	    		    				printf(" ");
//	    		    				char hh = ' ';
//	    		    				Storage::append("1:myfile.txt", &hh, sizeof(hh), 0);
//	    		    			}
//	    		    			if (j%64==0)
//	    		    			{
////	    		    				printf("\n");
//	    		    				char hh1 [2]= "\n";
//	    		    				Storage::append("1:myfile.txt", &hh1, sizeof(hh1), 0);
//	    		    			}
////	    		    			printf("%02X", (unsigned char)data[j]);
//	    		    			sprintf(&hhh, "%02X", data[j]);
	    		    			hhh = data[j];
	    		    			Storage::append("1:myfile1.txt", &hhh, 1, 0);
	    		    		}
	    		    offset += buffersize;

	    }
	    printf("Writing data is done. \n");
	    f_close(&fil);
//	    for(int j =0; j < 1; j ++)
//	    {
//	    		for (int i =0; i < 512 ; i++)
//	    		{
//	    			if (i%4==0)
//	    			{
//	    				printf(" ");
//	    			}
//	    			if (i%64==0)
//	    			{
//	    				printf("\n");
//	    			}
//	    			printf("%02X", (unsigned char)data[i]);
//	    		}
//	    }

//	//    FIL fil;        /* File object */
//	    char line[10]; /* Line buffer */
//	    FRESULT fr;     /* FatFs return code */
//	//    static FILINFO fno;
//	    fr = f_open(&fil, "1:3Peg.mp3", FA_READ);
//	    if (fr) return (int)fr;
//
//	    /* Read all lines and display it */
////	    int i =0;
//	    while (f_gets(line, sizeof line, &fil)) {
//    		for (int i =0; i < 10 ; i++)
//    		{
//    			if (i%4==0)
//    			{
//    				printf(" ");
//    			}
//    			if (i%64==0)
//    			{
//    				printf("\n");
//    			}
//    			printf("%02X", (unsigned char)line[i]);
//
//    		}
//	        printf(line);
//	        puts((char*) i);
//	        i++;
//	    }
//	    fr = f_stat("1:3Peg.mp3", &fno);
//	    f_gets(line, 1000, &fil);
//	    		for (int i =0; i < 900 ; i++)
//	    		{
//	    			if (i%4==0)
//	    			{
//	    				printf(" ");
//	    			}
//	    			if (i%64==0)
//	    			{
//	    				printf("\n");
//	    			}
//	    			printf("%02X", (unsigned char)line[i]);
//
//	    		}
	return true;

}

bool sdcard::run(void *p)
{
//	printf("I am in sdcard run.\n");
	return true;
}

void getsonglist()
{

}


