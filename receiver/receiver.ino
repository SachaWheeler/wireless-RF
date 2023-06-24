/*
* Arduino Wireless Communication Tutorial
*       Example 1 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <LedControl.h>


RF24 radio(7, 8);  // CE, CSN

const byte address[6] = "00001";

// Matrix
const int DIN_PIN = 6;
const int CS_PIN = 5;
const int CLK_PIN = 4;

LedControl display = LedControl(DIN_PIN, CLK_PIN, CS_PIN);
byte frames[][8] = {
  { B00000000,
    B00000000,
    B00000000,
    B00011000,
    B00011000,
    B00000000,
    B00000000,
    B00000000 },
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000 },
  { B00000000,
    B00000000,
    B00111100,
    B00100100,
    B00100100,
    B00111100,
    B00000000,
    B00000000 },
  { B00000000,
    B01111110,
    B01000010,
    B01000010,
    B01000010,
    B01000010,
    B01111110,
    B00000000 },
  { B11111111,
    B10000001,
    B10000001,
    B10000001,
    B10000001,
    B10000001,
    B10000001,
    B11111111 },
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000 },
};

void animate() {
  for (int i = 0; i <= 4; i += 2) {
    for (int j = 0; j < 8; j++) {
      display.setRow(0, j, frames[i][j]);
      display.setRow(1, j, frames[i + 1][j]);
    }
    delay(100);
  }
  display.clearDisplay(0);
}


void setup() {
  // matrix
  display.clearDisplay(0);
  display.shutdown(0, false);
  display.setIntensity(0, 10);

  Serial.begin(9600);

  // radio
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);
    if (strcmp(text, "flame") == 0) {
     animate();
    } else {
    }
  }
}
