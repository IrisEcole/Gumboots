

// IR1 will be at the front  of the robot
#include <NewPing.h>

#define LEFT_PING_PIN  18 // Arduino pin tied to both trigger and echo pins on the ultrasonic sensor.
#define LEFT_PING_PIN_ECHO  19  // Arduino pin tied to both trigger and echo pins on the ultrasonic sensor.
#define CENTER_PING_PIN  9  // Arduino pin tied to both trigger and echo pins on the ultrasonic sensor.
#define CENTER_PING_PIN_ECHO  10  // Arduino pin tied to both trigger and echo pins on the ultrasonic sensor.
#define RIGHT_PING_PIN  16  // Arduino pin tied to both trigger and echo pins on the ultrasonic sensor.
#define RIGHT_PING_PIN_ECHO 17   // Arduino pin tied to both trigger and echo pins on the ultrasonic sensor.


#define MAX_DISTANCE 80// Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonarLeft(LEFT_PING_PIN, LEFT_PING_PIN_ECHO, MAX_DISTANCE);
NewPing sonarCenter(CENTER_PING_PIN, CENTER_PING_PIN_ECHO, MAX_DISTANCE);
NewPing sonarRight(RIGHT_PING_PIN, RIGHT_PING_PIN_ECHO,  MAX_DISTANCE);
enum State { TurnLeft, TurnRight, Reverse, Attack, Search, Search_Go_Forward_A_Bit, ForwardEscape };


const int IR1 = 8;

const int RIGHT_SPEED   = 3;
const int RIGHT_FORWARD = 2;
const int RIGHT_REVERSE = 4;
const int LEFT_SPEED    = 6;
const int LEFT_FORWARD  = 5;
const int LEFT_REVERSE  = 7;
 int started = 0;

#define REVERSE_DURATION  6 //The idea of those is that 
#define TURN_DURATION     4
#define SEARCH_LIMIT      6 // Get rid of that when we have attack
#define ATTACK_DURATION      15536//
#define STARTFORWARD    10

State state = Search_Go_Forward_A_Bit;
State nextState = Search;
int stateCount = 0;
int stateCountLimit = 0;

void setup() {
  // put your setup code here, to run once:
  // pinMode(IR1, INPUT);  // define this pin as an INPUT
   pinMode(RIGHT_SPEED, OUTPUT);
  pinMode(RIGHT_FORWARD, OUTPUT);
  pinMode(RIGHT_REVERSE, OUTPUT);
  
  pinMode(LEFT_SPEED, OUTPUT);
  pinMode(LEFT_FORWARD, OUTPUT);
  pinMode(LEFT_REVERSE, OUTPUT);

    // pindmode(A0, INPUT);
    // pindmode(LEFT_PING_PIN_ECHO, INPUT);
  // pinMode(IR2, INPUT);  // define this pin as an INPUT
  Serial.begin(9600);
  stateCountLimit = STARTFORWARD;
  state = Search_Go_Forward_A_Bit;


}


void loop() {
  // driveForward();
  // testMotors();
  // delay(800);

  // driveBackward();
  // delay(800);
  // testMotors();
    int val1; 
    if (!started) {
    delay(3500);
  started =1;
      }

  long left_distance;
  long right_distance;
  long center_distance;
  left_distance = sonarLeft.ping_cm();
  delay(30);
  center_distance = sonarCenter.ping_cm();
  delay(30);
  right_distance = sonarRight.ping_cm();
    delay(30);
  Serial.print("Ping Left: ");
  Serial.print(left_distance); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  Serial.print("Ping Center: ");
  Serial.print(center_distance); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  Serial.print("Ping RIght: ");
  Serial.print(right_distance); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  val1 = digitalRead(IR1);  //This should be the white line sensor in the front;
    //val1 = 0;

     
  // else if (val2 == 1) {
  //       nextState = TurnRight;
  //       state = ForwardEscape;
  //       stateCount = 0;
  //       stateCountLimit = REVERSE_DURATION;
  // }
if (val1 == 1) {
        nextState = TurnRight;
        state = Reverse;
        stateCount = 0;
        stateCountLimit = REVERSE_DURATION;
  } else if (center_distance > 0) {
      //If detects on center sensor atttaaaccck
  // Serial.println("TRYING TO SWITCH TO ATTACK");
        state = Attack;
        stateCount = 0;
        stateCountLimit = ATTACK_DURATION;
  }else if (right_distance != 0 && center_distance == 0) {
      //If detects on right sensor but not center; turn right

        stateCount = 0;
        nextState = Search;
        state = TurnRight;
        stateCount = 0;
        stateCountLimit = TURN_DURATION;
  }  else if (left_distance  != 0 && center_distance == 0 ) {
    //If detects on right sensor but not center; turn left
    
        stateCount = 0;
        nextState = Search;
        state = TurnLeft;
        stateCount = 0;
        stateCountLimit = TURN_DURATION;
  }



Serial.print("IRR before switch ");
Serial.print(val1);
Serial.print("\n");
Serial.print("State before  switch : ");
Serial.print(state);
Serial.print("\n");
Serial.print("State count before switch ");
Serial.print(stateCount);
Serial.print("\n");
Serial.print("State count limit before  switch : ");
Serial.print(stateCountLimit);
Serial.print("\n");
   switch(state) {
        case Search:
        //Right now it can't really find anything so this code is just gonna turn infinitely so I added a limit to it before it moves foward
            if (++stateCount < stateCountLimit) {
            turnLeftSearch();
            // driveForward();

            } else {
                state = Search_Go_Forward_A_Bit;
               stateCount = 0;
               stateCountLimit = STARTFORWARD;
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
        case ForwardEscape:
            if (++stateCount < stateCountLimit) {
            attack();

            } else {
                              state = Search;
               stateCount = 0;
               stateCountLimit = SEARCH_LIMIT;
            }
        break;
        case Attack:
            if (++stateCount < stateCountLimit) {
            attack();
            } else {
                state = Search;
                nextState = Search;
                
            }

        break;
    }


// Serial.print("IRR after switch ");
// Serial.print(val1);
// Serial.print("\n");
// Serial.print("State after switch : ");
// Serial.print(state);
// Serial.print("\n");
// Serial.print(state);


 // testMotors();

}


void driveForward() {
  // TODO: Complete this function
  digitalWrite(RIGHT_FORWARD, HIGH);
  digitalWrite(RIGHT_REVERSE, LOW);
  analogWrite(RIGHT_SPEED, 140);

  digitalWrite(LEFT_FORWARD, HIGH);
  digitalWrite(LEFT_REVERSE, LOW);
  analogWrite(LEFT_SPEED, 140);
}

void attack() {
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
 
void turnRightSearch() {
  // TODO: Complete this function
  digitalWrite(RIGHT_FORWARD, HIGH);
  digitalWrite(RIGHT_REVERSE, LOW);
  analogWrite(RIGHT_SPEED, 140);

  digitalWrite(LEFT_FORWARD, LOW);
  digitalWrite(LEFT_REVERSE, HIGH);
  analogWrite(LEFT_SPEED, 140);
}
 
void turnLeftSearch() {
  // TODO: Complete this function
  digitalWrite(RIGHT_FORWARD, LOW);
  digitalWrite(RIGHT_REVERSE, HIGH);
  analogWrite(RIGHT_SPEED, 120);

  digitalWrite(LEFT_FORWARD, HIGH);
  digitalWrite(LEFT_REVERSE, LOW);
  analogWrite(LEFT_SPEED, 120);
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
