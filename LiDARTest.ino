#include <SoftwareSerial.h>

// Create a software serial port on D10 (RX) and D11 (TX)
SoftwareSerial lidarSerial(10, 11);  // RX, TX

void setup() {
  Serial.begin(9600);          // Serial Monitor
  lidarSerial.begin(115200);   // LiDAR's UART baud rate

  Serial.println("STL-19P LiDAR Test Starting...");
}

void loop() {
  int distance = readLidar();
  if (distance > 0) {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(100);  // Optional: reduce CPU usage
}

int readLidar() {
  if (lidarSerial.available() >= 9) {
    byte header = lidarSerial.read();
    if (header == 0x59) {
      byte nextByte = lidarSerial.read();
      if (nextByte == 0x59) {
        byte data[7];
        lidarSerial.readBytes(data, 7);
        int distance = data[1] << 8 | data[0];
        return distance;
      }
    }
  }
  return -1; // No valid data
}
