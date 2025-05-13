/*
 * IR sensors or Line sensors
 * We will be working with the Digital Output for simplicity. A0 will be left unused
 *
 * Ports:
 * Sensor VCC to Arduino 5V
 * Sensor GND to Arduino GND
 * Sensor D0 to Arduino D2
 *
 * IMPORTANT TO NOT CONNECT A0
 */

#define IR_PIN 2

// Constants ---
const int IRSleepTime = 2200;

void IRsetup() {
  pinMode(IR_PIN, INPUT);
  Serial.begin(9600);

  // let the IR adjust before sending data
  delay(IRSleepTime);
}

bool isWhiteLine() {
  int sensorValue = digitalRead(IR_PIN);
  return (sensorValue == LOW) ? true : false;
}