void delay(volatile int cycles)
{
    /* Delay function - do nothing for a number of cycles */
    while(cycles--);
}
//



#include "S32K144.h"
#include "clocks_and_modes.h"
#include "LPUART.h"
#define PTD0 0
#define PTC12 12


void watchDogDisable (void){
	WDOG->CNT = 0xD928C520;
	WDOG->TOVAL =  0x0000FFFF;
	WDOG->CS = 0x00002100;
}

void PORT_init(){

	//Port C will be used for LPUART
	PCC->PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK;

	//PORT D for button pressing
//	PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK;

	//Set UART for PORT C
	PORTC->PCR[6] |= PORT_PCR_MUX(2);
	PORTC->PCR[7] |= PORT_PCR_MUX(2);


	//Set LPUART to receive button press
	PTC->PDDR &= ~(1<<PTC12);
	PORTC->PCR[12] = 0x00000110;


	//Set button press of SW3
//	PTD->PDDR |= 1<<PTD0;
	PORTD->PCR[0] = 0x00000100;
}

int main(void){
	watchDogDisable();
	SOSC_init_8MHz();
	SPLL_init_160MHz();
	NormalRUNmode_80MHz();
	PORT_init();

	LPUART1_init();

	for(;;) {
		if(PTC->PDIR & (1<<PTC12)){
//			LPUART1_transmit_char('o');
//			LPUART1_transmit_char('n');
//			LPUART1_transmit_char('\n');
			LPUART_send_string("this is working");

			PTD-> PCOR |= 1<<PTD0;
			delay(10000000);
		}

	}
}





















