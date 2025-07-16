// Starter code the Sumobost Week 4 Workshops 2025
// 
// Refer to https://docs.arduino.cc/language-reference/ to see an overview of all the arduino functions and how they work!
 
// TODO: Define your pin numbers here
const int RIGHT_SPEED   = 3;
const int RIGHT_FORWARD = 2;
const int RIGHT_REVERSE = 4;
const int LEFT_SPEED    = 6;
const int LEFT_FORWARD  = 5;
const int LEFT_REVERSE  = 7;
 
void setup() {
  // TODO: Define the modes of your pins (hint: they should be OUTPUT)
  pinMode(RIGHT_SPEED, OUTPUT);
  pinMode(RIGHT_FORWARD, OUTPUT);
  pinMode(RIGHT_REVERSE, OUTPUT);
  
  pinMode(LEFT_SPEED, OUTPUT);
  pinMode(LEFT_FORWARD, OUTPUT);
  pinMode(LEFT_REVERSE, OUTPUT);

  Serial.begin(9600);
 
}
 
void loop() {
 
  // TODO: call each of the functions below to test whether your functions are working!
  
  driveForward();
  delay(100);
  testMotors();
  delay(1000);

  driveBackward();
  delay(100);
  testMotors();
  delay(1000);

  turnLeft();
  delay(100);
  testMotors();
  delay(1000);

  turnRight();
  delay(100);
  testMotors();
  // E.g.
  // driveForward():
  // delay(100);
  // testMotors();
 
  // Slow down the arduino so we can see whats going on in the serial monitor
  delay(1000);
}
 
void driveForward() {
  // TODO: Complete this function
  digitalWrite(RIGHT_FORWARD, HIGH);
  digitalWrite(RIGHT_REVERSE, LOW);
  analogWrite(RIGHT_SPEED, 255);

  digitalWrite(LEFT_FORWARD, HIGH);
  digitalWrite(LEFT_REVERSE, LOW);
  analogWrite(LEFT_SPEED, 255);
}
 
void driveBackward() {
  // TODO: Complete this function
  digitalWrite(RIGHT_FORWARD, LOW);
  digitalWrite(RIGHT_REVERSE, HIGH);
  analogWrite(RIGHT_SPEED, 255);

  digitalWrite(LEFT_FORWARD, LOW);
  digitalWrite(LEFT_REVERSE, HIGH);
  analogWrite(LEFT_SPEED, 255);
}
 
void turnRight() {
  // TODO: Complete this function
  digitalWrite(RIGHT_FORWARD, HIGH);
  digitalWrite(RIGHT_REVERSE, LOW);
  analogWrite(RIGHT_SPEED, 255);

  digitalWrite(LEFT_FORWARD, LOW);
  digitalWrite(LEFT_REVERSE, HIGH);
  analogWrite(LEFT_SPEED, 255);
}
 
void turnLeft() {
  // TODO: Complete this function
  digitalWrite(RIGHT_FORWARD, LOW);
  digitalWrite(RIGHT_REVERSE, HIGH);
  analogWrite(RIGHT_SPEED, 255);

  digitalWrite(LEFT_FORWARD, HIGH);
  digitalWrite(LEFT_REVERSE, LOW);
  analogWrite(LEFT_SPEED, 255);
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