// /*
//  * GP2Y0A21YK sensor (10cm - 80cm)
//  * Opponent detection sensor with medium range.
//  * More accurate in short range, but drops off above 80cm.
//  *
//  * Ports:
//  * Sensor VCC (red) to Arduino 5V
//  * Sensor GND (black) to Arduino GND
//  * Sensor Output Voltage (yellow) to Arduino A1 (Analog In)
//  */

// const int midRangePin = A1;

// void loop() {
//   int result = getMidRangeRawValue();
// }
// void midRangeSetup() {}

// void midRangeTest(int rawValue) {
//   Serial.print("Raw:");
//   Serial.print(rawValue);
//   Serial.println("  ");
// }

// int getMidRangeRawValue() {
//   return analogRead(midRangePin);
// }

// bool isOpponent2() {
//   count = 0;
//   result = 0;
//   while (count < 10) {
//     result += getRawValue();
//     count++;
//   }

//   if ((result/10)> 75) return true;
// }
