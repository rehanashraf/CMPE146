/*
 *     SocialLedge.com - Copyright (C) 2013
 *
 *     This file is part of free software framework for embedded processors.
 *     You can use it and/or distribute it as long as this copyright header
 *     remains unmodified.  The code is free for personal use and requires
 *     permission to use in a commercial product.
 *
 *      THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 *      OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 *      MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 *      I SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 *      CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *     You can reach the author of this software at :
 *          p r e e t . w i k i @ g m a i l . c o m
 */

/**
 * @file
 * @brief This is the application entry point.
 * 			FreeRTOS and stdio printf is pre-configured to use uart0_min.h before main() enters.
 * 			@see L0_LowLevel/lpc_sys.h if you wish to override printf/scanf functions.
 *
 */
#include <gpiolab.h>
#include <spilab.h>
#include "tasks.hpp"
#include "examples/examples.hpp"
#include "uartlab.h"
#include "eintlab.h"
#include "i2clab.h"
#include "uart0_min.h"
#include "stdio.h"
#include "sdcard.h"
//extern "C"{
#include "ff.h"
#include "io.hpp"
#include "storage.hpp"
#include "string.h"

//}//#include "ffconf.h"



/**
 * The main() creates tasks or "threads".  See the documentation of scheduler_task class at scheduler_task.hpp
 * for details.  There is a very simple example towards the beginning of this class's declaration.
 *
 * @warning SPI #1 bus usage notes (interfaced to SD & Flash):
 *      - You can read/write files from multiple tasks because it automatically goes through SPI semaphore.
 *      - If you are going to use the SPI Bus in a FreeRTOS task, you need to use the API at L4_IO/fat/spi_sem.h
 *
 * @warning SPI #0 usage notes (Nordic wireless)
 *      - This bus is more tricky to use because if FreeRTOS is not running, the RIT interrupt may use the bus.
 *      - If FreeRTOS is running, then wireless task may use it.
 *        In either case, you should avoid using this bus or interfacing to external components because
 *        there is no semaphore configured for this bus and it should be used exclusively by nordic wireless.
 */

void Task1(void *p)
{
	while(1)
	{
		uart0_puts("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
		vTaskDelay(50);
	}
}

void Task2(void *p)
{
	while(1)
	{
		uart0_puts("bbbbbbbbbbbbbbbb");
		vTaskDelay(50);
	}

}
//FRESULT scan_files (
//    char* path        /* Start node to be scanned (***also used as work area***) */
//)
//{
//    FRESULT res;
//    DIR dir;
//    UINT i;
//    static FILINFO fno;
//
//
//    res = f_opendir(&dir, path);                       /* Open the directory */
//    if (res == FR_OK) {
//        for (;;) {
//            res = f_readdir(&dir, &fno);                   /* Read a directory item */
//            if (res != FR_OK || fno.fname[0] == 0) break;  /* Break on error or end of dir */
//            if (fno.fattrib & AM_DIR) {                    /* It is a directory */
//                i = strlen(path);
//                sprintf(&path[i], "/%s", fno.fname);
//                res = scan_files(path);                    /* Enter the directory */
//                if (res != FR_OK) break;
//                path[i] = 0;
//            } else {                                       /* It is a file. */
//                printf("%s%s\n", path, fno.fname);
//            }
//        }
//        f_closedir(&dir);
//    }
//
//    return res;
//}

int main(void)
{
    /**
     * A few basic tasks for this bare-bone system :
     *      1.  Terminal task provides gateway to interact with the board through UART terminal.
     *      2.  Remote task allows you to use remote control to interact with the board.
     *      3.  Wireless task responsible to receive, retry, and handle mesh network.
     *
     * Disable remote task if you are not using it.  Also, it needs SYS_CFG_ENABLE_TLM
     * such that it can save remote control codes to non-volatile memory.  IR remote
     * control codes can be learned by typing the "learn" terminal command.
     */

//    scheduler_add_task(new gpio_lab_demo);
//    scheduler_add_task(new spi_lab);
//    scheduler_add_task(new uart_lab);
// 	  scheduler_add_task(new i2c_lab);
//	  scheduler_add_task(new eint_lab);
//	char** list = (char**)malloc(20);
//	scheduler_add_task(new sdcard(list));
	scheduler_add_task(new sdcard);

//	FATFS FatFs;
//    FIL fil;        /* File object */
//    char line[10]; /* Line buffer */
//    FRESULT fr;     /* FatFs return code */
//    static FILINFO fno;

    /* Register work area to the default drive */
//    f_mount(&FatFs, "1:", 0);

    /* Open a text file */
//    fr = f_open(&fil, "1:3Peg.mp3", FA_READ);
//    if (fr) return (int)fr;

    /* Read all lines and display it */
//    int i =0;
//    while (f_gets(line, sizeof line, &fil)) {
//        printf(line);
////        puts((char*) i);
////        i++;
////    }
//       fr = f_stat("1:3Peg.mp3", &fno);
//    switch (fr) {
//
//    case FR_OK:
//        printf("Size: %lu\n", fno.fsize);
//        printf("Timestamp: %u/%02u/%02u, %02u:%02u\n",
//               (fno.fdate >> 9) + 1980, fno.fdate >> 5 & 15, fno.fdate & 31,
//               fno.ftime >> 11, fno.ftime >> 5 & 63);
//        printf("Attributes: %c%c%c%c%c\n",
//               (fno.fattrib & AM_DIR) ? 'D' : '-',
//               (fno.fattrib & AM_RDO) ? 'R' : '-',
//               (fno.fattrib & AM_HID) ? 'H' : '-',
//               (fno.fattrib & AM_SYS) ? 'S' : '-',
//               (fno.fattrib & AM_ARC) ? 'A' : '-');
//        break;
//
//    case FR_NO_FILE:
//        printf("It is not exist.\n");
//        break;
//
//    default:
//        printf("An error occured. (%d)\n", fr);
//    }

    /* Close the file */
//    f_close(&fil);

//    FATFS fs;
//    FRESULT res;
//    char buff[256];
//
//
//    res = f_mount(&fs, "1:", 1);
//    if (res == FR_OK) {
//        strcpy(buff, "1:");
//        res = scan_files(buff);
//    }

    printf("Hello Rehan\n");

//    uint8_t data[1000] = { 0 };
//    Storage::read("1:3Peg.mp3", data, sizeof(data)-1);
//
//
//	for (int i =0; i < 1000 ; i++)
//	{
//		if (i%4==0)
//		{
//			printf(" ");
//		}
//		if (i%64==0)
//		{
//			printf("\n");
//		}
//		printf("%02X", (unsigned char)data[i]);
//
//	}

//	TaskHandle_t xTask1;
//	TaskHandle_t xTask2;
//	xTaskCreate(Task1, "task1", STACK_BYTES(2048), 0, 1, 0);
//	xTaskCreate(Task2, "task2", STACK_BYTES(2048), 0, 1, 0);





    scheduler_add_task(new terminalTask(PRIORITY_HIGH));

    /* Consumes very little CPU, but need highest priority to handle mesh network ACKs */
    scheduler_add_task(new wirelessTask(PRIORITY_CRITICAL));

//	vTaskStartScheduler();

    /* Change "#if 0" to "#if 1" to run period tasks; @see period_callbacks.cpp */
    #if 0
    scheduler_add_task(new periodicSchedulerTask());
    #endif

    /* The task for the IR receiver */
     scheduler_add_task(new remoteTask  (PRIORITY_LOW));

    /* Your tasks should probably used PRIORITY_MEDIUM or PRIORITY_LOW because you want the terminal
     * task to always be responsive so you can poke around in case something goes wrong.
     */

    /**
     * This is a the board demonstration task that can be used to test the board.
     * This also shows you how to send a wireless packets to other boards.
     */
    #if 0
        scheduler_add_task(new example_io_demo());
    #endif

    /**
     * Change "#if 0" to "#if 1" to enable examples.
     * Try these examples one at a time.
     */
    #if 0
        scheduler_add_task(new example_task());
        scheduler_add_task(new example_alarm());
        scheduler_add_task(new example_logger_qset());
        scheduler_add_task(new example_nv_vars());
    #endif

    /**
	 * Try the rx / tx tasks together to see how they queue data to each other.
	 */
    #if 0
        scheduler_add_task(new queue_tx());
        scheduler_add_task(new queue_rx());
    #endif

    /**
     * Another example of shared handles and producer/consumer using a queue.
     * In this example, producer will produce as fast as the consumer can consume.
     */
    #if 0
        scheduler_add_task(new producer());
        scheduler_add_task(new consumer());
    #endif

    /**
     * If you have RN-XV on your board, you can connect to Wifi using this task.
     * This does two things for us:
     *   1.  The task allows us to perform HTTP web requests (@see wifiTask)
     *   2.  Terminal task can accept commands from TCP/IP through Wifly module.
     *
     * To add terminal command channel, add this at terminal.cpp :: taskEntry() function:
     * @code
     *     // Assuming Wifly is on Uart3
     *     addCommandChannel(Uart3::getInstance(), false);
     * @endcode
     */
    #if 0
        Uart3 &u3 = Uart3::getInstance();
        u3.init(WIFI_BAUD_RATE, WIFI_RXQ_SIZE, WIFI_TXQ_SIZE);
        scheduler_add_task(new wifiTask(Uart3::getInstance(), PRIORITY_LOW));
    #endif

    scheduler_start(); ///< This shouldn't return
    return -1;
}

