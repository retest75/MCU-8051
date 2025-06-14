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
 *  (2) In other word, it must spend 1.085e-6 sec count one
 */

#include <REGX51.h>

void timer0_init(void);
void delayms(unsigned int);

int main(void) {
    unsigned int count = 2000; // default: 1000
    
    timer0_init();
    
    while(1) {
        P2 = 0x0F;      // 0000 1111
        delayms(count); // default: approximate 1 sec if count = 1000
        P2 = ~P2;       // 1111 0000
        delayms(count);
    }
    
    return 0;
}

void timer0_init(void) {
    TCON = 0x10; // 0001 0000, use time0
    TMOD = 0x01; // 0000 0001, use timer0 and mode 1
}

void delayms(unsigned int count) {
    /** Parameter
     * Assume the start point is ST
     * This function will delay (1.085e-6 * ST * count) sec
     */
    
    /** Initialize
     * Here we use mode 1
     * THO save more higher 8-bits and TL0 save more lower 8-bits
     * The total length is 16-bits and max value is 2^16 = 65536
     * We set start point = 65536 - 1000
     * So it will delay (1.085e-6 * 1000) sec when counting from start to 65536 
     */
    unsigned int start = 65536 - 1000;
    
    TH0 = start / 256;
    TL0 = start % 256;
    TF0 = 0; // clear flag
    
    /** Pollint flag of timer0, TF0
     * when timer0 overflow its flag TF0 will be set
     * Once TF0 is set, we clear it and reset TH0 and TL0 to defaut value
     * Supposed count = 1000, it will delay (1.085e-6 * 1000 * count) = 1.085 sec
     */
    while(count) {
        while(TF0 != 1); // polling timer 0 flag
        
        // the reset motion will lead to error
        TH0 = start / 256;
        TL0 = start % 256;
        TF0 = 0;
        
        count--;
    }
}
    