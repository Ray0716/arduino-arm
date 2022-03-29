//under development
// ray tang

//config : arduino uno bluetooth tx 12
//                               rx 13
//                  right servo pin 10
//                   left servo pin 7
//                          joystick x pin A0
//                          joystick y pin A1
//                          button out pin A5


#include <SoftwareSerial.h>
#include <Servo.h>

#include <ArduinoBlue.h>
int motor1Pin = 3; // H-bridge leg 1
int motor2Pin = 4; // H-bridge leg 2
int speedPin = 5; // H-bridge enable pin
int speed;
int sensitivity = 7.95;
int servo = 8; 
int count = 90;

int node_oneVal = 90; //determines the value for nodeone servo it wrotes at beginning of each main loop
int node_one_primeVal = 90;

int d_padPin = A5; //testing for joystick and dpad
int joystickX = A0;
int joystickY = A1;

Servo node_one;
Servo node_one_prime;

const int BLUETOOTH_TX_PIN = 12;
const int BLUETOOTH_RX_PIN = 13;
SoftwareSerial bluetooth(BLUETOOTH_TX_PIN, BLUETOOTH_RX_PIN);

ArduinoBlue phone(bluetooth); // pass reference of bluetooth object to ArduinoBlue constructor.

// ID of the slider moved.
/////int sliderId = phone.getSliderId();

// Slider value goes from 0 to 200.
//int sliderVal = phone.getSliderVal();

int oldsliderVal = 0;


void setup()
{
Serial.begin(9600);
bluetooth.begin(9600);
delay(100);
pinMode(motor1Pin, OUTPUT);
pinMode(motor2Pin, OUTPUT);
pinMode(speedPin, OUTPUT);




node_one.attach(10); //attaching 1st rotation  servo to pin 10
node_one_prime.attach(7);

node_one.write(90);
node_one_prime.write(90);


}



void loop() 
{
  
node_one.write(node_oneVal);
node_one_prime.write(node_one_primeVal);

int d_padVal = analogRead(d_padPin);
int joystickXVal = analogRead(joystickX);
int joystickYVal = analogRead(joystickY);


//Serial.println(d_padVal); if it is withon range of 2 it is assigned number from 1 to 4
Serial.print(joystickXVal);
Serial.print(" | ");
Serial.print(joystickYVal);
Serial.print("         ");//suppposd to print "     dpadvl"


if (joystickXVal != 480 or joystickXVal != 481 or joystickXVal != 482){ // if x axis of joystick is not moving the motor stays still
  
  if (joystickXVal >= 480){ // if joystick is moved right
    //node_one.write(((971-joystickXVal)/5.444444444)+90); // get x value starting from 0 to 490 (onleft side) then map it for servo
    Serial.print(round((0 + (490-(971-joystickXVal))/5.444444444)/8)+90);//((971-joystickXVal)/5.444444444));
    
    node_oneVal = (round((0 + (490-(971-joystickXVal))/5.444444444)/8)+90);
    node_one_primeVal = 80;
  }

  
  if (joystickXVal <= 479){ //if joystick moved left
    //node_one.write((971-joystickXVal)/5.444444444444);
    Serial.print(round((0 + (490-(971-joystickXVal))/5.444444444)/8)+90);
    
    node_oneVal = (round((0 + (490-(971-joystickXVal))/5.444444444)/8)+90);
    node_one_primeVal = 96;

    //node_oneVal = 40;
   // node_one.write(40);
    
  }

  
}


if (joystickXVal == 475 or joystickXVal == 476 or joystickXVal == 477 or joystickXVal == 478 or joystickXVal == 479  or joystickXVal == 480  or joystickXVal == 481 or joystickXVal == 482 or joystickXVal == 483 or joystickXVal == 484 or joystickXVal == 485){
  node_one.write(90);
  node_one_prime.write(90);

  node_one_primeVal = 90;
  node_oneVal = 90;
  //Serial.print("0");
}






if (d_padVal == 0 or d_padVal == 1){
  Serial.print("left");
}
if (d_padVal == 485 or d_padVal == 484 or d_padVal == 483 or d_padVal == 486 or d_padVal == 487 or d_padVal == 488 or d_padVal == 499 or d_padVal == 500){
  Serial.print("up");
}

if (d_padVal == 647 or d_padVal == 646 or d_padVal == 648){

  Serial.print("right");
}

if (d_padVal == 728 or d_padVal == 727 or d_padVal == 726 or d_padVal == 729 or d_padVal == 730){

  Serial.print("down");
}





Serial.print("      ");
Serial.print(d_padVal);
   
Serial.println(" ");



// ID of the slider moved.
int sliderId = phone.getSliderId();

// Slider value goes from 0 to 200.
int sliderVal = phone.getSliderVal();
int button = phone.getButton();



//code for motor move one side to hter, servo motor go from 0 to 180 degreea
//if (button == 0){


  if (button == 0){
    count = 1;
    
    for(count = 1; count <= 180; ++count){
    node_one.write(count);
    delay(10);
    Serial.println(count);
    
    }

  
  }
  
  if (button == 1){
    count = 180;
     for(count = 180; count >= 1; --count){
    node_one.write(count);
    delay(10);
    Serial.println(count);
  }
  }

  count = 0;

  //count = count + 1;
  //node_one.attach(0);
//}





//code for node one rotate (ITS NOW A SERVER MOTOR WOOOOOOO)
if (sliderId != -1) {
  Serial.print(sliderVal);
  Serial.print(" | ");
  
  if (oldsliderVal != -1){
  Serial.print(oldsliderVal);
  }
  
  Serial.println(" ");

  if (sliderId == 0){
    
    
    node_one.write(round(sliderVal*1.111111111111111111111111111));
    delay(1);

    
  }


  
    

    /*
  if (oldsliderVal != (-1 and sliderVal)){
    
    //if (oldsliderVal < sliderVal){  // if the old val is less than the current than mean val is increas
    analogWrite(speedPin, (250));
    delay(sensitivity);
    analogWrite(speedPin, (0));
    //}


    //if (oldsliderVal >= sliderVal){  // if the old val is more than the current than mean val is decres
     // analogWrite(speedPin, (250));
     // delay(sensitivity);
     // analogWrite(speedPin, (0));
    //}
    
  
  }
  */

}
oldsliderVal = sliderVal;
}
