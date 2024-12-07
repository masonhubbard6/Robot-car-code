int leftMotorPin = 7; //declare the pins to be used
int rightMotorPin = 8;
int leftMotorSpeed = 5;
int rightMotorSpeed = 6;
int enablePin = 3;

void setup() { 
  Serial.begin(9600); //serial communication
  pinMode(leftMotorPin, OUTPUT);//declare as outputs
  pinMode(rightMotorPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
} 

void loop() { 
  int rightSensor = analogRead(A0); //declare the sensors as analog inputs
  int middleSensor = analogRead(A1); 
  int leftSensor = analogRead(A2); 
//check conditions then call the corosplnding functions
  if (rightSensor > 1000 && middleSensor > 1000 && leftSensor > 1000 ) { 
    stopMotors(0); 
  } 
  if (middleSensor >= 600 && middleSensor <= 1000 ) { 
   moveForward(50); 
  } 
  if (rightSensor >= 600 && rightSensor <=1000 ) { 
    turnRight(85); 
  } 
  if (leftSensor >= 600 && leftSensor <= 1000 ) { 
    turnLeft(85); 
  } 
  if (middleSensor < 600 && rightSensor < 600 && leftSensor < 600 ) { 
    makeUTurn(100); 
  } 
//print out the results
  Serial.print("Right Sensor = ");
  Serial.print(rightSensor);
  Serial.print("\t");
  Serial.print("Middle Sensor = ");
  Serial.print(middleSensor);
  Serial.print("\t");
  Serial.print("Left Sensor = ");
  Serial.println(leftSensor);
} 

void stopMotors(int speedValue) { 
  digitalWrite(leftMotorPin, HIGH);
  digitalWrite(rightMotorPin, HIGH);
  analogWrite(leftMotorSpeed, speedValue);
  analogWrite(rightMotorSpeed, speedValue);
  digitalWrite(enablePin, HIGH);
} 
//declare the functions values
void makeUTurn(int speedValue) { 
  digitalWrite(leftMotorPin, HIGH); 
  analogWrite(leftMotorSpeed, speedValue); 
  digitalWrite(rightMotorPin, LOW); 
  analogWrite(rightMotorSpeed, speedValue / 2); 
  digitalWrite(enablePin, HIGH); 
} 

void moveForward(int speedValue) {
  digitalWrite(leftMotorPin, HIGH);
  digitalWrite(rightMotorPin, HIGH);
  analogWrite(leftMotorSpeed, speedValue);
  analogWrite(rightMotorSpeed, speedValue);
  digitalWrite(enablePin, HIGH);
} 

void turnRight(int speedValue) {
  digitalWrite(leftMotorPin, HIGH);
  digitalWrite(rightMotorPin, HIGH);
  analogWrite(leftMotorSpeed, 0);
  analogWrite(rightMotorSpeed, speedValue);
  digitalWrite(enablePin, HIGH);
}

void turnLeft(int speedValue) {
  digitalWrite(leftMotorPin, HIGH);
  digitalWrite(rightMotorPin, HIGH);
  analogWrite(leftMotorSpeed, speedValue);
  analogWrite(rightMotorSpeed, 0);
  digitalWrite(enablePin, HIGH);
}
