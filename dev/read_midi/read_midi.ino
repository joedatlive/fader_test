int LedPin = 23;
int MidiCC = 7; // set the midi Control Change to common volume setting
int MidiChannel = 1; //User midi channel 1

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(LedPin, OUTPUT);
  //iniitalize midi for reading CC
   usbMIDI.setHandleControlChange(onControlChange);
}

// the loop routine runs over and over again forever:
void loop() {
  while(usbMIDI.read()){} //read midi channel for updates
  delay(10);
}

void onControlChange(uint8_t channel, uint8_t control, uint8_t value){
  if(control == MidiCC){
   blinkLight(1000,500);
  }
}

// function to blink the led
void blinkLight(int wait1, int wait2) {
   analogWrite(LedPin, 255);   // turn the LED on (using Pulse Width Modulation to change intesity) to signal when volts are being read (testing)
   delay(wait1);               // wait for a second
   analogWrite(LedPin, 0);   // turn the LED off (using Pulse Width Modulation to change intesity)
   delay(wait2);               // wait for sometime
}
