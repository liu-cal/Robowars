const int linePins[4] = {A0, A1, A2, A3};  // Adjust if your pins differ

void setup() {
  Serial.begin(9600);  // Open Serial Monitor at 9600 baud
  for (int i = 0; i < 4; i++) {
    pinMode(linePins[i], INPUT);
  }
  Serial.println("Line sensor test started...");
}

void loop() {
  Serial.print("Line sensors: ");
  for (int i = 0; i < 4; i++) {
    int sensorValue = digitalRead(linePins[i]);
    if (sensorValue == HIGH) {
      Serial.print("W ");  // White surface detected
    } else {
      Serial.print("B ");  // Black surface detected
    }
  }
  Serial.println();
  delay(300);  // Refresh every 300 ms
}
