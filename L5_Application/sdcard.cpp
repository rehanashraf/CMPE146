/*
 * sdcard.cpp
 *
 *  Created on: Nov 28, 2017
 *      Author: rehanashraf
 */

#include "sdcard.h"

bool sdcard::init(void)
{

	return true;

}

bool sdcard::run(void *p)
{
	return true;
}

void getsonglist()
{

}

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
