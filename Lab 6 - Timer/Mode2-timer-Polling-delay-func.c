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
void delay(unsigned int);

int main(void) {
    unsigned int sec = 2;
    
    timer0_init();
    
    while (1) {
        P2 = 0xFE;  // 1111 1110
        delay(sec); // delay time for second
        P2 = 0x7F;  // 0111 1111
        delay(sec);
    }
    
    return 0;
}

void timer0_init(void) {
    TCON = 0x10;
    TMOD = 0x02; // mode 2 and timer0
}

void delay(unsigned int sec) {
    /** initialize default value
     * In this function, timer will count (200 * 5000 * sec) times.
     * And it will spend (200 * 5000 * sec * 1.085e-6) sec = 1.085 sec
     */
    unsigned int count = 5000 * sec;
    TL0 = 256 - 200;
    TH0 = 256 - 200;
    
    while (count) {
        while (TF0 != 1);
        TF0 = 0;
        count--;
    }
}
    