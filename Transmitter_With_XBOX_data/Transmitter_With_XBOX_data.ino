// for XBOX and USB shield
#include <XBOXONE.h>
// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif

#include <SPI.h>

// for wireless connection
#include <nRF24L01.h>
#include <RF24.h>

//variables for USB shield and XBOX
USB Usb;
XBOXONE Xbox(&Usb);

//variables for wireless connection and data
RF24 radio(9, 8); // CE, CSN

const byte address[6] = "00001";

// Max size of this struct is 32 bytes - NRF24L01 buffer limit
float data[2];

void setup() {
    radio.begin();
    radio.openWritingPipe(address);
    radio.setPALevel(RF24_PA_MIN);
    radio.stopListening();


    Serial.begin(115200);
    while (!Serial); // wait for serial port to connect
    if (Usb.Init() == -1) {
        Serial.print(F("\rnOSC did not start"));
        while (1); //halt
    }
    Serial.print(F("\r\nXBOX ONE USB Library Started"));
}

void loop() {
    Usb.Task();
    if (Xbox.XboxOneConnected) {
        if (Xbox.getAnalogHat(LeftHatX) < -7500 || Xbox.getAnalogHat(LeftHatX) > 7500) {
            data[0] = Xbox.getAnalogHat(LeftHatX);
        } else {
            data[0] = 0.0;
        }

        data[1] = Xbox.getButtonPress(RT); 
    }
    

    Serial.print(F("LeftX: "));
    Serial.print(data[0]);
    Serial.print("\t");

    Serial.print(F("RT: "));
    Serial.print(data[1]);
    Serial.print("\t\n");

    // sending the data from the structure to the receiver
    radio.write(&data, sizeof(Data_Package));
    //delay(100);
}
