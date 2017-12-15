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
//#include <gpiolab.h>
//#include <spilab.h>
#include "tasks.hpp"
#include "examples/examples.hpp"
//#include "uartlab.h"
//#include "eintlab.h"
//#include "i2clab.h"
#include "uart0_min.h"
#include "stdio.h"
#include "sdcard.h"
#include "ff.h"
#include "io.hpp"
#include "storage.hpp"
#include "string.h"
#include "i2c2.hpp"
#include "mp3Decoder.h"
#include "eint.h"

//
char** songlist = (char**)malloc(30*sizeof(char*));			//array where all the song names will be stored
char** songpathlist = (char**)malloc(30*sizeof(char*));
uint8_t songlistsize = 0;			//size of the songlist


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

int main(void)
{
	eint3_enable_port2(4, eint_falling_edge, MP3_decr_vol_handler);
	eint3_enable_port2(5, eint_falling_edge, MP3_incr_vol_handler);
	eint3_enable_port2(6, eint_falling_edge, MP3_prev_song_handler);
	eint3_enable_port2(3, eint_falling_edge, MP3_next_song_handler);
	eint3_enable_port2(2, eint_falling_edge, MP3_play_handler);

	scheduler_add_task(new sdcard);
	scheduler_add_task(new mp3Decoder);
    scheduler_add_task(new terminalTask(PRIORITY_HIGH));

    scheduler_start(); ///< This shouldn't return

    return -1;
}

