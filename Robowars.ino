// --- Pin Definitions ---
const int startPin = 2;   // JSUMO start signal pin
//const int linePins[4] = {A0, A1, A2, A3};  // TCRT5000 sensors (front-left, front-right, rear-left, rear-right)
// Motor pins (example)
const int leftMotorPWM = 9;
const int rightMotorPWM = 10;
const int leftMotorDir = 11;
const int rightMotorDir = 12;

bool robotActive = false;

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


#define LINE_CHECK_INTERVAL 700
#define FRONT_LEFT 5
#define FRONT_RIGHT 6
#define BACK_LEFT 7
#define BACK_RIGHT 8

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

  int val1 = getRawValue();
  String range1 = getDistanceApprox(val1);
  test(val1, range1);

  int val2 = getMidRangeRawValue();
  String range2 = getMidRangeDistanceApprox(val2);
  midRangeTest(val2, range2);
  
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
