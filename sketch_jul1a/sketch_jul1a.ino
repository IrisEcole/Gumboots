
// Starter code the Sumobost Week 4 Workshops 2025
// 
// Refer to https://docs.arduino.cc/language-reference/ to see an overview of all the arduino functions and how they work!
 
// TODO: Define your pin numbers here
const RIGHT_SPEED   = 13;
const RIGHT_FORWARD = 0;
const RIGHT_REVERSE = 0;
const LEFT_SPEED    = 12;
const LEFT_FORWARD  = 0;
const LEFT_REVERSE  = 0;
 
void setup() {
  // TODO: Define the modes of your pins (hint: they should be OUTPUT)
 
  Serial.begin(9600);
 
}
 
void loop() {
 
  // TODO: call each of the functions below to test whether your functions are working!
  
  // E.g.
  // driveForward():
  // delay(100);
  // testMotors();
 
  // Slow down the arduino so we can see whats going on in the serial monitor
  delay(1000);
}
 
void driveForward() {
  // TODO: Complete this function
  
}
 
void driveBackward() {
  // TODO: Complete this function
 
}
 
void turnRight() {
  // TODO: Complete this function
 
}
 
void turnLeft() {
  // TODO: Complete this function
 
}
 
 
//-------------------------------------------------------
//              Testing functions
//-------------------------------------------------------
// Tells you what direction your motor is going based on the pins
void testMotors() {
  // Read motor direction states
  int rightForward = digitalRead(RIGHT_FORWARD);
  int rightReverse = digitalRead(RIGHT_REVERSE);
  int leftForward  = digitalRead(LEFT_FORWARD);
  int leftReverse  = digitalRead(LEFT_REVERSE);
 
  // Read motor speeds
  int rightSpeed = analogRead(RIGHT_SPEED);  // 0 - 1023
  int leftSpeed  = analogRead(LEFT_SPEED);   // 0 - 1023
 
  // Determine motion of each motor
  int rightDir = rightForward - rightReverse;  // 1 = forward, -1 = backward
  int leftDir  = leftForward - leftReverse;
 
  String direction;
 
  if (leftDir == 1 && rightDir == 1) {
    direction = "Forward";
  } else if (leftDir == -1 && rightDir == -1) {
    direction = "Backward";
  } else if (leftDir == 1 && rightDir == -1) {
    direction = "Left Turn";
  } else if (leftDir == -1 && rightDir == 1) {
    direction = "Right Turn";
  } else {
    direction = "Stopped or Spinning in Place";
  }
 
  // Print results
  Serial.print("Direction: ");
  Serial.println(direction);
  Serial.print("Left Motor Speed: ");
  Serial.println(leftSpeed);
  Serial.print("Right Motor Speed: ");
  Serial.println(rightSpeed);
  Serial.println("---------------------");
}
