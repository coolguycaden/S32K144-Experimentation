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

void watchDogDisable (void){
	WDOG->CNT = 0xD928C520;
	WDOG->TOVAL =  0x0000FFFF;
	WDOG->CS = 0x00002100;
}

//Initializes LPUART to use the port entered
void LPUART_PORT_init(uint32_t PORT_INDEX){

	//Port C will be used for LPUART
	PCC->PCCn[PORT_INDEX] = PCC_PCCn_CGC_MASK;

	//Set UART for PORT C
	PORTC->PCR[6] |= PORT_PCR_MUX(2);
	PORTC->PCR[7] |= PORT_PCR_MUX(2);


	//Set LPUART to receive button press
	PTC->PDDR &= ~(1<<PTC12);
	PORTC->PCR[12] = 0x00000110;
}

void SW3_button_init(uint32_t PORT_INDEX){
	PCC->PCCn[PORT_INDEX] = PCC_PCCn_CGC_MASK;

	// Set PTC12 (SW3) as GPIO
	PORTD->PCR[SW3_PIN] = PORT_PCR_MUX(2);

	// Set PTC12 as input
	PTC->PDDR &= ~(1 << SW3_PIN);

	// Enable pull-up resistor for SW3 button (active-low button)
	PORTD->PCR[SW3_PIN] |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	//Set button press of SW3
	//PORTD->PCR[0] = 0x00000100;

	//Changes led on/off
	//	PTD->PDDR |= 1<<PTD0;
}

int main(void){
//	watchDogDisable();
	SOSC_init_8MHz();
	SPLL_init_160MHz();
	NormalRUNmode_80MHz();


	LPUART_PORT_init(PCC_PORTC_INDEX);
	SW3_button_init(PCC_PORTD_INDEX);
	LPUART_init(LPUART1, 9600, 8);


	LPUART0_send_string("this is working1\r\n");


	//Initializes LPUART0 with a baud rate of 9600 and SOSC of 8MHz
	//LPUART_init(LPUART0, 9600, 8);

//	LPUART0_init();
//	LPUART0_send_string("this is working2\r\n");
	//LPUART_send_string(LPUART0, "this is working2\r\n");
	while(1) {
		if(PTC->PDIR & (1<<PTC12)){
			LPUART0_send_string("button working1\r\n");
			PTD-> PCOR |= 1<<PTD0;
		//if(PTC->PDIR & (1<<PTC12)){
		//if(SW3_PORT->PDIR & (1<<SW3_PIN)){
		//if(!(PTC->PDIR & (1 << SW3_PIN))){
			//LPUART_send_string(LPUART0, "button working123\r\n");
			//while(!(PTC->PDIR & (1 << SW3_PIN))){};
//			PTD-> PCOR |= 1<<PTD0;
		}

	}
}





















