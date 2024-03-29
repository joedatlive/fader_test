#include <ADC.h>
// this code is not on github  https://github.com/joedatlive/fader_test.git
ADC *adc = new ADC();  //adc object
int LedPin = 23;
int MidiCC = 7; // set the midi Control Change to common volume setting
int MidiChannel = 1; //User midi channel 1
int FaderPotDataOld = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(LedPin, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  int FaderPotData = getAnalogData(A0); //this is the 10bit value from Fader after analogue to digital conversion.

  // lets check to see if the data changed, plus or minus 8
  // we want to avoid "jitter" and we will lose this level of granuliaty when we convert to 7 bits
  if (FaderPotDataOld > (FaderPotData + 8) or FaderPotDataOld < (FaderPotData - 8)){
    int FaderMidiData = bitShift(FaderPotData, 3, true); //This will variable hold the 7bit mapping value to send to midi
    while (usbMIDI.read()) {}  // controllers must call .read() to keep the queue clear even if they are not responding to MIDI
    usbMIDI.sendControlChange(MidiCC, FaderMidiData, MidiChannel);
    FaderPotDataOld = FaderPotData;
  }
  blinkLight(10, 10);
}

int getAnalogData(int port) {
// Read the value from the fader potentiomenter 
  int FaderPot = adc->analogRead(port); //Analog digital converter to read voltage coming from vader variable resistor. A0 mapps to pin 14 and is on ADC0_SE5b
  return FaderPot;
}

int bitShift(int InputBits, int ShiftCount, bool isRightShift){
  // Bit shift to the right or left by Shift value to convert for example a 10 bit signal to a 7 bit signal
  // The ADC gives a 10 bit value and midi takes a 7 bit value
  if (isRightShift) {
    //Right shift which is dividing by 2 raised to the power of the ShiftCount by deleting the right most bits
    return InputBits >> ShiftCount;
  } else {
    //Left shift which is multiplying by 2 raised to the power of the Shift Count by deleting the left most bits
    return InputBits << ShiftCount;
  }
}

// function to blink the led
void blinkLight(int wait1, int wait2) {
   analogWrite(LedPin, 255);   // turn the LED on (using Pulse Width Modulation to change intesity) to signal when volts are being read (testing)
   delay(wait1);               // wait for a second
   analogWrite(LedPin, 0);   // turn the LED off (using Pulse Width Modulation to change intesity)
   delay(wait2);               // wait for sometime
}
