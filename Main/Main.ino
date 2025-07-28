

// IR1 will be at the front  of the robot
// #include <NewPing.h>

#define LEFT_PING_PIN  12  // Arduino pin tied to both trigger and echo pins on the ultrasonic sensor.
#define CENTER_PING_PIN  12  // Arduino pin tied to both trigger and echo pins on the ultrasonic sensor.
#define RIGHT_PING_PIN  12  // Arduino pin tied to both trigger and echo pins on the ultrasonic sensor.


#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

// NewPing sonarLeft(PING_PIN, LEFT_PING_PIN, MAX_DISTANCE);
// NewPing sonarCenter(PING_PIN, CENTER_PING_PIN, MAX_DISTANCE);
// NewPing sonarRight(PING_PIN, PING_PIN, MAX_DISTANCE);
enum State { TurnLeft, TurnRight, Reverse, Attack, Search, Search_Go_Forward_A_Bit };


 const int IR1 = 8;

const int RIGHT_SPEED   = 3;
const int RIGHT_FORWARD = 2;
const int RIGHT_REVERSE = 4;
const int LEFT_SPEED    = 6;
const int LEFT_FORWARD  = 5;
const int LEFT_REVERSE  = 7;


#define REVERSE_DURATION  1 //The idea of those is that 
#define TURN_DURATION     2
#define SEARCH_LIMIT      25 // Get rid of that when we have attack
#define ATTACK_DURATION      5//

State state = Search;
State nextState = Search;
int stateCount = 0;
int stateCountLimit = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(IR1, INPUT);  // define this pin as an INPUT
   pinMode(RIGHT_SPEED, OUTPUT);
  pinMode(RIGHT_FORWARD, OUTPUT);
  pinMode(RIGHT_REVERSE, OUTPUT);
  
  pinMode(LEFT_SPEED, OUTPUT);
  pinMode(LEFT_FORWARD, OUTPUT);
  pinMode(LEFT_REVERSE, OUTPUT);
  //pinMode(IR2, INPUT);  // define this pin as an INPUT
  Serial.begin(9600);
  stateCountLimit = SEARCH_LIMIT;

}


void loop() {
  // driveForward();
  // testMotors();
  // delay(800);

  // driveBackward();
  // delay(800);
  // testMotors();
    int val1; 

  // int left_distance;
  // int right_distance;
  // int center_distance;
  // left_distance = sonarLeft.ping_cm();
  // center_distance = sonarCenter.ping_cm();
  // right_distance = sonarRight.ping_cm();
  // Serial.print("Ping Left: ");
  // Serial.print(left_distance); // Send ping, get distance in cm and print result (0 = outside set distance range)
  // Serial.println("cm");
  // Serial.print("Ping Center: ");
  // Serial.print(center_distance); // Send ping, get distance in cm and print result (0 = outside set distance range)
  // Serial.println("cm");
  // Serial.print("Ping RIght: ");
  // Serial.print(right_distance); // Send ping, get distance in cm and print result (0 = outside set distance range)
  // Serial.println("cm");
  val1 = digitalRead(IR1);  //This should be the white line sensor in the front;


   switch(state) {
        case Search:
        //Right now it can't really find anything so this code is just gonna turn infinitely so I added a limit to it before it moves foward
            if (++stateCount < stateCountLimit) {
            turnLeft();

            } else {
                              state = Search_Go_Forward_A_Bit;
               stateCount = 0;
               stateCountLimit = SEARCH_LIMIT;
            }
        break;
                case Search_Go_Forward_A_Bit:
        //Happens when it turned a bunch and didnt find anything, no need for that I thinl
            if (++stateCount < stateCountLimit) {
            driveForward();

            } else {
                              state = Search;
               stateCount = 0;
               stateCountLimit = SEARCH_LIMIT;
            }
        break;

        case TurnLeft:
            if (++stateCount < stateCountLimit) {
                turnLeft();
            } else {
               state = Search;
               stateCount = 0;
               stateCountLimit = SEARCH_LIMIT;
            }
        break;
        case TurnRight:
            if (++stateCount < stateCountLimit) {
                turnRight();
            } else {
              state = Search;
               stateCount = 0;
               stateCountLimit = SEARCH_LIMIT;
            }
        break;
        case Reverse:
            if (++stateCount < stateCountLimit) {
                driveBackward();
            } else {
              //Reverse is only 
                state = nextState;
                nextState = Search;
                stateCount = 0;
                stateCountLimit = TURN_DURATION;
            }
        break;
        case Attack:
            if (++stateCount < stateCountLimit) {
            driveForward();
            } else {
                state = Search;
                nextState = Search;
            }

        break;
    }
   if (val1 == 0) {
        nextState = TurnRight;
        state = Reverse;
        stateCount = 0;
        stateCountLimit = REVERSE_DURATION;
  }

// //If detects on right sensor but not center; turn left
//      if (left_distance  == HIGH && center_distance == LOW ) {
//         stateCount = 0;
//         nextState = Search;
//         state = TurnLeft;
//         stateCount = 0;
//         stateCountLimit = TURN_DURATION;
//   }
// //If detects on center sensor atttaaaccck
//      if (center_distance == HIGH) {
//         state = Attack;
//         stateCount = 0;
//         stateCountLimit = ATTACK_DURATION;
//   }

// //If detects on right sensor but not center; turn right
//      if (right_distance == HIGH && center_distance == LOW ) {
//         stateCount = 0;
//         nextState = Search;
//         state = TurnLeft;
//         stateCount = 0;
//         stateCountLimit = TURN_DURATION;
//   }

Serial.print("IRR an state");
Serial.print(val1);
Serial.print(state);


 // testMotors();

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
