// Pin declarations
const int soilMoisturePin = A0;
const int rainDropPin = A1;
const int motor1Pin1 = 2;
const int motor1Pin2 = 3;
const int motor2Pin1 = 4;
const int motor2Pin2 = 5;

// Threshold values
const int soilMoistureThreshold = 600;
const int rainDropThreshold = 900;

// Motor rotation time in milliseconds
const int motorRotationTime = 2500;

// Variable to keep track of roof state
bool roofClosed = false;

void setup() {
  // Initialize motor pins as output
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
}

void loop() {
  int soilMoistureValue = analogRead(soilMoisturePin);
  int rainDropValue = analogRead(rainDropPin);

  // Check if both sensors are below threshold and roof is not closed
  if (soilMoistureValue < soilMoistureThreshold && rainDropValue < rainDropThreshold && !roofClosed) {
    // Rotate motors clockwise to close the roof
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, HIGH);
    delay(motorRotationTime);

    // Stop the motors
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, LOW);
    
    // Update roof state
    roofClosed = true;
  }
  else if (roofClosed && (soilMoistureValue >= soilMoistureThreshold || rainDropValue >= rainDropThreshold)) {
    // Check if either sensor turns off after roof is closed
    while ((soilMoistureValue >= soilMoistureThreshold || rainDropValue >= rainDropThreshold)) {
      soilMoistureValue = analogRead(soilMoisturePin);
      rainDropValue = analogRead(rainDropPin);
    }

    // Rotate motors anticlockwise to open the roof
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);
    delay(motorRotationTime);

    // Stop the motors
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, LOW);
    
    // Update roof state
    roofClosed = false;
  }
}
