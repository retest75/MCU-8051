#include "AT89X51.h"

/** README
 * 1. IT0 and IT1 are the register interrupt 0 (INT0) and interrupt 2 (INT1)
 *  (1) set to bit 1 will lead to falling edge trigger
 *  (2) set to bit 0 will lead to low-level trigger
 * 2. IE is interrupt enable register (bit addressable)
 *  (1) | EA | - | - | ES | ET1 | EX1 | ET0 | EX0 |
 *  (2) bit 1 is enable and bit 0 is disable
 * 3. PX is  interrupt priority register (bit addressable)
 *  (1) | - | - | - | PS | PT1 | PX1 | PT0 | PX0 |
 *  (2) PS for serial port, PX for external interrupt, PT for timer interrupt
 *  (3) bit 0 is lower priority and bit 1 is higher priority
 */ 
void delay(int);

int main(void){
    IT0 = 1; // set INT0 to falling edge/low-level trigger
    PX0 = 0; // set INT0 to lower/higher priority

    IT1 = 1; // set INT1 to falling edge/low-level trigger
    PX1 = 1; // set INT1 to lower/higher priority
    
    IE = 0x85; // IE = 1000 0101
    
    while (1){
        P2_0 = ~P2_0; // P2.0 flashing
        delay(333);   // delay about 0.5 sec
    }
    
    return 0;
}

void INT0_ISR() interrupt 0{
    int i;
    
    P2_0 = 1; // P2.0 dark
    P2_2 = 1; // P2.1 dark
    
    for (i = 0; i < 8; i++){
        P2_1 = ~P2_1;
        delay(333);
    }
}

void INT1_ISR() interrupt 2{
    int i;
    
    P2_0 = 1; // P2.0 dark
    P2_1 = 1; // P2.1 dark
    for (i = 0; i < 8; i++){
        P2_2 = ~P2_2;
        delay(333);
    }
}

void delay(int time){
    int i;
    int j;
    
    for (i = 0; i < time; i++){
        for (j = 0; j < 144; j++){
        }
    }
}
