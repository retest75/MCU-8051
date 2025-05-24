#include "AT89X51.h"

/** README
 * This experiment is the implement of open drain.
 * open drain means the port 0 can't output High.
 * The LED must use source current i.e.,  positive connect to port 0 and negative connect to ground.
 * After we run this code, the LED will not be lighted since there is not any output of port 0.
 * If you want to light LED, adding an pull-up resistance.
 * That means one pin connect to VCC and another pin connected to LED, then LED will be lighted
 */
 


int main(void){
    
    P0 = 0x00; // output High
    for (;;)
    
    return 0;
}