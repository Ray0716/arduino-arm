//photoresistor low: 300
//        high: 600
const int midpoint = 450;

const int photoresistor_1 = A5;
const int photoresistor_2 = A4;

int reading[2];

void takeReading(){
  int val1 = analogRead(photoresistor_1);
  int val2 = analogRead(photoresistor_2);
  
  if(val1 > midpoint){
    reading[0] = 1;
  } else {
    reading[0] = 0;
  }
  
  if(val2 > midpoint){
    reading[1] = 1;
  } else {
    reading[1] = 0;
  }
}

void setup(){
  pinMode(A5, INPUT);
    Serial.begin(9600);
}

void loop(){
takeReading();
int val = analogRead(A5);
  Serial.print(val);
  Serial.print("   ");
  Serial.print(analogRead(A4));
  Serial.print(" || ");
  Serial.print(reading[0]);
  Serial.print("   ");
  Serial.println(reading[1]);
}
