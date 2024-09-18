#include "LPUART.h"

//Initializes LPUART0 to PORT C at 4.8 MHz, NOT multipurpose
void LPUART0_init(void){

	//Enable clock for LPUART0
	PCC->PCCn[PCC_LPUART0_INDEX] = PCC_PCCn_CGC_MASK;


	/* Initialize for 9600 baud, 1 stop: */
	/* SBR=52 (0x34): baud divisor = 8Mhz/9600/16 = ~52 */
	/* OSR=15: Over sampling ratio = 15+1=16 */
	/* SBNS=0: One stop bit */
	/* BOTHEDGE=0: receiver samples only on rising edge */
	/* M10=0: Rx and Tx use 7 to 9 bit data characters */
	/* RESYNCDIS=0: Resync during rec'd data word supported */
	/* LBKDIE, RXEDGIE=0: interrupts disable */
	/* TDMAE, RDMAE, TDMAE=0: DMA requests disabled */
	/* MAEN1, MAEN2, MATCFG=0: Match disabled */
	// 8 MHz / (16 * 9600) = ~52
	LPUART0->BAUD = 0x0F000034;

	// Enable transmitter and receiver
	/* Enable transmitter & receiver, no parity, 8 bit char: */
	/* RE=1: Receiver enabled */
	/* TE=1: Transmitter enabled */
	/* PE,PT=0: No hw parity generation or checking */
	/* M7,M,R8T9,R9T8=0: 8-bit data characters*/
	/* DOZEEN=0: LPUART enabled in Doze mode */
	/* ORIE,NEIE,FEIE,PEIE,TIE,TCIE,RIE,ILIE,MA1IE,MA2IE=0: no IRQ*/
	/* TxDIR=0: TxD pin is input if in single-wire mode */
	/* TXINV=0: TRansmit data not inverted */
	/* RWU,WAKE=0: normal operation; rcvr not in statndby */
	/* IDLCFG=0: one idle character */
	/* ILT=0: Idle char bit count starts after start bit */
	/* SBK=0: Normal transmitter operation - no break char */
	/* LOOPS,RSRC=0: no loop back */

	/*The 'C' in 0x000C0000 is the hexadecimal representation of the binary number of 12
	 * The bit representation of 12 is 1100, and the hexadecimal of 12 is C
	 * The bit 1100 comes from the TRANSMITTER and RECEIVER being assigned the value of 1 (on)
	 * which means the byte now has the value of 8 + 4, which is 12
	 */
	LPUART0->CTRL = 0x000C0000;
}


//Stolen from the S32K1xx Cookbook
/* Init. summary: 9600 baud, 1 stop bit, 8 bit format, no parity */
void LPUART1_init(void) {

	/* Ensure clk disabled for config */
	PCC->PCCn[PCC_LPUART1_INDEX] &= ~PCC_PCCn_CGC_MASK;

	/** Clock Src= 1 (SOSCDIV2_CLK) */
	PCC->PCCn[PCC_LPUART1_INDEX] |= PCC_PCCn_PCS(0b001) | PCC_PCCn_CGC_MASK;


 /* Initialize for 9600 baud, 1 stop: */
 /* SBR=52 (0x34): baud divisor = 8M/9600/16 = ~52 */
 /* OSR=15: Over sampling ratio = 15+1=16 */
 /* SBNS=0: One stop bit */
 /* BOTHEDGE=0: receiver samples only on rising edge */
 /* M10=0: Rx and Tx use 7 to 9 bit data characters */
 /* RESYNCDIS=0: Resync during rec'd data word supported */
 /* LBKDIE, RXEDGIE=0: interrupts disable */
 /* TDMAE, RDMAE, TDMAE=0: DMA requests disabled */
 /* MAEN1, MAEN2, MATCFG=0: Match disabled */
 LPUART1->BAUD = 0x0F000034;




 /* Enable transmitter & receiver, no parity, 8 bit char: */
 /* RE=1: Receiver enabled */
 /* TE=1: Transmitter enabled */
 /* PE,PT=0: No hw parity generation or checking */
 /* M7,M,R8T9,R9T8=0: 8-bit data characters*/
 /* DOZEEN=0: LPUART enabled in Doze mode */
 /* ORIE,NEIE,FEIE,PEIE,TIE,TCIE,RIE,ILIE,MA1IE,MA2IE=0: no IRQ*/
 /* TxDIR=0: TxD pin is input if in single-wire mode */
 /* TXINV=0: TRansmit data not inverted */
 /* RWU,WAKE=0: normal operation; rcvr not in statndby */
 /* IDLCFG=0: one idle character */
 /* ILT=0: Idle char bit count starts after start bit */
 /* SBK=0: Normal transmitter operation - no break char */
 /* LOOPS,RSRC=0: no loop back */
 LPUART1->CTRL=0x000C0000;

}

//Initializes LPUART given a LPUART instance (LPUART0, LPUART1, or LPUART2)
//The baudRate is the bits per second that the LPUART processes at
void LPUART_init(LPUART_Type *lpuart, uint32_t baudRate, uint32_t busClock){

	/*Initialize LPUART to the instance sent in, i.e. checking *lpuart if
	 * is equal to one of the three LPUART instances available
	 * (LPUART0, LPUART1, or LPUART2)
	 */
	//TODO: fix this formatting
	if (lpuart == LPUART0) {

		//Disables clock for config of LPUART
		PCC->PCCn[PCC_LPUART0_INDEX] &= ~PCC_PCCn_CGC_MASK;

		//TODO: fix hardcoded clock source
		//Changes the clock source  to 1, (SOSCDIV2_CLK)
		PCC->PCCn[PCC_LPUART0_INDEX] |= PCC_PCCn_PCS(0b001) | PCC_PCCn_CGC_MASK;
		
	} else if (lpuart == LPUART1) {

		//Disables clock for config of LPUART
		PCC->PCCn[PCC_LPUART1_INDEX] &= ~PCC_PCCn_CGC_MASK;

		//TODO: fix hardcoded clock source
		//Changes the clock source  to 1, (SOSCDIV2_CLK)
		PCC->PCCn[PCC_LPUART1_INDEX] |= PCC_PCCn_PCS(0b001) | PCC_PCCn_CGC_MASK;
		
	} else {

		//Defaults to initializing LPUART to LPUART2 instance

		//Disables clock for config of LPUART
		PCC->PCCn[PCC_LPUART2_INDEX] &= ~PCC_PCCn_CGC_MASK;

		//TODO: fix hardcoded clock source
		//Changes the clock source  to 1, (SOSCDIV2_CLK)
		PCC->PCCn[PCC_LPUART2_INDEX] |= PCC_PCCn_PCS(0b001) | PCC_PCCn_CGC_MASK;
	}

	// Set baud rate, this interprets busClock as being sent in as MHz and changes it into hz
	//This determines bits per second the LPUART reads at
	uint32_t sbr = ((busClock * 1000000) / (baudRate * 16));

	//sets BAUD rate of the LPUART, which is the bit rate determined above
	lpuart->BAUD = LPUART_BAUD_SBR(sbr);

	// Enable transmitters, this works because the C represents the byte 1100
	// That byte works because the first 1 represents TRANSMITTERS ON, the second represents RECEIVERS ON
	// The byte value of 1100 = 12, and 12 = C in hexadecimal
	lpuart->CTRL = 0x000C0000;
}

void LPUART_PORT_init(PORT_Type *port, LPUART_Type *lpuart){

	//Depending on port that is called to initialize LPUART,
	//it is necessary to change the port_index to turn on the clock for that port
	uint32_t port_index = 75;

	/* THIS IS IMPORTANT!!!
	 *  Different instances of LPUART have different pin values for receiving/transmitting.
	 *
	 *  Technically, you can hard-code transmitting/receiving pins regardless of LPUART instance but that is bad practice!!!
	 *
	 *  receiverPin and transmitterPin will change based off the sent in LPUART instance parameter
	 *
	 *
	 */
	int receiverPin = 6;
	int transmitterPin = 7;

	if(lpuart == LPUART0){

	} else if(lpuart == LPUART1){

	} else
	//Changes port_index based on the value of the PCC index offsets
	//E.g. PORTA has a PCC index offset of 73
	//TODO: fix this formatting to be more intuitive
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

		//Sets default port to PORTC, which has port_index of 75
		port = PORTC;
	}

	//The index of the port will be used for communicating to LPUART, turns on the clock for that port
	PCC->PCCn[port_index] = PCC_PCCn_CGC_MASK;

	//Sets the receving
	port->PCR[6] |= PORT_PCR_MUX(2);
	port->PCR[7] |= PORT_PCR_MUX(2);


	//Set LPUART to receive button press
	PTC->PDDR &= ~(1<<PTC12);
	port->PCR[12] = 0x00000110;
}

//Prints a string assuming LPUART0 has been initialized
void LPUART0_send_string(const char *str) {
    while (*str) {

    	// Wait until transmit buffer is empty
        while (!(LPUART1->STAT & LPUART_STAT_TDRE_MASK));

        // Send character
        LPUART1->DATA = *str++;
    }
}

/* Function to Transmit single Char */
void LPUART1_transmit_char(char send) { 
	
    /* Wait for transmit buffer to be empty */
    while((LPUART1->STAT & LPUART_STAT_TDRE_MASK)>>LPUART_STAT_TDRE_SHIFT==0);

     /* Send data */
    LPUART1->DATA=send;
}

/* Function to Transmit whole string */
void LPUART1_transmit_string(char data_string[]) { 
	
    /* Send chars one at a time */
    uint32_t i=0;
    while(data_string[i] != '\0') { 
        LPUART1_transmit_char(data_string[i]);
        i++;
    }
}

/* Function to Receive single Char */
char LPUART1_receive_char(void) { 
    char receive;

    /* Wait for received buffer to be full */
    while((LPUART1->STAT & LPUART_STAT_RDRF_MASK)>>LPUART_STAT_RDRF_SHIFT==0);
    
    
    /* Read received data*/
    receive= LPUART1->DATA; 
    
    return receive;
}

/* Function to echo received char back */
void LPUART1_receive_and_echo_char(void) { 
    
    /* Receive Char */	
    char send = LPUART1_receive_char(); 
    
    /* Transmit same char back to the sender */
    LPUART1_transmit_char(send); 

    /* New line */
    LPUART1_transmit_char('\n'); 
}


//ChatGPT generated, general purpose string printing, assumes LPUART is initialized
void LPUART_send_string(LPUART_Type *lpuart, const char *str) {
    while (*str) {
	    
        // Wait until transmit buffer is empty
        while (!(lpuart->STAT & LPUART_STAT_TDRE_MASK));
	    
        // Send character
        lpuart->DATA = *str++;
    }
}
