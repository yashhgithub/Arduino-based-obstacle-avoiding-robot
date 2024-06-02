// Improved Obstacle-Avoiding Robot Code for Arduino in C++

#include <NewPing.h> // Include NewPing library for ultrasonic sensor

const int trigPin = 9;  // Ultrasonic sensor trigger pin
const int echoPin = 8;  // Ultrasonic sensor echo pin
const int motorLeftPin1 = 5; // Left motor driver pin 1 (IN1)
const int motorLeftPin2 = 4; // Left motor driver pin 2 (IN2)
const int motorRightPin1 = 6; // Right motor driver pin 1 (IN3)
const int motorRightPin2 = 7; // Right motor driver pin 2 (IN4)
const int motorSpeed = 150;  // Adjustable motor speed (0-255)
const int thresholdDistance = 30; // Obstacle detection range (cm)

NewPing sonar(trigPin, echoPin, 400); // Create NewPing object with maximum distance of 400 cm

void setup() {
  // Set motor driver pins as outputs
  pinMode(motorLeftPin1, OUTPUT);
  pinMode(motorLeftPin2, OUTPUT);
  pinMode(motorRightPin1, OUTPUT);
  pinMode(motorRightPin2, OUTPUT);
}

void loop() {
  long duration = sonar.ping(); // Measure ultrasonic travel time
  int distance = duration / (2 * 29.1); // Calculate distance in cm (assuming speed of sound = 343 m/s)

  // Obstacle avoidance logic
  if (distance <= thresholdDistance) {
    Serial.println("Obstacle detected!"); // Optional: Print obstacle detection message

    // Stop motors
    stopMotors();
    delay(500); // Short delay for stability

    // Backward motion
    backwardMotion();
    delay(500); // Adjust delay for desired backward movement distance

    // Turn right (adjust for left turn if needed)
    turnRight();
    delay(1000); // Adjust delay for desired turn angle

  } else {
    // Move forward
    moveForward();
  }

  delay(100); // Short delay between measurements
}

void moveForward() {
  // Set motor directions for forward motion
  digitalWrite(motorLeftPin1, HIGH);
  digitalWrite(motorLeftPin2, LOW);
  digitalWrite(motorRightPin1, HIGH);
  digitalWrite(motorRightPin2, LOW);

  // Set motor speed
  analogWrite(motorLeftPin1, motorSpeed);
  analogWrite(motorRightPin1, motorSpeed);
}

void stopMotors() {
  // Stop motors by setting both pins low (braking)
  digitalWrite(motorLeftPin1, LOW);
  digitalWrite(motorLeftPin2, LOW);
  digitalWrite(motorRightPin1, LOW);
  digitalWrite(motorRightPin2, LOW);
}

void backwardMotion() {
  // Set motor directions for backward motion
  digitalWrite(motorLeftPin1, LOW);
  digitalWrite(motorLeftPin2, HIGH);
  digitalWrite(motorRightPin1, LOW);
  digitalWrite(motorRightPin2, HIGH);

  // Set motor speed
  analogWrite(motorLeftPin1, motorSpeed);
  analogWrite(motorRightPin1, motorSpeed);
}

void turnRight() {
  // Set motor directions for right turn (adjust for left turn)
  digitalWrite(motorLeftPin1, HIGH);
  digitalWrite(motorLeftPin2, LOW);
  digitalWrite(motorRightPin1, LOW);
  digitalWrite(motorRightPin2, HIGH);

  // Set motor speed (adjust for desired turn speed)
  analogWrite(motorLeftPin1, motorSpeed);
  analogWrite(motorRightPin1, motorSpeed / 2); // Optionally adjust for sharper turn
}
