/******************************
   FADER-8 V1
   for Teensy 3.2 (www.pjrc.com)
   joed@live.com
 ******************************/

/**************************************
   ** Upload Settings **
   Board: "Teensy 3.2"
   USB Type: "MIDI"
 **************************************/
// #include <ADC.h>
// include the ResponsiveAnalogRead library for analog smoothing
#include <ResponsiveAnalogRead.h> //lets go back to analog read

// customize program variables
const int channel = 1; // MIDI channel
const int A_PINS = 1; // number of Analog PINS
//const int ON_VELOCITY = 99; // note-one velocity sent from buttons (should be 65 to  127)
int iLed = 23;

// define the analog pins to use
const int FADER_PINS[A_PINS] = {A0};
// define the CCID number to send fader input to midi
const int CCID[A_PINS] = {1};
//The standard and most common ones are 1 mod, 2 breath, 7 volume, and 11 expression.

// create a data array and a old copy to tell when MIDI changes are required
byte data[A_PINS];
byte dataOld[A_PINS]; // when lag and new are not the same then update MIDI CC value

// initialize the ReponsiveAnalogRead objects
ResponsiveAnalogRead analog[]{
  {FADER_PINS[0],true},
}; 

// ************Setup*************
void setup() {}

// ************LOOP**************
void loop() {
  getAnalogData();
  while (usbMIDI.read()) {
     // controllers must call .read() to keep the queue clear even if they are not responding to MIDI
  }
}

void getAnalogData(){  
  for (int i=0;i<A_PINS;i++){
   // update the ResponsiveAnalogRead object every loop
    analog[i].update(); 
    // if the repsonse value has change, sebd to midi cc
    if(analog[i].hasChanged()) {
      blinkLight(2000);
      data[i] = analog[i].getValue()>>3;
      if (data[i] != dataOld[i]){
        blinkLight(200);
        dataOld[i] = data[i];
        usbMIDI.sendControlChange(CCID[i], data[i], channel);
      }
    }
  }
}

void blinkLight(int wait) {
   analogWrite(iLed, 255);   // turn the LED on (using Pulse Width Modulation to change intesity) to signal when volts are being read (testing)
   delay(500);               // wait for a second
   analogWrite(iLed, 0);   // turn the LED off (using Pulse Width Modulation to change intesity)
   delay(wait);               // wait for a second
}
