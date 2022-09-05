#include <SoftwareSerial.h>
#include <Servo.h>

#include <ArduinoBlue.h>
int right_sen = 0.8;

int speed;
double sensitivity = 3;   // higher values decrease sensitivity, lower values increase, 1 is max (straight 0 to 180 for servo with no scaling)
//int servo = 8; 
int count = 90;

int node_oneVal = 90; //determines the value for nodeone servo it wrotes at beginning of each main loop
int node_twoVal = 90;
int claw_rotateVal = 90;
int clawVal = 90;


int claw_rotate_button = 0;
int claw_button = 0;

int d_padPin = A5; //testing for joystick and dpad
int joystickX = A0;
int joystickY = A1;

Servo node_one;
Servo node_two;
Servo claw_rotate;
Servo claw;

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





node_one.attach(10); //attaching 1st rotation  servo to pin 10
node_two.attach(6);
claw_rotate.attach(7);
claw.attach(8);

node_one.write(90);
node_two.write(90);
claw_rotate.write(90);
claw.write(90);
TIMSK0=0;

}



//--------------------------------------------------------------------------------------------


void loop() 
{
  
node_one.write(node_oneVal);
node_two.write(node_twoVal);
claw_rotate.write(claw_rotateVal);
//claw.write(clawVal);

int d_padVal = analogRead(d_padPin);
int joystickXVal = analogRead(joystickX);
int joystickYVal = analogRead(joystickY);


//Serial.println(d_padVal); if it is withon range of 2 it is assigned number from 1 to 4
Serial.print(joystickXVal);
Serial.print(" | ");
Serial.print(joystickYVal);
Serial.print("       N1 ");//suppposd to print "     dpadvl"
Serial.print(node_oneVal);
//Serial.print("      N1' ");
//Serial.print(node_one_primeVal);
Serial.print("       N2 ");
Serial.print(node_twoVal);
Serial.print("       CR ");
Serial.print(claw_rotateVal);
Serial.print("     D_PAD - ");
Serial.print(d_padVal);
Serial.print("     SEN: ");
Serial.print(sensitivity);



// if joystick is in rest position ---------------------------------------------------JOYSTICK X

if (joystickXVal >= 457 and joystickXVal<= 570){
  node_one.write(90);                            // UNCOMMENT THIS WHEN DONE WITH TESTING VERY VERY IMPORTANT 
//  node_one_prime.write(90);

  //node_one_primeVal = 90;
  node_oneVal = 90;
  //Serial.print("0");
}
  
  if (joystickXVal >= 571){ // if joystick is moved right
    //Serial.print(round(joystickXVal / 5.44)); //((971-joystickXVal)/5.444444444));
    int a = round((joystickXVal / 5.44)-90);  
    Serial.print("      a = ");
    Serial.print(a);
    node_oneVal = (90+(a/ (sensitivity))); // a is 90 - 0 - 90p

    //node_one_primeVal = (90-(a/(sensitivity)));
  }
//bmjfnhf
  
  if (joystickXVal <= 457){ //if joystick moved left
    //node_one.write((971-joystickXVal)/5.444444444444);
    //Serial.print(round((0 + (475-(971-joystickXVal))/5.4)/8)+90);
    int a = round(90-(joystickXVal / 5.44));
    Serial.print("      a = ");
    Serial.print(a);

    node_oneVal = (90-(a/sensitivity));
    
    //node_one_primeVal = (90+(a/sensitivity));

    //node_oneVal = 40;
   // node_one.write(40);
    
  }





// ---------------------------------------------------------------------------------------------JOYSTICK Y



  
if (joystickYVal >= 457 and joystickYVal<= 570){
  node_two.write(90);                            // UNCOMMENT THIS WHEN DONE WITH TESTING VERY VERY IMPORTANT 
 
  node_twoVal = 90;
  //Serial.print("0");
}


  
  if (joystickYVal >= 571){ // if joystick is moved up
    //node_one.write(((971-joystickXVal)/5.444444444)+90); // get x value starting from 0 to 490 (onleft side) then map it for servo
    //Serial.print(round(joystickXVal / 5.44)); //((971-joystickXVal)/5.444444444));
    int a = round((joystickYVal / 5.44)-90);  
    
    node_twoVal = (90+(a/3));

    //node_one_primeVal = (90-(a/(sensitivity)));
  }

  
  if (joystickYVal <= 469){ //if joystick moved down
    //node_one.write((971-joystickXVal)/5.444444444444);
    //Serial.print(round((0 + (475-(971-joystickXVal))/5.4)/8)+90);
    int a = round(90-(joystickYVal / 5.44));

    node_twoVal = (90-(a/3));
    
    //node_one_primeVal = (90+(a/sensitivity));

    //node_oneVal = 40;
   // node_one.write(40);
    
  }

  











if (d_padVal == 0 or d_padVal == 1 or d_padVal == 2){
  Serial.print("left");
  sensitivity = sensitivity + 0.2;
  delay(30000);
}


if (d_padVal > 325 and d_padVal < 550){
  Serial.print("up");

  claw_rotate_button += 1;

  if (claw_rotate_button % 2 == 0){
    claw_rotateVal = 90;
  }
  else {
    claw_rotateVal = 0;
  }
  
  delay(30000);
  
}

if (d_padVal > 551 and d_padVal < 675){
  Serial.print("right");
  sensitivity = sensitivity - 0.2;
  delay(30000);
}

if (d_padVal > 676 and d_padVal < 776){

  Serial.print("down");

  claw_button += 1;
Serial.print(claw_button);
  if (claw_button % 2 == 0){
//    clawVal = 100;
    claw.write(180);
    delay(200000);
    claw.write(90);
    
  }else{

    claw.write(0);
    delay(200000);
    claw.write(90);
  }

   /* claw.write(80);
    delay(100000);
    claw.write(90); */
}else{
  claw.write(90);
}
  
//  delay(30000);





/*
Serial.print("      ");
Serial.print(d_padVal);
*/
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





//code for node one rotate 
if (sliderId != -1) {
  Serial.print(sliderVal);
  Serial.print(" | ");
  
  if (oldsliderVal != -1){
  Serial.print(oldsliderVal);
  }
  
  Serial.println(" ");

  if (sliderId == 0){
    
    
    //node_one.write(round(sliderVal*1.111111111111111111111111111));
    //delay(1);

    
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
