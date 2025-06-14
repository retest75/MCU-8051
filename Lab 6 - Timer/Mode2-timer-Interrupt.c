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
unsigned int count = 5000; // default = 5000

int main(void) {
    /** Initialize timer
     * In here, we use mode 2.
     * So TL0 is used as container and TH0 is used to save default start valur
     * And both oh them are 8-bits length.
     * Thus we set the default start value is 2^8 - 200 = 256 - 200
     * If TL0 overflow, it will auto-reload from TH0
     * The real world time is (1.059e-6 * start) sec when TL0 overflow
     */
    unsigned int start = 256 - 200;
    
    timer0_init();
    TL0 = start;
    TH0 = start;
    
    // setup interrupt system
    IE = 0x82; // 1000 0010
    
    P2 = 0XF0;
    while (1);
    
    return 0;
}

void timer0_init(void) {
    TCON = 0x10; // 0001 0000
    TMOD = 0x02; // 0000 0010
}

void timer0_ISR(void) interrupt 1 {
    /** interrupt
     * Since we use mode 2, the default value in TH0 will auto reload into TL0.
     * The flag of timer0 TF0 will clear automatically.
     * We just only check count.
     * It will delay (1.085e-6 * start * count) = (1.085e-6 * 200 * 5000) = 1.085 sec
     */
    if (count == 0) {
        P2 = ~P2;
        count = 5000;
    }
    else {
        count--;
    }
}
