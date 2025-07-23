/*
void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT); // ultrasonic sensor output
  pinMode(4, INPUT); // ultrasonic sensor input
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  long dist = ultrasonicDetection();

  Serial.println(dist);

  delay(500);
*/
//From the internet, but comments are mine :)
// pins can be any digital pins
const int trigPin = 9;
const int echoPin = 10;

float duration, distance;

void setup() {
  // declare pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // creates a pulse from the trigPin for the sensor (echoPin) to read later
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //pulseIn records the time between a pulse, i.e. from low to high to low
  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2; // this converts the duration to distance from sensor
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(100);
}
