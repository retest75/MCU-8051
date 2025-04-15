#include "delay.h"
#include "flashing.h"

int main(void){
    int time = 666; // approzimate 1 sec
    
    //pureFlash(time);
    alternatingFlash(time);
    
    return 0;
}