#include <Control_Surface.h>
//getting started docs: https://tttapa.github.io/Control-Surface-doc/Doxygen/d5/d7d/md_pages_Getting-Started.html

USBMIDI_Interface midi;
CCPotentiometer pot { A0, MIDI_CC::General_Purpose_Controller_1 };

void setup() { 
  Control_Surface.begin();
}
void loop() {
  Control_Surface.loop();
  blinkLight(2000);
}

void blinkLight(int wait) {
   analogWrite(23, 255);   // turn the LED on (using Pulse Width Modulation to change intesity) to signal when volts are being read (testing)
   delay(500);               // wait for a second
   analogWrite(23, 0);   // turn the LED off (using Pulse Width Modulation to change intesity)
   delay(wait);               // wait for a second
}
