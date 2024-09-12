///*
// * Copyright 2020 NXP
// * All rights reserved.
// *
// * NXP Confidential. This software is owned or controlled by NXP and may only be
// * used strictly in accordance with the applicable license terms. By expressly
// * accepting such terms or by downloading, installing, activating and/or otherwise
// * using the software, you are agreeing that you have read, and that you agree to
// * comply with and are bound by, such license terms. If you do not agree to be
// * bound by the applicable license terms, then you may not retain, install,
// * activate or otherwise use the software. The production use license in
// * Section 2.3 is expressly granted for this software.
// */
//
//#define EVB
//
//#ifdef EVB
//	#define PCC_CLOCK	PCC_PORTD_CLOCK
//	#define LED0_PORT PTD
//	#define LED0_PIN  15
//	#define LED1_PORT PTD
//	#define LED1_PIN  16
//#else
//	#define PCC_CLOCK	PCC_PORTC_CLOCK
//	#define LED0_PORT PTC
//	#define LED0_PIN  0
//	#define LED1_PORT PTC
//	#define LED1_PIN  1
//#endif
//
//#include "sdk_project_config.h"
//
void delay(volatile int cycles)
{
    /* Delay function - do nothing for a number of cycles */
    while(cycles--);
}
//
//int main(void)
//{
//  status_t error;
//  /* Configure clocks for PORT */
//  error = CLOCK_DRV_Init(&clockMan1_InitConfig0);
//  DEV_ASSERT(error == STATUS_SUCCESS);
//  /* Set pins as GPIO */
//  error = PINS_DRV_Init(NUM_OF_CONFIGURED_PINS0, g_pin_mux_InitConfigArr0);
//  DEV_ASSERT(error == STATUS_SUCCESS);
//
//  /* Set Output value LED0 & LED1 */
//  PINS_DRV_SetPins(LED0_PORT, 1 << LED0_PIN);
//  PINS_DRV_ClearPins(LED1_PORT, 1 << LED1_PIN);
//
//  for (;;)
//  {
//      /* Insert a small delay to make the blinking visible */
//      delay(720000);
//
//      /* Toggle output value LED0 & LED1 */
//      PINS_DRV_TogglePins(LED0_PORT, 1 << LED0_PIN);
//      PINS_DRV_TogglePins(LED1_PORT, 1 << LED1_PIN);
//  }
//}



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

	PCC->PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK;
	PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK;

	//Set UART for PORT C
	PORTC->PCR[6] |= PORT_PCR_MUX(2);
	PORTC->PCR[7] |= PORT_PCR_MUX(2);

	//Set Receiving for PORT
	 PTD->PDDR &= ~(1<<PTC12);
	 PORTD->PCR[12] = PORT_PCR_MUX(2);
}

int main(void){
	watchDogDisable();
	SOSC_init_8MHz();
	SPLL_init_160MHz();
	NormalRUNmode_80MHz();
	PORT_init();

	LPUART1_init();
	LPUART1_transmit_string("Running LPUART example\n\r");
	LPUART1_transmit_string("Input character to echo...\n\r");



	for(;;) {
		if(PTD->PDIR & (1<<PTC12)){
			LPUART1_transmit_char('o');
			LPUART1_transmit_char('n');
			LPUART1_transmit_char('\n');
		}
//		} else {
//			LPUART1_transmit_char('o');
//			LPUART1_transmit_char('f');
//			LPUART1_transmit_char('f');
//			LPUART1_transmit_char('\n');
//
//		}

		//wait 2 seconds
		delay(10000000);
		//LPUART1_transmit_char('>');
		//LPUART1_receive_and_echo_char();
	}
}


//Press SW3 to get message

//#include "S32K144.h"
//#include "clock_config.h"
//#include "LPUART.h"
//
//char data = 0;





















