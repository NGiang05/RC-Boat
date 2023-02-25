#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 8); // CE, CSN

const byte address[6] = "00001";

// Max size of this struct is 32 bytes - NRF24L01 buffer limit
float data[2];

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  // Check whether there is data to be received
  if (radio.available()) {
    radio.read(data, sizeof(data)); // Read the whole data and store it into the 'data' structure
  Serial.print("a: ");
  Serial.print(data[0]);
  Serial.print("b: ");
  Serial.println(data[1]);
  }
}
