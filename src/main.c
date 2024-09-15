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
void LPUART_PORT_init(PORT_Type *port){


	//Changes port_index based on the value of the PCC index offsets
	//E.g. PORTA has a PCC index offset of 73
	uint32_t port_index = 75;
	if(port == PORTA){
		port_index = 73;
	} else if (port == PORTB){
		port_index = 74;
	} else if (port == PORTC){
		port_index = 75;
	} else if (port == PORTD){
		port_index = 76;
	} else if (port == PORTE){
		port_index = 77;
	} else {
		port = PORTC;
	}

	//Port C will be used for LPUART
	PCC->PCCn[port_index] = PCC_PCCn_CGC_MASK;

	//Set UART for PORT C
	port->PCR[6] |= PORT_PCR_MUX(2);
	port->PCR[7] |= PORT_PCR_MUX(2);


	//Set LPUART to receive button press
	PTC->PDDR &= ~(1<<PTC12);
	port->PCR[12] = 0x00000110;
}


//Enables the SW3 button (PTC12) to be pressed and print terminal output
void SW3_button_init(PORT_Type *port){

	uint32_t port_index = 75;
	if(port == PORTA){
		port_index = 73;
	} else if (port == PORTB){
		port_index = 74;
	} else if (port == PORTC){
		port_index = 75;
	} else if (port == PORTD){
		port_index = 76;
	} else if (port == PORTE){
		port_index = 77;
	} else {
		port = PORTD;
	}

	PCC->PCCn[port_index] = PCC_PCCn_CGC_MASK;

	// Set PTC12 (SW3) as GPIO
	port->PCR[PTC12] = PORT_PCR_MUX(2);

	// Set PTC12 as input
	PTC->PDDR &= ~(1 << PTC12);

	// Enable pull-up resistor for SW3 button (active-low button)
	port->PCR[PTC12] |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;



	//Set button press of SW3
	//PORTD->PCR[0] = 0x00000100;

	//Changes led on/off
	//	PTD->PDDR |= 1<<PTD0;
}

int main(void){
	//watchDogDisable();
	SOSC_init_8MHz();
	SPLL_init_160MHz();
	NormalRUNmode_80MHz();


	LPUART_PORT_init(PORTC);
	SW3_button_init(PORTD);

	//Initializes LPUART0 with a baud rate of 9600, 8MHz
	LPUART_init(LPUART1, 9600, 8);


	LPUART0_send_string("this is working5\r\n");

	while(1) {
		if(PTC->PDIR & (1<<PTC12)){
			LPUART_send_string(LPUART1, "button working123\r\n");
			while(PTC->PDIR & (1 << PTC12)){};
			PTD-> PCOR |= 1<<PTD0;
		}

	}
}





















