/** README
 * This code is same as UART with interrupt.
 * We trigger interrupt by arduino rather than by manual
 */
#include <REGX51.h>

void delay(int);
void init_UART(void);

int main(void) {
    init_UART();
    
    while (1) {
        SBUF = '7';
        delay(666);
    }
    
    return 0;
}

void init_UART() {
    /* UART setting */
    TH1 = 0xFD;
    SCON = 0x50;
    TMOD = 0x20;
    TR1 = 1;
    
    /* UART interrupt setting */
    ES = 1; // serial port enable
    EA = 1; // global enable
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
    unsigned i, j;
    for (i = 0; i < time; i++){
        for (j = 0; j < 114; j++) {
        }
    }
}
