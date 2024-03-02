/*
  Fader test code
  A project testing reading and setting a fader controller
 */

#include <ADC.h>
// this code is not on github  https://github.com/joedatlive/fader_test.git
//Yay!!!
ADC *adc = new ADC();  //adc object
int iLed = 23;
float fFaderVolts = 0.0; 

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(iLed, OUTPUT);
  // Set up serial interface to see output in Serial monitor in IDE
  Serial.begin(9600); // USB is always 12 or 480 Mbit/sec
}


// the loop routine runs over and over again forever:
void loop() {
  analogWrite(iLed, 255);   // turn the LED on (using Pulse Width Modulation to change intesity) to signal when volts are being read (testing)
  fFaderVolts = adc->analogRead(A0); //Analog digital converter to read voltage coming from vader variable resistor. A0 mapps to pin 14 and is on ADC0_SE5b
  Serial.println(fFaderVolts); //write volts to terminal
  delay(500);               // wait for a second
  analogWrite(iLed, 0);   // turn the LED off (using Pulse Width Modulation to change intesity)
  delay(2000);               // wait for a second
}
