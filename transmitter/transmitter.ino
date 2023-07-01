/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);  // CE, CSN

const byte address[6] = "00001";

//int led = 13; // define the LED pin
int digitalPin = 2;  // KY-026 digital interface
int analogPin = A0;  // KY-026 analog interface
int digitalVal;      // digital readings
int analogVal;       //analog readings

const char flame[] = "flame";
const char none[] = "none";

void setup() {
  Serial.begin(9600);

  pinMode(digitalPin, INPUT);

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {

  digitalVal = digitalRead(digitalPin);
  if (digitalVal == HIGH)  // if flame is detected
  {
    Serial.println(flame);  // print analog value to serial
    radio.write(&flame, sizeof(flame));
  } else {
    Serial.println(none);  // print analog value to serial
    radio.write(&none, sizeof(none));
  }
  // Read the analog interface
  analogVal = analogRead(analogPin);
  Serial.println(analogVal);  // print analog value to serial

  delay(2000);
}
