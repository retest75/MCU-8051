/** README
 * 1. TCON: Timer/Counter Control Register (bit addressable)
 *  (1) | TF1 | TR1 | TF0 | TR0 | IE1 | IT1 | IE0 | IT0 |
 *  (2) TFx is flag of Timer_x, x = 0, 1
 *  (3) TRx is switch of Timer_x, x = 0, 1 where ser/clear to turn on/off
 * 2. TMOD: Timer/Counter Mode Control Register(byte addressable)
 *  (1) | GATE | C/T | M1 | M0 | GATE | C/T | M1 | M0 |
 *      |       Timer 1        |       Timer 0        |
 *  (2) GATE is a part of timer switch
 *  (3) C/T control triggered method, 1 for counter and 0 for timer
 * 3. IE: Interrupt Enable Register (bit addressable)
 *  (1) | EA | - | - | ES | ET1 | EX1 | ET0 | EX0 |
 * 4. In this experiment, we use crystal with 11.059 MHz 
 *  (1) That means timer will count to 0.921e06 /s theorily
 *  (2) In other word, it must spend 1.085e-6 sec counting one
 */

#include <REGX51.h>
void timer0_init(void);
void delay(int);

int main(void) {
    // initialize timer0
    unsigned int start = 256 - 5;
    timer0_init();
    TL0 = start; // container
    TH0 = start; // default value
    
    
    // interrupt setup
    IE =0x82;    // 1000 0010
    
    while (1) {
        P2 = 0xAA; // 1010 1010
        delay(333);
        P2 = ~P2;
        delay(333);
    }
    
    return 0;
}

void timer0_init(void) {
    TCON = 0x10; // 0001 0000
    TMOD = 0x06; // 0000 0110, mode 2 and counter0
}

void delay(int count) {
    int i, j;
    
    for (i = 0; i <count; i++) {
        for (j = 0; j < 144; j++) {
        }
    }
}

void timer0_ISR(void) interrupt 1 {
    unsigned char i;
    
    // light from P2.0 to P2.7
    P2 = 0xFF;
    for (i = 0; i < 8; i++) {
        P2 = 0xFE << i;
        delay(333);
    }
    
    // dark from P2.7 to P2.0
    for (i = 0; i < 8; i++) {
        P2 = P2 | (0x80 >> i);
        delay(333);
    }
}
    
    
