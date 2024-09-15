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
#define SW3_PIN 12
#define SW3_PORT PTC

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

void SW3_init(void){
	PCC->PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK;

	// Set PTC12 (SW3) as GPIO
	PORTC->PCR[SW3_PIN] = PORT_PCR_MUX(1);

	// Set PTC12 as input
	SW3_PORT->PDDR &= ~(1 << SW3_PIN);

	// Enable pull-up resistor for SW3 button (active-low button)
	PORTC->PCR[SW3_PIN] |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
}

int main(void){
//	watchDogDisable();
//	SOSC_init_8MHz();
//	SPLL_init_160MHz();
//	NormalRUNmode_80MHz();
//	PORT_init();
	SW3_init();

	//Initializes LPUART0 with a baud rate of 9600 and SOSC of 8MHz
	LPUART_init(LPUART0, 9600, 8);

	for(;;) {
		//if(PTC->PDIR & (1<<PTC12)){
		if(SW3_PORT->PDIR & (1<<SW3_PIN)){
			LPUART_send_string(LPUART0, "this is working");
			while(){}
//			PTD-> PCOR |= 1<<PTD0;
		}

	}
}





















