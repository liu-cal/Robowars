// --- Pin Definitions ---
const int startPin = 2;   // JSUMO start signal pin
const int lidarRx = 10;   // RX pin from LiDAR (TX of sensor)
const int lidarTx = 11;   // TX pin to LiDAR (RX of sensor)
const int linePins[4] = {A0, A1, A2, A3};  // TCRT5000 sensors (front-left, front-right, rear-left, rear-right)
// Motor pins (example)
const int leftMotorPWM = 5;
const int rightMotorPWM = 6;
const int leftMotorDir = 7;
const int rightMotorDir = 8;

bool robotActive = false;

void setup() {
  Serial.begin(115200);  // for LiDAR
  pinMode(startPin, INPUT);

  for (int i = 0; i < 4; i++) pinMode(linePins[i], INPUT);

  pinMode(leftMotorPWM, OUTPUT);
  pinMode(rightMotorPWM, OUTPUT);
  pinMode(leftMotorDir, OUTPUT);
  pinMode(rightMotorDir, OUTPUT);

  stopMotors();  // ensure safe startup
}

void loop() {
  if (!robotActive) {
    if (digitalRead(startPin) == HIGH) {
      robotActive = true;
      delay(1000);  // Optional startup delay
    } else {
      stopMotors();
      return;
    }
  }

  // --- Line Sensor Check ---
  bool nearEdge = false;
  for (int i = 0; i < 4; i++) {
    if (digitalRead(linePins[i]) == HIGH) { // white detected
      nearEdge = true;
      break;
    }
  }

  if (nearEdge) {
    reverseAndTurn();
    return;
  }

  // --- LiDAR Tracking Logic ---
  int distance = readLidar();  // returns distance in cm

  if (distance > 0 && distance < 100) {
    moveForward();
  } else {
    spinSearch();  // rotate to find opponent
  }
}

// --- Helper Functions ---
void stopMotors() {
  analogWrite(leftMotorPWM, 0);
  analogWrite(rightMotorPWM, 0);
}

void moveForward() {
  digitalWrite(leftMotorDir, HIGH);
  digitalWrite(rightMotorDir, HIGH);
  analogWrite(leftMotorPWM, 180);
  analogWrite(rightMotorPWM, 180);
}

void reverseAndTurn() {
  // Back up and turn
  digitalWrite(leftMotorDir, LOW);
  digitalWrite(rightMotorDir, LOW);
  analogWrite(leftMotorPWM, 180);
  analogWrite(rightMotorPWM, 180);
  delay(400);

  // Rotate in place
  digitalWrite(leftMotorDir, HIGH);
  digitalWrite(rightMotorDir, LOW);
  delay(300);
}

void spinSearch() {
  digitalWrite(leftMotorDir, HIGH);
  digitalWrite(rightMotorDir, LOW);
  analogWrite(leftMotorPWM, 150);
  analogWrite(rightMotorPWM, 150);
}

// Example: read distance from STL-19P via UART
int readLidar() {
  if (Serial.available() >= 9) {
    byte header = Serial.read();
    if (header == 0x59) {
      byte nextByte = Serial.read();
      if (nextByte == 0x59) {
        byte data[7];
        Serial.readBytes(data, 7);
        int distance = data[1] << 8 | data[0];
        return distance;
      }
    }
  }
  return -1; // no valid reading
}


#define LINE_CHECK_INTERVAL 100
#define FRONT_LEFT 2
#define FRONT_RIGHT 3
#define BACK_LEFT 4
#define BACK_RIGHT 5

void setup() {
  IRsetup();
}

void loop() {
  // TODO make it turn according to which sensor triggered
  if (isWhiteLine(FRONT_LEFT)) {
    Serial.println("White line detected: FRONT_LEFT");
  }
  else if (isWhiteLine(FRONT_RIGHT)) {
    Serial.println("White line detected: FRONT_RIGHT");
  }
  else if (isWhiteLine(BACK_LEFT)) {
    Serial.println("White line detected: BACK_LEFT");
  }
  else if (isWhiteLine(BACK_RIGHT)) {
    Serial.println("White line detected: BACK_RIGHT");
  }
  else {
    Serial.println("All sensors on black");
  }

  delay(LINE_CHECK_INTERVAL);
}
