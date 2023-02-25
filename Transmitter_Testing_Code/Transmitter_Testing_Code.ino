// Link to tutorial: https://lastminuteengineers.com/nrf24l01-arduino-wireless-communication/
//https://howtomechatronics.com/tutorials/arduino/arduino-wireless-communication-nrf24l01-tutorial/


#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 8); // CE, CSN

const byte address[6] = "00001";

// Max size of this struct is 32 bytes - NRF24L01 buffer limit
struct Data_Package {
  byte a = 0;
  byte b = 125;
  byte c = 255;
  int d = 1024;
  float e = 3.141592;
  String f = "Test";
};

Data_Package data; // Create a variable with the above structure

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  // Send the whole data from the structure to the receiver
  radio.write(&data, sizeof(Data_Package));
  delay(500);
}
