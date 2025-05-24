#include "AT89X51.h"

/** README
 * 1. IT0 is the register interrupt 0(INT0)
 *   (1) set to bit 1 means falling edge triggered
 *   (2) set to bit 0 means low-level triggered
 * 2. IE is interrupt enable register(bit addressable)
 *   (1) EA | - | - | ES | ET1 | EX1 | ET0 | EX0
 *   (2) EA for global, ES for serial port, ET for timer, EX for external
 *   (3) bit 1 is enable and bit 0 is disable
 */
 
void delay(int);

int main (void){
    
    IT0 = 1;   // 0 for low-level ot 1 for falling edge triggered
    IE = 0x81; // IE register = 1000 0001

    while(1){
        P2_0 = ~P2_0; // P2.0 flashing
        delay(333);   // about 1 second
    }
    return 0;
}

void INT0_ISR() interrupt 0{
    int i;
    
    P2_0 = 1;        // P2.0 dark
    
    for (i = 0; i < 8; i++){
        P2_1= ~P2_1; // P2.1 flashing
        delay(333);
    }
}

void delay(int time){
    int i, j;
    
    for (i = 0; i < time; i++){
        for (j = 0; j < 144; j++){
        }
    }
}
