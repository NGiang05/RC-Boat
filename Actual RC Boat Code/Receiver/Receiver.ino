#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

RF24 radio(9, 8); // CE, CSN

const int en = 3;
const int in1 = 4;
const int in2 = 5;

const int servoPin = 6;
int servo; 
int motor; 

Servo myservo;

const byte address[6] = "00001";

// Max size of this struct is 32 bytes - NRF24L01 buffer limit
float data[2]; // first index is for the servo and the second index is for the motor

void setup() {
  myservo.attach(servoPin); 

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
  
  servo = map(data[0], 0, 1023, 0, 180);
  motor = map(data[1], 0, 1023, -255, 255); 

  if (motor < 0) { // PWM outputs for speed are from 0 to 255
    analogWrite(en, motor * -1); 
    digitalWrite(in1, LOW); 
    digitalWrite(in2, HIGH);
  } else {
    analogWrite(en, motor);  
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }
  myservo.write(servo);
}
