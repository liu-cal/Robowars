#define BRAKE 0
#define CW    1
#define CCW   2
#define CS_THRESHOLD 15   // Definition of safety current (Check: "1.3 Monster Shield Example").

//MOTOR 1
#define MOTOR_A1_PIN 7
#define MOTOR_B1_PIN 8

//MOTOR 2
#define MOTOR_A2_PIN 4
#define MOTOR_B2_PIN 9

#define PWM_MOTOR_1 5
#define PWM_MOTOR_2 6

#define CURRENT_SEN_1 A2
#define CURRENT_SEN_2 A3

#define EN_PIN_1 A0
#define EN_PIN_2 A1

#define MOTOR_1 0
#define MOTOR_2 1

short usSpeed = 150;  //default motor speed
unsigned short usMotor_Status = BRAKE;

// void setup()                         
// {
//   pinMode(MOTOR_A1_PIN, OUTPUT);
//   pinMode(MOTOR_B1_PIN, OUTPUT);

//   pinMode(MOTOR_A2_PIN, OUTPUT);
//   pinMode(MOTOR_B2_PIN, OUTPUT);

//   pinMode(PWM_MOTOR_1, OUTPUT);
//   pinMode(PWM_MOTOR_2, OUTPUT);

//   pinMode(CURRENT_SEN_1, OUTPUT);
//   pinMode(CURRENT_SEN_2, OUTPUT);  

//   pinMode(EN_PIN_1, OUTPUT);
//   pinMode(EN_PIN_2, OUTPUT);

//   Serial.begin(9600);              // Initiates the serial to do the monitoring 

// }


// void loop() 
// {
//   digitalWrite(EN_PIN_1, HIGH);
//   digitalWrite(EN_PIN_2, HIGH); 

//   Forward();
// }

// void Forward()
// {
//   usMotor_Status = CW;
//   motorGo(MOTOR_1, usMotor_Status, usSpeed);
//   motorGo(MOTOR_2, usMotor_Status, usSpeed);
// }

// void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm)         //Function that controls the variables: motor(0 ou 1), direction (cw ou ccw) e pwm (entra 0 e 255);
// {
//   if(motor == MOTOR_1)
//   {
//     if(direct == CW)
//     {
//       digitalWrite(MOTOR_A1_PIN, LOW); 
//       digitalWrite(MOTOR_B1_PIN, HIGH);
//     }
//     else if(direct == CCW)
//     {
//       digitalWrite(MOTOR_A1_PIN, HIGH);
//       digitalWrite(MOTOR_B1_PIN, LOW);      
//     }
//     else
//     {
//       digitalWrite(MOTOR_A1_PIN, LOW);
//       digitalWrite(MOTOR_B1_PIN, LOW);            
//     }
    
//     analogWrite(PWM_MOTOR_1, pwm); 
//   }
//   else if(motor == MOTOR_2)
//   {
//     if(direct == CW)
//     {
//       digitalWrite(MOTOR_A2_PIN, LOW);
//       digitalWrite(MOTOR_B2_PIN, HIGH);
//     }
//     else if(direct == CCW)
//     {
//       digitalWrite(MOTOR_A2_PIN, HIGH);
//       digitalWrite(MOTOR_B2_PIN, LOW);      
//     }
//     else
//     {
//       digitalWrite(MOTOR_A2_PIN, LOW);
//       digitalWrite(MOTOR_B2_PIN, LOW);            
//     }
    
//     analogWrite(PWM_MOTOR_2, pwm);
//   }
// }

void setup() {
  // Set all control pins to output
  pinMode(MOTOR_A1_PIN, OUTPUT);
  pinMode(MOTOR_B1_PIN, OUTPUT);
  pinMode(MOTOR_A2_PIN, OUTPUT);
  pinMode(MOTOR_B2_PIN, OUTPUT);

  pinMode(PWM_MOTOR_1, OUTPUT);
  pinMode(PWM_MOTOR_2, OUTPUT);

  pinMode(EN_PIN_1, OUTPUT);
  pinMode(EN_PIN_2, OUTPUT);

  // Set current sense as input
  pinMode(CURRENT_SEN_1, INPUT);
  pinMode(CURRENT_SEN_2, INPUT);

  // Turn everything on HIGH
  digitalWrite(MOTOR_A1_PIN, HIGH);
  digitalWrite(MOTOR_B1_PIN, HIGH);
  digitalWrite(MOTOR_A2_PIN, HIGH);
  digitalWrite(MOTOR_B2_PIN, HIGH);

  digitalWrite(EN_PIN_1, HIGH);
  digitalWrite(EN_PIN_2, HIGH);

  analogWrite(PWM_MOTOR_1, 255); // Full speed
  analogWrite(PWM_MOTOR_2, 255); // Full speed

  Serial.begin(9600);
}

void loop() {
}