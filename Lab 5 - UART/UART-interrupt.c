/** README
 * This project implement UART with interrupt.
 * In init_UART(), we not only initiate the UART setting but turning on the UART interrupt.
 * Interrupt Enable Register(IE)
 *  (1) | EA | - | - | ES | ETI | EX1 | ET0 | EX0 |
 *  (2) EA: global interrupt, ES: serial port interrupt
 *  (3) we can settup by bit addressable or bytes addressable
 * The UART interrupt is No. 4, so we use keyword interrupt 4 to define its ISR
 *  (1) Because we don't know which registers(RI/TI) trigger the interrupt, we have to check in ISR
 *  (2) If RI trigger, then we clear it and check input character
 *  (3) If TI trigger, then we cleat it and do nothing
 */
 
#include <REGX51.h>
#include <stdio.h>

void init_UART(void);
void delay(int);

int main(void) {
    init_UART();
    
    while (1) {
        SBUF = '7'; // transmit mode
        delay(666);
    }
    
    return 0;
}
    
void init_UART(void) {
    /* UART setting */
    TH1 = 0xFD;
    SCON = 0x50;
    TMOD = 0x20;
    TR1 = 1;
    
    /* UART interrupt setting */
    ES = 1;    // serial port enable
    EA = 1;    // global enable
    //IE = 0x90; // bytes addressable: 1001 0000
}

void UART_ISR(void) interrupt 4 {
    unsigned char buffer;
    
    if (RI == 1) {
        RI = 0;
        buffer = SBUF;
        
        if (buffer == '6') {
            P2 = 0xF0;
        }
        else {
            P2 = 0x0F;
        }
    }
    else if (TI == 1) {
        TI = 0;
    }
}

void delay(int time) {
    int i, j;
    
    for (i = 0; i < time; i++) {
        for (j = 0; j < 144; j++) {
        }
    }
}
