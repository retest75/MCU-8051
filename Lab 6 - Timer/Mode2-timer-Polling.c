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
void delayms(unsigned int);
 
int main(void) {
    unsigned int ms = 2000; // milli sec = 1e-3 sec
    timer0_init();
     
    while (1) {
       P2 = 0xF0;   // 1111 0000
       delayms(ms); // delay milli second time
       P2 = ~P2;    // 0000 1111
       delayms(ms);
    }
     
    return 0;
}
 
void timer0_init(void) {
    TCON = 0x10; // 0001 0000
    TMOD = 0x02; // 0000 0010
}
 
void delayms(unsigned int ms) {
    /** Initialize
     * In mode 2, TL0 is used as container with 8-bits length.
     * So its max value is 2^8 = 256.
     * TH0 is used to save default value of timer0.
     * Thus we set start point is 256 - 200 
     * In other words, timer will spend (1.085e-6 * 200) sec in real world approxinately when it occur overflow
     */
    unsigned int start = 256 - 200;
    unsigned int count;
    
    TL0 = start; // container
    TH0 = start; // auto-reload
     
    /** Polling
     * In here, we polling the flag of timer0, TF0.
     * If TL0 overflow, then TF0 is set.
     * Then we just clear TF0 since the default value in TH0 will auto reload into TL0.
     * On the other hands, we set count = ms * 5.
     * Supposed ms = 1, this function will delay (1.085e-6 * 200 * cnt) = 1.085e-3 sec
     */
    count = ms * 5;
    while (count) {
        while (TF0 == 0); // polling TF0
        TF0 = 0;          // clear flag
        count--;
    }
}
 