// Link to tutorial: https://lastminuteengineers.com/nrf24l01-arduino-wireless-communication/
//https://howtomechatronics.com/tutorials/arduino/arduino-wireless-communication-nrf24l01-tutorial/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define joyX1 A0
#define joyY2 A1

RF24 radio(9, 8); // CE, CSN

const byte address[6] = "00001";

// Max size of this struct is 32 bytes - NRF24L01 buffer limit
float data[2] = {0,0};

//Data_Package data; // Create a variable with the above structure

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  Serial.begin(9600);
}

void loop() {
  // Send the whole data from the structure to the receiver
  data[0] = analogRead(joyX1);
  data[1] = analogRead(joyY2);

  Serial.print(data[0]); 
  Serial.print("\t"); 
  Serial.println(data[1]); 
  
  radio.write(data, sizeof(data));
  //delay(500);
}
