void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly
  usbMIDI.sendControlChange(7, 127, 1);
  blinkLight(1000, 2000);
  usbMIDI.sendControlChange(7, 112, 1);
  blinkLight(1000, 2000);
  usbMIDI.sendControlChange(7, 96, 1);
  blinkLight(1000, 2000);
  usbMIDI.sendControlChange(7, 80, 1);
  blinkLight(1000, 2000);
  usbMIDI.sendControlChange(7, 64, 1);
  blinkLight(1000, 2000);
  usbMIDI.sendControlChange(7, 48, 1);
  blinkLight(1000, 2000);
  usbMIDI.sendControlChange(7, 32, 1);
  blinkLight(1000, 2000);
  usbMIDI.sendControlChange(7, 16, 1);
  blinkLight(1000, 2000);
  usbMIDI.sendControlChange(7, 0, 1);
}

void blinkLight(int wait1, int wait2) {
   analogWrite(23, 255);   // turn the LED on (using Pulse Width Modulation to change intesity) to signal when volts are being read (testing)
   delay(wait1);               // wait for a second
   analogWrite(23, 0);   // turn the LED off (using Pulse Width Modulation to change intesity)
   delay(wait2);               // wait for sometime
}
