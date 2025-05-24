#include "AT89X51.h"

#define HIGH 1
#define LOW 0

void delay(int);

int main(void){
    /**
     * in 8051 MCU, the size of sign/unsign int data type is 2 bytes (= 16 bits)
     * however, each port just have 8 pins (= 8 bits)
     * so the higher bits would be omit and retain the lower 8 bits
     */
    unsigned int pin = 1; // pin = 0000 0000 0000 0001
    
    while(1){
        P2 = ~pin; // only retain 8 lower bits, P2 = 1111 1110
        
        // detect input
        if (P1_0 == LOW){
            pin = pin << 1;
            
            if (pin > 0x80){
                pin = 1;
            }
            delay(666/4);
        }
    }
}

void delay(int time){
    int i, j;
    
    for(i = 0; i < time; i++){
        for(j = 0; j < 144; j++){
        }
    }
}