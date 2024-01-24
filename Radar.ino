
#include <Servo.h>

const int baudRate = 9600;


// Deifne Ultrasonic sensor pins
const int trigPin = 10;
const int echoPin = 11;

// Variables for distance
long duration;
int distance;

// define buzzer pin
const int piezoPin = 8;

// beep frequencies 
int notes[] = { 262, 462, 862, 1662, 3262 };

// object for connecting motor
Servo myServo;
const int servoPin = 12;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(baudRate);
  myServo.attach(servoPin);
}

// Print: angle, distance to object;
void loop() {
  for (int i = 15; i <= 165; i++) {
    myServo.write(i);
    delay(30);
    distance = calculateDistance();
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
  }
}

int calculateDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);  // Reads echoPin and returns the travel time of sound wave in microseconds
  distance = duration * 0.034 / 2;
  beep();
  return distance;
}

void beep() {
  if (distance > 40) {
    noTone(piezoPin);
    delay(10);
    noTone(piezoPin);
    delay(30);
  } else if (distance > 30) {
    tone(piezoPin, notes[1]);
    delay(10);
    noTone(piezoPin);
    delay(30);
  } else if (distance > 20) {
    tone(piezoPin, notes[2]);
    delay(10);
    noTone(piezoPin);
    delay(30);
  } else if (distance > 10) {
    tone(piezoPin, notes[3]);
    delay(10);
    noTone(piezoPin);
    delay(30);
  } else {
    tone(piezoPin, notes[4]);
    delay(10);
    noTone(piezoPin);
    delay(30);
  }
}