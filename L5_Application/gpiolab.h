/*
 * gpiolabdemo.h
 *
 *  Created on: Sep 11, 2017
 *      Author: rehanashraf
 */

#ifndef L5_APPLICATION_GPIOLAB_H_
#define L5_APPLICATION_GPIOLAB_H_

#include "tasks.hpp"
#include "examples/examples.hpp"
#include "stdio.h"

class gpio_lab_demo : public scheduler_task
{
public:
    gpio_lab_demo(): scheduler_task("gpio", 2000, PRIORITY_LOW) { /* constructor code */ };

    bool init(void) {
 //        LPC_PINCON->PINSEL2 &= ~(3 << 2);
 //        LPC_GPIO1->FIODIR |= (1 << 1);

 //		GPIO Switch SW2 output P1.14
     	LPC_PINCON->PINSEL2 &= ~(3 << 28);
     	LPC_GPIO1->FIODIR &= ~(1 << 14); //pin 14
 //		GPIO LED LED7 input P1.4
     	LPC_PINCON->PINSEL2 &= ~(3 << 8);
     	LPC_GPIO1->FIODIR  |= (1 << 4);// pin 4 port 1

 //		External GPIO Switch input P2.0
     	LPC_PINCON->PINSEL4 &= ~(3);
     	LPC_GPIO2->FIODIR &= ~(1);

 //		External GPIO For LED output P2.1
     	LPC_PINCON->PINSEL4 &= ~(3 << 2);
     	LPC_GPIO2->FIODIR |= (1 << 1);
         return true;
     }

     bool run (void *p) {
 //        LPC_GPIO1->FIOPIN |= (1 << 1);
 //        //LPC_GPIO1->FIOSET = (1 << 1);
 //        vTaskDelay(1000);
 //        LPC_GPIO1->FIOPIN &= ~(1 << 1);
 //        //LPC_GPIO1->FIOCLR = (1 << 1);
 //        vTaskDelay(1000);

     	//		For External Switch and Led Circuit
//     	(LPC_GPIO2->FIOPIN & (1 << 0)) ? LPC_GPIO2->FIOSET = (1 << 1), printf("External Switch is pressed.\n") : LPC_GPIO2->FIOCLR = (1 << 1);


     	//		For Internal Switch and Led Circuit
     	(LPC_GPIO1->FIOPIN & (1 << 14) ) ? LPC_GPIO1->FIOCLR = (1 << 4), printf("Internal Switch is pressed.\n") : LPC_GPIO1->FIOSET = (1 << 4);

         return true;
     }
};

#endif /* L5_APPLICATION_GPIOLAB_H_ */
