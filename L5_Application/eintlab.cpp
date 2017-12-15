///*
// * eintlab.cpp
// *
// *  Created on: Sep 28, 2017
// *      Author: rehanashraf
// */
//
//#include <eintlab.h>
//
//
//bool eint_lab::init()
//{
//	LPC_PINCON->PINSEL0 &= ~(0xF << 0);
//	LPC_GPIO0->FIODIR |= (3 << 0);
//
//	LPC_PINCON->PINSEL4 &= ~(3 << 0);
//	LPC_GPIO2->FIODIR &= ~(1 << 0);
//
//
//	LPC_GPIOINT->IO0IntEnF &= ~(3 << 0);
//	LPC_GPIOINT->IO0IntEnR |= (3 << 0);
//	LPC_GPIOINT->IO2IntEnR |= (1 << 0);
//
//
////		GPIO Switch SW2 output P1.14
//	LPC_PINCON->PINSEL2 &= ~(3 << 28);
//	LPC_GPIO1->FIODIR &= ~(1 << 14); //pin 14
//
//	LPC_PINCON->PINSEL2 &= ~(3 << 20);
//	LPC_GPIO1->FIODIR &= ~(1 << 10);
//
//
////	LPC_SC->EXTMODE     = (1 << 3);
////	LPC_SC->EXTPOLAR    = (1 << 3);
//	NVIC_EnableIRQ(EINT3_IRQn);
//
//
//
//	return true;
//
//}
//
//bool eint_lab::run(void *p)
//{
////	u0_dbg_printf(array);
//	(LPC_GPIO1->FIOPIN & (1 << 10)) ? u0_dbg_printf("Button pressed. \n "), LPC_GPIO0->FIOSET = (1 << 0) : false  ;
// 	(LPC_GPIO1->FIOPIN & (1 << 14) ) ?  u0_dbg_printf("Internal Switch is pressed.\n"), LPC_GPIO0->FIOSET = (1 << 1) : false;
//// 	(LPC_GPIO2->FIOPIN & (1 << 0)) ? u0_dbg_printf("External Switch Pressed. \n") : false ;
//	return true;
//}
//
// void somefunction()
//{
//	u0_dbg_printf("Switch 1 pressed. \n");
//}
//
//void somefunction1()
//{
//	u0_dbg_printf("Switch 2 pressed. \n");
//}
//
// void somefunction2()
//{
//	u0_dbg_printf("External Switch is pressed. \n");
//}
//
//extern "C"
//{
//#include "eintlab.h"
//	void EINT3_IRQHandler(void)
//	{
//		char * array = "External Interrupt hits here.\n";
//		u0_dbg_printf(array);
////		(LPC_GPIOINT->IO0IntStatR  & (1 << 0)) ? somefunction() : false;
////		(LPC_GPIOINT->IO0IntStatR  & (1 << 1)) ? somefunction1() : false;
////		(LPC_GPIOINT->IO2IntStatR  & (1 << 0)) ? somefunction2() : false;
//
//		if (LPC_GPIOINT->IO0IntStatR  & (1 << 0))
//			somefunction();
//		else if (LPC_GPIOINT->IO0IntStatR  & (1 << 1))
//			somefunction1();
//		else if (LPC_GPIOINT->IO2IntStatR  & (1 << 0))
//			somefunction();
//
//		LPC_GPIO0->FIOCLR = (3 << 0);
//        LPC_GPIOINT->IO0IntClr = 0xFFFFFFFF;
//        LPC_GPIOINT->IO2IntClr = 0xFFFFFFFF;
//
//	}
//}
//
//
//
//
//
