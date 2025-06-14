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

unsigned int count = 1000;         // default: 3000 (approximate 1 sec)
unsigned int start = 65536 - 1000; // default: 65536 - 1000

void timer0_init(void);
void delay(unsigned int);

int main(void) {
    /** initialize timer0
     * In here, we use mode 1 so the total length of contatiner is 2 bytes(TH0 | TL0)
     * We set start value is 2^8 - 1000 = 65536 - 1000
     * Thus it will spend (1.059e-6 * 1000) sec when counting from start to max value
     */
    timer0_init();
    TH0 = start / 256;
    TL0 = start % 256;
    
    // time0 interrupt setup
    IE = 0x82; // 1000 0010    
    
    P2 = 0xF0; // 1111 0000
    
    while(1);
    
    return 0;
}
    
void timer0_init(void) {

    TCON = 0x10; // 0001 0000, use time0
    TMOD = 0x01; // 0000 0001, use time0 and mode 1
}

void timer0_ISR(void) interrupt 1 {
    /** reset container
     * When timer0 overflow, the flag TF0 will be set and interrupt will be triggered
     * In ISR, we must reset start value
     * The flag TF0 will be clear automatically by HW
     * If count = 0, we reset it, otherwise we decrease it
     * Supposed count = 1000, the total delay time = (1.059e-6 * 1000 * count) = 1.059 sec
     */
    
    TH0 = start / 256;
    TL0 = start % 256;
    
    if (count == 0) {
        P2 = ~P2;
        count = 1000; // reset, as same sa the global variable count
    }
    else {
        count--;
    }
}


