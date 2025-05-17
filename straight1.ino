/*
 * GP2Y0A02YK sensor (20cm - 150cm)
 * Main sensor to search for the opponent. 
 * Wide range, less accurate and falls off under 20cm
 *
 * Ports:
 * Sensor VCC (red) to Arduino 5V
 * Sensor GND (black) to Arduino GND
 * Sensor Output Voltage (yellow) to Arduino A0 (Analog In)
 *
 */


const int straightLine1Pin = A0;

void straightLine1setup() {}

void test(int rawValue, String range) {
  Serial.print("Raw:");
  Serial.print(rawValue);
  Serial.print("  ");
  Serial.print(range);
  Serial.println();
}

int getRawValue() {
  return analogRead(straightLine1Pin);
}

// String getDistanceApprox(int input) {
//   if (input > 500) return "under 20";
//   else if (input > 370) return "under 30"; // increments by 15
//   else if (input > 250) return "under 45";
//   else if (input > 195) return "under 60";
//   else if (input > 150) return "under 75";
//   else if (input > 120) return "under 90";
//   else if (input > 100) return "under 105";
//   else if (input > 90) return "under 120";
//   else if (input > 80) return "under 135";
//   else if (input > 65) return "around 150";
//   else return "nothing";
// }

bool isOpponent1() {
  int count = 0;
  int result = 0;
  while (count < 5) {
    result += getRawValue();
    count++;
  }

  if ((result/5)> 70) return true;
}