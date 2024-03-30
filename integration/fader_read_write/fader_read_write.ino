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
  //iniitalize midi for reading CC
  usbMIDI.setHandleControlChange(onControlChange);
}

// the loop routine runs over and over again forever:
void loop() {
  //*******Slider to Teensy to MIDI to DAW********
  //read analog port voltage to see if slider moved
  int FaderPotData10 = adc->analogRead(A0); //Analog digital converter to read voltage coming from vader variable resistor. A0 mapps to pin 14 and is on ADC0_SE5b
  //check if data changed enough and bit shift form 10bits to 7 if it did
  if (FaderPotDataOld > (FaderPotData10 + 8) or FaderPotDataOld < (FaderPotData10 - 8)){
    int FaderPotData7 = bitShift(FaderPotData10, 3, true); //This will variable hold the 7bit mapping value to send to midi
    //write the Pot data to midi
    usbMIDI.sendControlChange(MidiCC, FaderPotData7, MidiChannel); //write the data to the Midi Channel
    FaderPotDataOld = FaderPotData10; //reset the current setting to the Old setting to see if it changes in the future
  }
  //*******DAW to MIDO to Teensy to slider********
  //read midi data to see if DAW changed fader
  while(usbMIDI.read()){} //read midi channel for updates on Control Change and do something
  delay(10);
}

void onControlChange(uint8_t channel, uint8_t control, uint8_t value){
  if(control == MidiCC){
     blinkLight(1000,500);
     //convert the Midi 7 bit to 10 bits
     int FaderMidiData10 = bitShift(value, 3, false); //This will variable hold the 10 bit mapping of the midi value to compare to the fader analog setting
     //until slider is within 8 bits of value
     int FaderPotData10 = adc->analogRead(A0); 
     while (FaderMidiData10 < (FaderPotData10 - 8)) {
      //move the slider down 8 bits
      FaderPotData10 = FaderPotData10 - 8; //this will get replaced with a function to move the motor
      blinkLight(1000,500);
      //FaderPotData10 = adc->analogRead(A0); will need this once we can actually move the motor
     }
     while (FaderMidiData10 > (FaderPotData10 - 8)) {
      //move the slider up 8 bits
       FaderPotData10 = FaderPotData10 + 8; //this will get replaced with a function to move the motor
      blinkLight(1000,500);
      //int FaderPotData10 = adc->analogRead(A0); will need this once we can actually move the motor
     }
   }
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
