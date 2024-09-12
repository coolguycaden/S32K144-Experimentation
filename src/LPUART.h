#include "S32K144.h"

void LPUART1_init(void);
void LPUART1_transmit_char(char);
void LPUART1_transmit_string(char[]);
char LPUART1_receive_char(void);
void LPUART1_receive_and_echo_char(void);
