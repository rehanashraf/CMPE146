/*
 * uartlab.cpp
 *
 *  Created on: Sep 18, 2017
 *      Author: rehanashraf
 */

#include <uartlab.h>

bool uart_lab::init(void) {
	const uint32_t baud = 38400;
	uint16_t dll;
	/*Power up the uart2*/
	LPC_SC->PCONP |= (1 << 24);
	/*Clear bits for priphiral clock*/
	LPC_SC->PCLKSEL1 &= ~(3 << 16);
	/*setting the PCLCLOCK to CLK that is 01 value at bit 16 and 17 */
	LPC_SC->PCLKSEL1 |= (1 << 16);

	/*enablinng Uart 2 pins at P0.10 and P0.11 function needed is 01 so 0101 is 5 */
//	LPC_PINCON->PINSEL0 &= ~(0xF << 20);
//	LPC_PINCON->PINSEL0 |= (5 << 20);

	LPC_PINCON->PINSEL4 &= ~(3<< 16);
	LPC_PINCON->PINSEL4 |= (2<< 16);
	LPC_PINCON->PINSEL4 &= ~(3<< 18);
	LPC_PINCON->PINSEL4 |= (2<< 18);

	LPC_UART2->LCR |= (1 << 7); //setting DLAB to 1
	dll = (sys_get_cpu_clock() / (16 * baud)) + 0.5;
	//    LPC_UART2->DLM = 0;
	LPC_UART2->DLL = dll;
	LPC_UART2->DLM = dll >> 8;

	LPC_UART2->LCR &= ~(1 << 7);
	LPC_UART2->LCR = (3 << 0);

	LPC_UART2->FCR |= (1 << 0);

	//
	//
	//	LPC_SC->PCONP |= (1 << 25);
	//	/*Clear bits for priphiral clock*/
	//	LPC_SC->PCLKSEL1 &= ~(3 << 18);
	//	/*setting the PCLCLOCK to CLK that is 01 value at bit 16 and 17 */
	//	LPC_SC->PCLKSEL1 |= (1 << 18);
	//
	//	/*enablinng Uart 2 pins at P0.10 and P0.11 function needed is 01 so 0101 is 5 */
	//	LPC_PINCON->PINSEL0 &= ~(0xF << 0 );
	//	LPC_PINCON->PINSEL0 |= (0xA << 0 );
	//
	//	LPC_UART3->LCR |= (1 << 7 ); //setting DLAB to 1
	////    LPC_UART2->DLM = 0;
	//    LPC_UART3->DLL = sys_get_cpu_clock() / (16 * baud);
	//
	//    LPC_UART3->LCR &= ~(0xFF << 0);
	//    LPC_UART3->LCR |= (3 << 0);

	return true;
}

void uart_lab::put_char(char data) {
	LPC_UART2->THR = data;
//		 while(1)
//		 {
//			if (LPC_UART2->LSR & (1 << 6) )
//			{
//
//				break ;
//			}
//			printf("Stuck in put_char while. \n");
//		 }
	while (!(LPC_UART2->LSR & (1 << 6)));
	return;

}
char uart_lab::get_char() {
	char data;
//		 while(1)
//		 {
//			if (LPC_UART2->LSR & (1 << 0) )
//			{
//				break ;
//			}
//			printf("Stuck in get_char while. \n");
//		 }
	while (!(LPC_UART2->LSR & (1 << 0)));
	data = LPC_UART2->RBR;
	return data;
}

bool uart_lab::run(void *p) {

	put_char(DATA);
	printf("Data send is %c. \n", DATA);
	DATA = get_char();
	printf("Data received is %c. \n", DATA);
	DATA = DATA + 1;

	return true;
}

