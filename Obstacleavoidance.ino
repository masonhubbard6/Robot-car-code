// Define pins for motors, ultrasonic sensor, and servo
#define STBY 3
#define AIN1 7
#define BIN1 8
#define PWMA 5
#define PWMB 6
#define TRIG 13
#define ECHO 12
#define SERVO_PIN 10
#include <Servo.h>
// Define servo object
Servo myServo;

// Initialize the servo position
int servoPosition = 90;  // Start at the middle (90 degrees)

// Function to initialize all the pins
void setup() {
  // Initialize motor pins
  pinMode(STBY, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);

  // Initialize ultrasonic sensor pins
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  // Initialize servo motor
  myServo.attach(SERVO_PIN);
  myServo.write(servoPosition); // Initial position

  // Start the serial communication
  Serial.begin(9600);
}

// Function to measure distance using ultrasonic sensor
long measureDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  
  long duration = pulseIn(ECHO, HIGH);
  long distance = duration * 0.034 / 2;
  return distance;
}

// Function to move the robot forward
void forward(int speed) {
  digitalWrite(STBY, 1);
  digitalWrite(AIN1, 1);
  digitalWrite(BIN1, 1);
  analogWrite(PWMA, speed);
  analogWrite(PWMB, speed);
}

// Function to stop the robot
void stop(int arrete) {
  digitalWrite(STBY, 1);
  digitalWrite(AIN1, 1);
  digitalWrite(BIN1, 1);
  analogWrite(PWMA, arrete);
  analogWrite(PWMB, arrete);
}

// Function to move the robot backward
void backwards(int back) {
  digitalWrite(STBY, 1);
  digitalWrite(AIN1, 0);
  digitalWrite(BIN1, 0);
  analogWrite(PWMA, back);
  analogWrite(PWMB, back);
  delay(1000); // Move backward for 1 second (adjust based on your need)
  forward(0); // Stop after backing up
}

// Function to turn the robot left
void left(int leaf) {
  digitalWrite(STBY, 1);
  digitalWrite(AIN1, 1);
  digitalWrite(BIN1, 0);
  analogWrite(PWMA, leaf);
  analogWrite(PWMB, leaf);
}

// Function to turn the robot right
void right(int rule) {
  digitalWrite(STBY, 1);
  digitalWrite(AIN1, 0);
  digitalWrite(BIN1, 1);
  analogWrite(PWMA, rule);
  analogWrite(PWMB, rule);
}

// Main loop
void loop() {
  long distance = measureDistance();  // Measure the distance from the obstacle

  // If no obstacle detected, move forward
  if (distance > 26 || distance == 0) {
    forward(100);  // Move forward at full speed
  } 
  // If obstacle detected between 2 and 26 cm, stop and evaluate further
  else if (distance <= 26 && distance >= 2) {
    stop(0);  // Stop the car

    // Turn the servo left to check the left side
    myServo.write(180);
    delay(1000);  // Give time for servo to move
    long leftDistance = measureDistance();

    // If nothing detected on the left, try moving left
    if (leftDistance > 26 || leftDistance == 0) {
      left(100);  // Turn left
      delay(1000);  // Turn for 1 second
      forward(100);  // Move forward again
    } else {
      // If something is detected on the left, turn the servo right to check the right side
      myServo.write(0);
      delay(1000);  // Give time for servo to move
      long rightDistance = measureDistance();

      // If nothing detected on the right, try moving right
      if (rightDistance > 26 || rightDistance == 0) {
        right(100);  // Turn right 
        delay(1000);  // Turn for 1 second
        forward(100);  // Move forward again
      } 
      // If something is detected on both sides, go backward
      else {
        backwards(100);  // Move backward 
      }
    }

    // After checking left and right, return the servo to 90 degrees (center)
    myServo.write(90);  // Center the servo
    delay(1000);  // Give time for the servo to move back to 90 degrees
  }
}
