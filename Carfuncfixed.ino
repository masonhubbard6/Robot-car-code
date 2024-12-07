#include <IRremote.hpp>

const int IR_RECEIVE_PIN = 9; // Define the pin connected to the IR receiver  
int STBY = 3;  
int PWMA = 5;  
int PWMB = 6;  
int AIN1 = 7;  
int BIN1 = 8;  

int vitesse = 50; // Initial speed

// Define IR codes as constants for readability
#define STOP_CODE 3208707840
#define FORWARD_CODE 3108437760
#define LEFT_CODE 3141861120
#define ACCELERATE_CODE 3860463360
#define RIGHT_CODE 3158572800
#define BACKWARD_CODE 3927310080
#define SLOWDOWN_CODE 3877175040
#define BACKTURNLEFT_CODE 3910598400
#define BACKTURNRIGHT_CODE 4061003520

//declare the functions

void forward(int speed) { 
  digitalWrite(STBY, 1);  
  digitalWrite(AIN1, 1);  
  digitalWrite(BIN1, 1);  
  analogWrite(PWMA, speed);
  analogWrite(PWMB, speed);  
}  

void backwards(int back) { 
  digitalWrite(STBY, 1); 
  digitalWrite(AIN1, 0); 
  digitalWrite(BIN1, 0); 
  analogWrite(PWMA, back); 
  analogWrite(PWMB, back); 
} 

void stop(int arrete) {  
  digitalWrite(STBY, 1);  
  digitalWrite(AIN1, 1);  
  analogWrite(PWMA, arrete);  
  digitalWrite(BIN1, 1);  
  analogWrite(PWMB, arrete);  
} 

void left() { 
  digitalWrite(STBY, 1); 
  digitalWrite(AIN1, 1); 
  digitalWrite(BIN1, 0); 
  analogWrite(PWMA, 100); 
  analogWrite(PWMB, 25); 
} 

void right() { 
  digitalWrite(STBY, 1); 
  digitalWrite(AIN1, 0); 
  digitalWrite(BIN1, 1); 
  analogWrite(PWMA, 25); 
  analogWrite(PWMB, 100); 
} 

void backturnright() { 
  digitalWrite(STBY, 1); 
  digitalWrite(AIN1, 0); 
  digitalWrite(BIN1, 0); 
  analogWrite(PWMA, 25); 
  analogWrite(PWMB, 100); 
} 

void backturnleft() { 
  digitalWrite(STBY, 1); 
  digitalWrite(AIN1, 0); 
  digitalWrite(BIN1, 0); 
  analogWrite(PWMA, 100); 
  analogWrite(PWMB, 25); 
} 

void accelerate() {
  // Increase speed by 50
  vitesse += 50; 
  // Ensure that the speed does not exceed 255 (maximum for PWM)
  if (vitesse > 255) {
    vitesse = 255;
  }
  Serial.print("Speed Increased to: ");
  Serial.println(vitesse);
  forward(vitesse); // Apply the new speed for forward motion
}

void slowdown() {
  // Decrease speed by 50, but ensure it doesn't go below 0
  if (vitesse > 50) { // Allow speed to decrease only if it's greater than 50
    vitesse -= 50;
  } else {
    vitesse = 0; // Set to 0 if speed would go below 0
  }
  
  Serial.print("Speed Decreased to: ");
  Serial.println(vitesse);
  forward(vitesse); // Apply the decreased speed for forward motion
} 

void setup() {  
  pinMode(STBY, OUTPUT); //Declare as outputs
  pinMode(AIN1, OUTPUT);
  pinMode(BIN1, OUTPUT);
  
  Serial.begin(9600);  // initialize serial communication

  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Initialize the receiver  

  Serial.println("IR Receiver Initialized. Waiting for input...");  
}

void loop() {  
  // Check if a signal is received  
  if (IrReceiver.decode()) {  
    Serial.print("Received HEX Value: 0x");  
    Serial.println(IrReceiver.decodedIRData.decodedRawData); // Print the HEX value of the received signal  
    IrReceiver.resume(); // Prepare to receive the next signal  

    // Check for specific IR codes and perform corresponding actions
    if (IrReceiver.decodedIRData.decodedRawData == STOP_CODE) { 
      stop(0); 
    } 
    else if (IrReceiver.decodedIRData.decodedRawData == FORWARD_CODE) { 
      forward(50); 
    } 
    else if (IrReceiver.decodedIRData.decodedRawData == LEFT_CODE) { 
      left(); 
    } 
    else if (IrReceiver.decodedIRData.decodedRawData == ACCELERATE_CODE) { 
      accelerate(); // Increment speed on each button press
    } 
    else if (IrReceiver.decodedIRData.decodedRawData == RIGHT_CODE) { 
      right(); 
    } 
    else if (IrReceiver.decodedIRData.decodedRawData == BACKWARD_CODE) { 
      backwards(50); 
    } 
    else if (IrReceiver.decodedIRData.decodedRawData == SLOWDOWN_CODE) { 
      slowdown(); // Decrease speed on each button press
    } 
    else if (IrReceiver.decodedIRData.decodedRawData == BACKTURNLEFT_CODE) { 
      backturnleft(); 
    } 
    else if (IrReceiver.decodedIRData.decodedRawData == BACKTURNRIGHT_CODE) { 
      backturnright(); 
    } 
  }
}
