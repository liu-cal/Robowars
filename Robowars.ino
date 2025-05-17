// --- Pin Definitions ---
const int startPin = 2;   // JSUMO start signal pin
//const int linePins[4] = {A0, A1, A2, A3};  // TCRT5000 sensors (front-left, front-right, rear-left, rear-right)
// Motor pins (example)
const int leftMotorPWM = 9;
const int rightMotorPWM = 10;
const int leftMotorDir = 11;
const int rightMotorDir = 12;

#define LINE_CHECK_INTERVAL 700
#define FRONT_LEFT 5
#define FRONT_RIGHT 6
#define BACK_LEFT 7
#define BACK_RIGHT 8

bool robotActive = false;
bool opponentFound = false;

const int IRSleepTime = 2200;

void IRsetup() {
  pinMode(FRONT_LEFT, INPUT);
  pinMode(FRONT_RIGHT, INPUT);
  pinMode(BACK_LEFT, INPUT);
  pinMode(BACK_RIGHT, INPUT);

  // let the IR adjust before sending data
  delay(IRSleepTime);
}

bool isWhiteLine(int pin) {
  return (digitalRead(pin) == LOW);
}

void setup() {
  Serial.begin(9600);
  IRsetup();
  pinMode(startPin, INPUT);

  pinMode(leftMotorPWM, OUTPUT);
  pinMode(rightMotorPWM, OUTPUT);
  pinMode(leftMotorDir, OUTPUT);
  pinMode(rightMotorDir, OUTPUT);

  stopMotors();  // ensure safe startup
}

// --- Helper Functions ---
void stopMotors() {
  analogWrite(leftMotorPWM, 0);
  analogWrite(rightMotorPWM, 0);
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
  // TODO make it turn according to which sensor triggered

  if (!opponentFound) {
  Serial.println("Spinning to search for opponent...");
  spinSearch();

  if (isOpponent1()) {
    Serial.println("Opponent detected by main sensor!");
    opponentFound = true;
    stopMotors();

    // Check left sensor for 3 seconds
    bool leftSeen = false;
    unsigned long checkStart = millis();
    while (millis() - checkStart < 3000) {
      if (isOpponent2()) {
        leftSeen = true;
        Serial.println("Opponent detected on the left side.");
        break;
      }
      delay(100); // Polling interval
    }

    if (!leftSeen) {
      Serial.println("No opponent on left, turning right...");
      digitalWrite(leftMotorDir, HIGH);
      digitalWrite(rightMotorDir, LOW);
      analogWrite(leftMotorPWM, 150);
      analogWrite(rightMotorPWM, 150);
      delay(5000); // Adjust time to your turning speed
      stopMotors();
    }
  } else {
    // Keep spinning
    return;
  }
  
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
}
