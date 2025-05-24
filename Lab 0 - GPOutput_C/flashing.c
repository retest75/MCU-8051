#include "AT89X51.H"
#include "delay.h"
#include "flashing.h"

void pureFlash(int time){
    while(1){
        P2 = ~P2;
        delay(time);
    }
}

void alternatingFlash(int time){
    
    P2 = P2 & 0xAA; // 1010 1010 = 1111 1111 & 1010 1010
    while(1){
        P2 = P2 ^ 0xFF;
        delay(time);
    }
}