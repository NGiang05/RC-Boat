#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 8); // CE, CSN

int en = 3;
int in1 = 4;
int in2 = 5;

const byte address[6] = "00001";

// Max size of this struct is 32 bytes - NRF24L01 buffer limit
float data[2];

void setup() {
  pinMode(en, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

int speedControl = 255;

void loop() {
  // Check whether there is data to be received
  if (radio.available()) {
    radio.read(data, sizeof(data)); // Read the whole data and store it into the 'data' structure
    Serial.print("a: ");
    Serial.print(data[0]);
    Serial.print("b: ");
    Serial.println(data[1]);
  }
  /*
  //PWM outputs for speed are from 0 to 255
  if (speedControl == 0) { speedControl = 255;}
  analogWrite(en, speedControl);
  speedControl--; 

  //set direction = clockwise
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  delay(10);
  */
}
