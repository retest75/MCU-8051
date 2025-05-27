/** README
 * This experiment is the implement of UART
 * We first tramsmit some message then receive message from user input
 * Befor beginning, we must setup some SPF register about UART
 * SCON is the Serial Port Control Register
 *  (1) | SM0 | SM1 | SM2 | REN | TN8 | RB8 | TI | RI |
 *  (2) SM0 and SM1 used to select mode
 *  (3) REN used to enable/disable reception if we set/clear by software
 *  (4) TI/RI is the interrupt flag of Transmit/Receiver and we must clear manually after it was triggered
 * TH1 is the high byte of Timer 1, it is concerned about baud rate
 * TMOD is Timer Mode Control Register
 * TR1 is the Timer1 controller, see more details in TCON
 * SBUF is the serial buffer
 */
 
#include <REGX51.h>
#define SEND_SIZE 4
#define RECV_SIZE 2
 
void init_UART(unsigned int);

int main(void) {
    unsigned char sendBuff[SEND_SIZE] = {'M', 'C', 'U', '.'};
    unsigned char recvBuff[RECV_SIZE];
    unsigned int i;
    unsigned int baudRate = 9600;
    
    init_UART(baudRate);
    
    while (1) {
        /** Remark: transmit data
         * 1. The buffer, SBUF get 1 byte output data from sendBuff
         * 2. Polling register TI which is the flag of Tx
         *  (1) If TI = 0, that means the data have not been transmit from SBUF
         *  (2) If TI = 1, that means the data have already been transmit from SBUF
         * 3. Then exit second while loop and clear the TI register manually
         */
        for (i = 0; i < SEND_SIZE; i++) {
            SBUF = sendBuff[i]; // transmit mode
            while (TI == 0);    // polling register TI
            TI = 0;             // clear TI
        }
        
        /** Remark: receive data
         * 1. Polling register RI, which is the flag of Rx
         *  (1) If RI = 0, that means SBUF have not received input data
         *  (2) If RI = 1, that meand SBUF get the input data
         * 2. Then exit the third while loop and clear the RI register manually
         * 3. move the input data from SBUF to recvBuff
         */
        for (i = 0; i < RECV_SIZE; i++) {
            while (RI == 0);    // polling register RI
            RI = 0;             // clear RI
            recvBuff[i] = SBUF; // receive mode
        }
        
        /** Remark: check input data and give a corresponding response
         * 1. If MCU get "OK" by UART, light LED
         * 2. If MCU didn't get "OK" by UART, dark LED
         * 3. You can change the LED number
         */
        if (recvBuff[0] == 'O' && recvBuff[1] == 'K') {
            P2 = 0X55; // 0101 0101
        }
        else {
            P2 = 0xAA; // 1010 1010
        }
    }
}

/** initiate UART
 * Baud rate = 9600
 * Mode: 1
 * Timer: turn on Timer 1
 */

void init_UART(unsigned int baudRate) {
    TH1 = 256 - (28800 / baudRate);
    SCON = 0x50; // 0101 0000
    TMOD = 0x20; // 0010 0000
    TR1 = 1;     // turn on Timer 1, see TCON to get more details
}