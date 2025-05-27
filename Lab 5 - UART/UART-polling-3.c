/** README
 * In this project, we use self-defined string compare function and take '.' as the ending character of string
 * Since the strcmp() in standard library is too big and we have to save some memory space.
 * First we polling the RI register, if SUBF get input character then we clear RI and move the input character into recvBuff[i]
 * After getting entire character, we compare these string.
 */
 
#include <REGX51.h>
#define SIZE 4

void init_UART(unsigned int);
unsigned char self_strcmp(unsigned char *, unsigned char *);

unsigned char recvBuff[SIZE]; // global array

int main(void) {
    unsigned int i = 0;
    unsigned int baudRate = 9600;
    
    init_UART(baudRate);
    
    while (1) {
        do {
            while (RI == 0); // polling register RI
            RI = 0;          // clear RI
            recvBuff[i++] = SBUF;
        } while (recvBuff[i - 1] != '.'); // use '.' as end of string
        
        i = 0;
        
        /** compare strings
         * if same, self_strcmp() return 1
         * if different, self_strcmp() return 0
         */
        if (self_strcmp(recvBuff, "MCU.")) {
            P2 = 0x0F; // 0000 1111
        }
        else {
            P2 = 0xF0; // 1111 0000
        }
    }
}

void init_UART(unsigned int baudRate) {
    TH1 = 256 - (28800 / baudRate);
    SCON = 0x50;
    TMOD = 0x20;
    TR1 = 1;
}

unsigned char self_strcmp(unsigned char *recvBuff, unsigned char *string) {
    unsigned int i;
    
    for (i = 0; (recvBuff[i] != '.') && (string[i] != '.'); i++) {
        if (*(recvBuff + i) != string[i]) {
            return 0;
        }
    }
    if (recvBuff[i] == string[i]) {
        return 1;
    }
    else {
        return 0;
    }
}