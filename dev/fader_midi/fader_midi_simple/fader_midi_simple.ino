void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  usbMIDI.sendControlChange(7, 100, 1);
  blinkLight(200);
  usbMIDI.sendControlChange(7, 50, 1);
}

void blinkLight(int wait) {
   analogWrite(23, 255);   // turn the LED on (using Pulse Width Modulation to change intesity) to signal when volts are being read (testing)
   delay(1000);               // wait for a second
   analogWrite(23, 0);   // turn the LED off (using Pulse Width Modulation to change intesity)
   delay(wait);               // wait for sometime
}
