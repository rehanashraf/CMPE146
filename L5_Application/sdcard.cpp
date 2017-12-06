/*
 * sdcard.cpp
 *
 *  Created on: Nov 28, 2017
 *      Author: rehanashraf
 */

#include "sdcard.h"

FRESULT sdcard::scan_files (
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
            	uint8_t size = strlen(fno.fname);
//            	printf("%s%s\n", path, fno.fname);
            	if (fno.fname[size-1] == '3' && fno.fname[size-2] == 'P' && fno.fname[size-3] == 'M'  && fno.fname[0] != '_')
            	{
            		char * songname = (char*)malloc(strlen(fno.fname));
            		sprintf(songname, fno.fname);
            		songlist[*songlistsize] = songname;

            		char * songpath = (char*)malloc(strlen(path));
            		sprintf(songpath, path);
            		songpathlist[*songlistsize] = path;

            		*songlistsize +=1;
            	}
            }
        }
        f_closedir(&dir);
    }

    return res;
}


bool sdcard::init(void)
{
    char path[256];
    strcpy(path, "1:");
//    result = scan_files(path);



    FRESULT rehan;
    FIL newfile;
    FILINFO newfileinfo;
    rehan = f_open(&newfile, "1:newtext.txt", FA_READ);
    if (rehan == FR_OK)
    {
    	printf("file opened sucessfully.\n");
    }
//    rehan = f_stat("1:newtext.txt", &newfileinfo);
    printf("size is %u. \n", newfile.fsize);

    char newarray[512];
    int toreadsize = 512;
    UINT readsize =0;
    rehan = f_read(&newfile, newarray, toreadsize, &readsize);
    printf("Length of the newarray is %i \n", strlen(newarray));
    if (rehan == FR_OK)
    {	printf("Data read successful.\n");}
    printf("Total bytes read are %u. \n", readsize);
    printf("Data read is\n");
    for (uint8_t i = 0; i < strlen(newarray); i++)
    {
   		printf("%02X", newarray[i]);
 //   		printf("%c", newarray[i]);
   }
//    f_close(&newfile);
//    }
//    FRESULT fr;
//    fr = f_stat("1:3Peg.mp3", &finfo);
//    long int totalsize = finfo.fsize;
//    int totalsize = 1024;
//    printf("total size of the file is %i. \n", totalsize);
//    printf("buffersize is %i.\n", buffersize);
//	uint8_t data[buffersize] = { 0 };
//	fr = f_open(&fil, "1:3PEGNE~1.MP3", FA_READ);
//	    if (fr == FR_OK)
//	    {
//	    	printf("File opend sucessfully\n");
//	    	while(1);
//	    }
//	    Storage::read("1:newtext.txt", data, sizeof(data)-1);
//	    UINT size=0;
//	    UINT offset = 0;
//	    int endReadeSize = totalsize%buffersize;
//	    int loopsize = totalsize/buffersize;
//	    int readsize = buffersize;
//	    for(int i = 0; i < loopsize +1 ; i++)
//	    {
//	    	f_lseek(&fil, offset);
//	    	printf("offset is %u, \n", offset);
//	    	f_read(&fil,data, readsize, &size);
//	    	char hhh;
//	    	printf("size is %u.\n", size);
//	    		    		for (UINT j =0; j < size ; j++)
//	    		    		{
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
//	    		    			hhh = data[j];
//	    		    			Storage::append("1:myfile1.txt", &hhh, 1, 0);
//	    		    		}
//	    		    offset += buffersize;
//	    		    printf("Loop is %i. \n", i);
//	    }
//	    printf("Writing data is done. \n");
//	    f_close(&fil);
	return true;

}

bool sdcard::run(void *p)
{
//	printf("I am in sdcard run.\n");
	return true;
}

void sdcard::opensongfile(uint8_t songnumber)
{
	char songpathbuffer[strlen(songlist[songnumber])+strlen(songpathlist[songnumber])];
	sprintf(songpathbuffer,songlist[songnumber],songpathlist[songnumber]);
    if((result = f_open(&fil, songpathbuffer, FA_READ)) == FR_OK)
    		{
    		printf("%s opened successfully.\n", songlist[songnumber]);
    		}
//    result= f_stat(songpathbuffer, &finfo);
    long int totalsize = fil.fsize;
    endReadeSize = totalsize%buffersize;
    loopsize = totalsize/buffersize;

}
void sdcard::closesongfile(uint8_t songnumber)
{
    if((result = f_close(&fil)) == FR_OK)
    		{
    			printf("%s opened successfully.\n", songlist[songnumber]);
    		}
    endReadeSize = 0;
    loopsize =0;
    offset = 0;
}
void sdcard::readsong()
{
	UINT size = 0 ;
	uint8_t readsize = buffersize;
	if(offset >= loopsize * buffersize)
		readsize = endReadeSize;
	f_lseek(&fil, offset);
	f_read(&fil,data, endReadeSize, &size);
	offset += buffersize;
}



