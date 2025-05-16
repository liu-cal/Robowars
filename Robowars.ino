// // --- Pin Definitions ---
// const int startPin = 2;   // JSUMO start signal pin
// const int lidarRx = 10;   // RX pin from LiDAR (TX of sensor)
// const int lidarTx = 11;   // TX pin to LiDAR (RX of sensor)
// const int linePins[4] = {A0, A1, A2, A3};  // TCRT5000 sensors (front-left, front-right, rear-left, rear-right)
// //peepeepoopoo
// // Motor pins (example)
// const int leftMotorPWM = 5;
// const int rightMotorPWM = 6;
// const int leftMotorDir = 7;
// const int rightMotorDir = 8;

// bool robotActive = false;

// void setup() {
//   Serial.begin(115200);  // for LiDAR
//   pinMode(startPin, INPUT);

//   for (int i = 0; i < 4; i++) pinMode(linePins[i], INPUT);

//   pinMode(leftMotorPWM, OUTPUT);
//   pinMode(rightMotorPWM, OUTPUT);
//   pinMode(leftMotorDir, OUTPUT);
//   pinMode(rightMotorDir, OUTPUT);

//   stopMotors();  // ensure safe startup
// }

// void loop() {
//   if (!robotActive) {
//     if (digitalRead(startPin) == HIGH) {
//       robotActive = true;
//       delay(1000);  // Optional startup delay
//     } else {
//       stopMotors();
//       return;
//     }
//   }

//   // --- Line Sensor Check ---
//   bool nearEdge = false;
//   for (int i = 0; i < 4; i++) {
//     if (digitalRead(linePins[i]) == HIGH) { // white detected
//       nearEdge = true;
//       break;
//     }
//   }

//   if (nearEdge) {
//     reverseAndTurn();
//     return;
//   }

//   // --- LiDAR Tracking Logic ---
//   int distance = readLidar();  // returns distance in cm

//   if (distance > 0 && distance < 100) {
//     moveForward();
//   } else {
//     spinSearch();  // rotate to find opponent
//   }
// }

// // --- Helper Functions ---
// void stopMotors() {
//   analogWrite(leftMotorPWM, 0);
//   analogWrite(rightMotorPWM, 0);
// }

// void moveForward() {
//   digitalWrite(leftMotorDir, HIGH);
//   digitalWrite(rightMotorDir, HIGH);
//   analogWrite(leftMotorPWM, 180);
//   analogWrite(rightMotorPWM, 180);
// }

// void reverseAndTurn() {
//   // Back up and turn
//   digitalWrite(leftMotorDir, LOW);
//   digitalWrite(rightMotorDir, LOW);
//   analogWrite(leftMotorPWM, 180);
//   analogWrite(rightMotorPWM, 180);
//   delay(400);

//   // Rotate in place
//   digitalWrite(leftMotorDir, HIGH);
//   digitalWrite(rightMotorDir, LOW);
//   delay(300);
// }

// void spinSearch() {
//   digitalWrite(leftMotorDir, HIGH);
//   digitalWrite(rightMotorDir, LOW);
//   analogWrite(leftMotorPWM, 150);
//   analogWrite(rightMotorPWM, 150);
// }

// Example: read distance from STL-19P via UART

#include <AltSoftSerial.h>
AltSoftSerial Serial1; // RX = pin 8


#define LINE_CHECK_INTERVAL 700
#define FRONT_LEFT 2
#define FRONT_RIGHT 3
#define BACK_LEFT 4
#define BACK_RIGHT 7

// Motor pins (example)
const int leftMotorPWM = 5;
const int rightMotorPWM = 6;
const int leftMotorDir = 7;
const int rightMotorDir = 8;

void setup() {
  IRsetup();
}

// int readLidar() {
//   Serial.print("Available bytes: ");
//   Serial.println(Serial1.available());  
  
//   if (Serial1.available() >= 9) {


//     byte frame[79];
//     Serial1.readBytes(frame, 79);  // Read all 9 bytes into frame

//     Serial.print("Full frame: ");
//     for (int i = 0; i < 79; i++) {
//       if (frame[i] < 0x10) Serial.print("0"); // zero padding
//       Serial.print(frame[i], HEX);
//       Serial.print(" ");
//     }
//     Serial.println();


//     byte header = Serial1.read();
//     Serial.print("Header byte: ");
//     Serial.println(header, HEX);
//     if (header == 0x59) {
//       byte nextByte = Serial1.read();
//       if (nextByte == 0x59) {
//         byte data[7];
//         Serial1.readBytes(data, 7);
//         int distance = data[1] << 8 | data[0];
//         return distance;
//       }
//     }
//   }
//   return -1; // no valid reading
// }

// int readLidar() {
//   // Wait for complete frame (9 bytes)
//   if (Serial1.available() >= 9) {
//     byte frame[9];
//     Serial1.readBytes(frame, 9);  // Read all 9 bytes
    
//     // Debug print
//     Serial.print("Full frame: ");
//     for (int i = 0; i < 9; i++) {
//       if (frame[i] < 0x10) Serial.print("0"); // zero padding
//       Serial.print(frame[i], HEX);
//       Serial.print(" ");
//     }
//     Serial.println();

//     // Check header
//     if (frame[0] == 0xAA && frame[1] == 0xAA) {
//       // Calculate checksum (sum of bytes 0-7)
//       byte checksum = 0;
//       for (int i = 0; i < 8; i++) {
//         checksum += frame[i];
//       }
      
//       // Verify checksum
//       if (checksum == frame[8]) {
//         // Combine distance bytes (little-endian)
//         int distance = frame[3] << 8 | frame[2];
//         return distance;
//       } else {
//         Serial.println("Checksum error");
//       }
//     } else {
//       Serial.println("Header mismatch");
//     }
//   }
//   return -1; // no valid reading
// }

void loop() {
  // TODO make it turn according to which sensor triggered
  
  if(isWhiteLine(FRONT_LEFT)&&isWhiteLine(FRONT_RIGHT)){
    Serial.println("White line detected: FRONT_LEFT AND FRONT_RIGHT");
    
    //customizable depending on motor force
    digitalWrite(leftMotorDir, LOW);
    digitalWrite(rightMotorDir, LOW);
    analogWrite(leftMotorPWM, 180);
    analogWrite(rightMotorPWM, 180);
    delay(400);

    digitalWrite(leftMotorDir, HIGH);
    digitalWrite(rightMotorDir, LOW);
    delay(300);
  }
  else if(isWhiteLine(FRONT_LEFT) && isWhiteLine(BACK_LEFT)){
    Serial.println("White line detected: FRONT_LEFT AND BACK_LEFT");

    //customizable depending on motor force
    digitalWrite(leftMotorDir, HIGH);
    digitalWrite(rightMotorDir, HIGH);
    analogWrite(leftMotorPWM, 180);
    analogWrite(rightMotorPWM, 60);
    delay(400);

    analogWrite(rightMotorPWM, 180);
    delay(300);
  }
  else if(isWhiteLine(BACK_RIGHT) && isWhiteLine(BACK_LEFT)){
    Serial.println("White line detected: BACK_LEFT AND BACK_RIGHT");

    //customizable depending on motor force
    digitalWrite(leftMotorDir, HIGH);
    digitalWrite(rightMotorDir, HIGH);
    analogWrite(leftMotorPWM, 180);
    analogWrite(rightMotorPWM, 180);
    delay(700);
  }
  else if(isWhiteLine(FRONT_RIGHT)&& isWhiteLine(BACK_RIGHT)){
    Serial.println("White line detected: FRONT_RIGHT AND BACK_RIGHT");

    //customizable depending on motor force
    digitalWrite(leftMotorDir, HIGH);
    digitalWrite(rightMotorDir, HIGH);
    analogWrite(leftMotorPWM, 60);
    analogWrite(rightMotorPWM, 180);
    delay(400);

    analogWrite(leftMotorPWM, 180);
    delay(300);
  }
  else if (isWhiteLine(FRONT_LEFT)) {
    Serial.println("White line detected: FRONT_LEFT");

    //customizable depending on motor force
    digitalWrite(leftMotorDir, HIGH);
    digitalWrite(rightMotorDir, HIGH);
    analogWrite(leftMotorPWM, 180);
    analogWrite(rightMotorPWM, 60);
    delay(400);

    analogWrite(rightMotorPWM, 180);
    delay(300);
  }
  else if (isWhiteLine(FRONT_RIGHT)) {
    Serial.println("White line detected: FRONT_RIGHT");

    //customizable depending on motor force
    digitalWrite(leftMotorDir, HIGH);
    digitalWrite(rightMotorDir, HIGH);
    analogWrite(leftMotorPWM, 60);
    analogWrite(rightMotorPWM, 180);
    delay(400);

    analogWrite(leftMotorPWM, 180);
    delay(300);
  }
  else if (isWhiteLine(BACK_LEFT)) {
    Serial.println("White line detected: BACK_LEFT");

    //customizable depending on motor force
    digitalWrite(leftMotorDir, HIGH);
    digitalWrite(rightMotorDir, HIGH);
    analogWrite(leftMotorPWM, 180);
    analogWrite(rightMotorPWM, 60);
    delay(400);

    analogWrite(rightMotorPWM, 180);
    delay(300);
  }
  else if (isWhiteLine(BACK_RIGHT)) {
    Serial.println("White line detected: BACK_RIGHT");

    //customizable depending on motor force
    digitalWrite(leftMotorDir, HIGH);
    digitalWrite(rightMotorDir, HIGH);
    analogWrite(leftMotorPWM, 60);
    analogWrite(rightMotorPWM, 180);
    delay(400);

    analogWrite(leftMotorPWM, 180);
    delay(300);
  }
  else {
    Serial.println("All sensors on black or on white");
  }

  delay(LINE_CHECK_INTERVAL);

  int distance = readLidar();  // returns distance in cm

  Serial.println(distance);
}
