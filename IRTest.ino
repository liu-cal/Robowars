/*
 * IR sensors or Line sensors
 * We will be working with the Digital Output for simplicity. A0 will be left unused
 *
 * Ports:
 * Sensor VCC to Arduino 5V
 * Sensor GND to Arduino GND
 * Sensor D0 to Arduino D2, D3, D4, D5
 *
 * IMPORTANT TO LEAVE A0 UNCONNECTED
 */

// Constants ---
const int IRSleepTime = 2200;

void IRsetup() {
  pinMode(FRONT_LEFT, INPUT);
  pinMode(FRONT_RIGHT, INPUT);
  pinMode(BACK_LEFT, INPUT);
  pinMode(BACK_RIGHT, INPUT);

  // pinMode(leftMotorPWM, OUTPUT);
  // pinMode(rightMotorPWM, OUTPUT);
  // pinMode(leftMotorDir, OUTPUT);
  // pinMode(rightMotorDir, OUTPUT);

  Serial.begin(9600);
  Serial1.begin(9600);

  // let the IR adjust before sending data
  delay(IRSleepTime);
}

bool isWhiteLine(int pin) {
  return (digitalRead(pin) == LOW);
}