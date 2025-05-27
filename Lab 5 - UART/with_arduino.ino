/*
  8051 MCU LAB WITH Atmega328P UART 
*/

void setup()
{
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop()
{

 if(Serial.available())
 {
    if(Serial.read() == '7') // receive
    { 
		Serial.print('6');       // transmit
 		// turn the LED on (HIGH is the voltage level)
  		digitalWrite(13, HIGH);
    }
    else
    {
  		// turn the LED oFF
  	     digitalWrite(13, LOW);

     }
 }
 
  
}
