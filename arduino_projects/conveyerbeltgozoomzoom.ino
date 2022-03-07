#include <SoftwareSerial.h> // SoftwareSerial for serial communication with HM10 bluetooth module.
#include <ArduinoBlue.h> // ArduinoBlue bluetooth library
#include <Servo.h>
const int BUZZER = 11;
const int SERVO_RIGHT_PIN = 3;
Servo servoLeft;
Servo servoRight;
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  servoLeft.attach(SERVO_LEFT_PIN);
  servoRight.attach(SERVO_RIGHT_PIN);
}

// the loop function runs over and over again forever
void loop() {
  servoLeft.write(0);
  servoRight.write(0);                       // wait for a second
}
