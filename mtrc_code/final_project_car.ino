//photoresistor low: 300
//        high: 600

#include <SoftwareSerial.h> // SoftwareSerial for serial communication with HM10 bluetooth module.
#include <ArduinoBlue.h> // ArduinoBlue bluetooth library
#include <Servo.h>
const int trigger = 7;
const int echo = 6;
const int midpoint = 450;
const int SERVO_LEFT_PIN = 2;
const int SERVO_RIGHT_PIN = 3;
const int SERVO_BOX_PIN = 9;
const int photoresistor_1 = A5;
const int photoresistor_2 = A4;
Servo servoLeft;
Servo servoRight;
Servo servoBox;
int reading[2];



void setup(){
  pinMode(A5, INPUT);
  servoLeft.attach(SERVO_LEFT_PIN);
  servoRight.attach(SERVO_RIGHT_PIN);
  servoBox.attach(SERVO_BOX_PIN);
  Serial.begin(9600);
  pinMode(7, OUTPUT);
  pinMode(6, INPUT);
  pinMode(11, OUTPUT);

  
  servoBox.write(180);
  servoLeft.write(180);
  servoRight.write(60);
  delay(5000);
  servoLeft.write(180);
  servoRight.write(90);
  delay(1200);
  servoLeft.write(180);
  servoRight.write(60);
  delay(3000);
  servoLeft.write(90);
  servoRight.write(90);
}

long pingUltrasonic(){
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  long duration = pulseIn(echo, HIGH);
  long result = duration / 29 / 2;
  return result;
}

void loop(){
  Serial.println(pingUltrasonic());
  delay(50);
  
  if (pingUltrasonic() <= 3){
    Serial.println("test");
    digitalWrite(11, HIGH);
    delay(50);
    digitalWrite(11, LOW);
    delay(50);
    digitalWrite(11, HIGH);
    delay(50);
    digitalWrite(11, LOW);
    delay(50);
    digitalWrite(11, HIGH);
    delay(50);
    digitalWrite(11, LOW);
    delay(50);
    servoBox.write(90);
    delay(5000);
    servoBox.write(180);
  }
  

  
}
