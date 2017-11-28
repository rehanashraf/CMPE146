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
    FRESULT res;     /* FatFs return code */
    static FILINFO fno;
    FATFS fs;
    char path[256];


    res = f_mount(&fs, "1:", 1);
//    if (res == FR_OK) {
        strcpy(path, "1:");
        res = scan_files(path);

//    }
	printf("I am in sadcard init.\n");

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


