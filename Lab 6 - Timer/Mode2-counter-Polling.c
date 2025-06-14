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
 * 3. In this experiment, we use crystal with 11.059 MHz 
 *  (1) That means timer will count to 0.921e06 /s theorily
 *  (2) In other word, it must spend 1.085e-6 sec counting one
 */

#include <REGX51.h>

void timer0_init(void);
void delay(int);

int main(void) {
    /** Initialize timer0
     * Here we use counter with mode 2
     * And we setup start = 256 - 5 as our default value
     */
    unsigned int start = 256 - 5;
    unsigned char i;
    timer0_init();
    TL0 = start;
    TH0 = start;
    
    // standby
    for (i = 0; i < 8; i++) {
        P2 = 0xFE << i;
        delay(333);
    }
    
    while (1) {
        // wait and flash
        P2 = 0xF0;
        delay(333);
        P2 = 0xFF;
        delay(333);
        
        /** Overflow
         * When counter0 overflaw, its flag TF0 is set
         * So we constantly polling its flag TF0
         * Once the flag TF0 is set, we clear it and give some response
         */
        if (TF0 == 1) { // polling TF0 constantly
            P2 = 0xFF;  // reset Port 2
            TF0 = 0;    // clear flag TF0
            for (i = 0; i < 8; i++) {
                P2 = 0x7F >> i; // 0111 1111 >> i
                delay(333);
            }
        }
    }
    
    return 0;
}

void timer0_init(void) {
    TCON = 0x10; // 0001 0000
    TMOD = 0x06; // 0000 0110, mode 2 & counter
}
    
void delay(int count) {
    int i, j;
    
    for (i = 0; i < count; i++) {
        for (j = 0; j < 144; j++) {
        }
    }
}