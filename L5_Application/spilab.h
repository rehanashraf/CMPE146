/*
 * spilab.h
 *
 *  Created on: Sep 13, 2017
 *      Author: rehanashraf
 */

#ifndef L5_APPLICATION_SPILAB_H_
#define L5_APPLICATION_SPILAB_H_

#include <scheduler_task.hpp>
#include "tasks.hpp"
#include "examples/examples.hpp"
#include "stdio.h"
#include "../L4_IO/fat/disk/spi_flash.h"

class spi_lab: public scheduler_task {
public:
    spi_lab(): scheduler_task("spi", 2000, PRIORITY_LOW) { /* constructor code */ };

    bool init(void)
    {
    	//setting P0.6, 0.7, 0.8, 0.9 as GPIO(for CS) SCK, MISO and MOSI respectively
    	LPC_PINCON->PINSEL0 &= ~(0xFF << 12);
    	LPC_PINCON->PINSEL0 |= (0xA8 << 12);

     	LPC_PINCON->PINSEL4 &= ~(3);
     	LPC_GPIO2->FIODIR |= (1);

    	//setting P0.6 as output for CS for the Flash
    	LPC_GPIO0->FIODIR |= (1 << 6);


    	LPC_SC->PCONP |= (1 << 10); //Power on
    	LPC_SC->PCLKSEL0 &= ~(3 << 20); //setting PCLK_SSP1 to 00
//    	LPC_SC->PCLKSEL0 |= (1 << 20); // setting PCLK_SSP1 to 01 for clock to be CCLK which should be 24MHz

    	LPC_SSP1->CR0 = 7; // setting bit transfer to 8 bits 0111 as said in datasheet
    	LPC_SSP1->CR1 &= ~(3 << 1); // enabling ssp controller and setting ssp as master
    	LPC_SSP1->CR1 |= (1 << 1);
    	LPC_SSP1->CPSR = 128;

    	return true;
    }



    void select_flash()
    {
    	LPC_GPIO0->FIOCLR = (1 << 6);
    	LPC_GPIO2->FIOCLR = (1 << 0);
    	printf("selecetd flash\n");
    }

    void deselect_flash()
    {
    	LPC_GPIO0->FIOSET = (1 << 6);
    	LPC_GPIO2->FIOSET = (1 << 0);
    	printf("deselected flash\n");
    }

    uint8_t ssp_exchange(uint8_t out)
    {
        LPC_SSP1->DR = out;
        while(LPC_SSP1->SR & (1 << 4)); // Wait until SSP is busy
        return LPC_SSP1->DR;
    }

    void read_id()
    {
    	uint8_t out, in;
    	out = (0x9F);
    	select_flash();
    	in = ssp_exchange(out);
    	printf("Data send to Flash is  0x%(hex). \n", out);
//    	printf("Data got back is 0x%02x. \n", in);
  //  	vTaskDelay(1000);
    	out = (0x1F);
    	in = ssp_exchange(out);
//    	printf("Data send to Flash is 0x%02x. \n", out);
    	printf("Data got back from Flash is  0x%02x. \n", in);
   // 	vTaskDelay(1000);
    	out = (0xD7);
    	in = ssp_exchange(out);
    	in = ssp_exchange(out);
//    	printf("Data send to Flash is 0x%02x. \n", out);
    	printf("Data got back from Flash is  0x%02x. \n", in);
    	deselect_flash();
    	vTaskDelay(2500);

    }

    bool run(void *p)
    {
    	read_id();
    	uint8_t data [512];
    	if(flash_read_sectors(data, 0,1) == RES_OK)
    	{ int k=0;
    		for (int i = 0; i < 32 ; i++)
    		{
    			for (int j = 0; j < 16; j ++)
    				printf ("%02x ",data[i]);
    			printf("\n");
    		}
    	}

//    	(flash_read_sectors(data, 0, 1) == RES_OK ) ? printf("/n/n/n **********************FLASH READ**********************/n/n/n") : ;

    	return true;
    }

};

#endif /* L5_APPLICATION_SPILAB_H_ */
