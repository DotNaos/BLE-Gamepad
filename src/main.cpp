/*
@Title BLE keyboard, arcade button to phone
@Author Geert Roumen
@Institute Umeå Institute of Design
@Date 29-01-2020

@Hardware

Any ESP32 dev board would do, but I used the:
Geekworm EASY KIT ESP32-C1
https://geekworm.com/products/official-geekworm-esp32-development-board

Arcade button
Adafruit Large Arcade button white
https://www.adafruit.com/product/1192

D13       Button pin
3.3V      Connected to the other leg of the button

In this example sketch one single button will send a spacebar when being pressed.
*/
#include <Arduino.h>
#include <BleKeyboard.h>
// Se the name of the bluetooth keyboard (that shows up in the bluetooth menu of your device)
BleKeyboard bleKeyboard("Orions Connect");



const byte buttonPin = 13;

const byte joyY = 26;
const byte joyX = 25;

void JoyButtonPressed() {
  bleKeyboard.print(" ");
  // Serial.println("Spacebar");
}

int x = 0;
int y = 0;

void setup()
{
 

  Serial.begin(115200);
  Serial.println("Starting Device");

  Serial.println(analogRead(joyX));
  Serial.println(analogRead(joyY));
  // Begin BLE keyboard/start advertising 
  bleKeyboard.begin();                                                                                 

  pinMode(buttonPin, INPUT_PULLUP);
  // Make a interupt 
  attachInterrupt(digitalPinToInterrupt(buttonPin), JoyButtonPressed, RISING);
}
                                                    
void loop()
{
  // Read the joystick values
  x = analogRead(joyX);
  y = analogRead(joyY);

  // Print the joystick values
  Serial.print("X: ");
  Serial.println(x);
  Serial.print("Y: ");
  Serial.println(y);

  




  // Simulate a keyboard if the joystick value is above a certain value
  if (x > 4000) {
    bleKeyboard.print("s");
    // Serial.println("s");
  }    
  else if (x < 1000) {
    bleKeyboard.print("w");
    // Serial.println("w");
  }

  if (y > 4000) {
    bleKeyboard.print("d");
    // Serial.println("d");
  }
  else if (y < 1000) {
    bleKeyboard.print("a");
    // Serial.println("a");
  }          

  

  // Delay to prevent the keyboard from spamming
  delay(100);



               


}



