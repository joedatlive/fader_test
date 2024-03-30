// Define motor driver pin connections (adjust based on your wiring)
const int AIN1 = 3;
const int AIN2 = 4;
const int PWMA = 5; // PWM pin for motor A speed control
const int LedPin = 23;
int motorSpeed = 128; // Motor speed (0-255)

void setup() {
  // Set motor driver pins as output
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(LedPin, OUTPUT);

  // Set initial motor state (stopped)
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, 0); // Set initial PWM to 0 (motor stopped)
}
void loop() {
  // put your main code here, to run repeatedly:
  // Set motor direction (forward in this example)
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);

  // Control motor speed using PWM
  analogWrite(PWMA, motorSpeed);

  // Update motor speed based on external control (e.g., user input)
  // ... (replace with your logic for changing motorSpeed)

  //delay(10); // Delay between updates (adjust as needed)
  blinkLight(1000, 200);
}

// function to blink the led
void blinkLight(int wait1, int wait2) {
   analogWrite(LedPin, 255);   // turn the LED on (using Pulse Width Modulation to change intesity) to signal when volts are being read (testing)
   delay(wait1);               // wait for a second
   analogWrite(LedPin, 0);   // turn the LED off (using Pulse Width Modulation to change intesity)
   delay(wait2);               // wait for sometime
}
