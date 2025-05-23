#include <Wire.h>
#include <LiquidCrystal.h>

// LCD configuration
LiquidCrystal lcd(7, 8, 4, 5, 6, 9);

// MPU6050 Address
const int MPU_ADDR = 0x68;

// L298N Pins
const int ENA = 10;  // PWM for Speed Control
const int IN1 = 11;  // Direction Control
const int IN2 = 12;  // Direction Control

// Encoder Pins
const int encoderA = 3;  // Interrupt Pin
const int encoderB = 13; // Digital Pin

// Variables
volatile int encoderCount = 0; // Tracks encoder pulses
float angle = 0;               // MPU6050 angle
float motorSpeed = 0;          // Motor speed

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);
  
  // Initialize LCD
  lcd.begin(16, 2);
  lcd.print("Initializing...");

  // Initialize MPU6050
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);  // Wake up MPU6050
  Wire.write(0);
  Wire.endTransmission(true);

  // L298N Motor Driver Pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // Encoder Pins
  pinMode(encoderA, INPUT_PULLUP);
  pinMode(encoderB, INPUT_PULLUP);

  // Interrupt for Encoder
  attachInterrupt(digitalPinToInterrupt(encoderA), readEncoder, RISING);

  lcd.clear();
  lcd.print("System Ready");
  delay(1000);
  lcd.clear();
}

void loop() {
  // Read MPU6050 Angle
  angle = getMPU6050Angle();

  // Map angle to motor speed and direction
  motorSpeed = map(constrain(angle, -90, 90), -90, 90, -255, 255);

  // Update motor control
  if (motorSpeed > 0) {
    // Forward
    analogWrite(ENA, motorSpeed);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  } else if (motorSpeed < 0) {
    // Backward
    analogWrite(ENA, -motorSpeed);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  } else {
    // Stop
    analogWrite(ENA, 0);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
  }

  // Display on LCD
  lcd.setCursor(0, 0);
  lcd.print("Angle: ");
  lcd.print(angle);
  lcd.setCursor(0, 1);
  lcd.print("Enc: ");
  lcd.print(encoderCount);

  delay(100);
}

// Read MPU6050 Angle
float getMPU6050Angle() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);  // Starting register for accelerometer
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 6, true);

  int16_t AcX = Wire.read() << 8 | Wire.read();
  int16_t AcY = Wire.read() << 8 | Wire.read();
  int16_t AcZ = Wire.read() << 8 | Wire.read();

  // Calculate angle (pitch)
  float angle = atan2(AcY, AcZ) * 180 / PI;
  return angle;
}

// Interrupt Service Routine for Encoder
void readEncoder() {
  if (digitalRead(encoderB) == HIGH) {
    encoderCount++;
  } else {
    encoderCount--;
  }
}
