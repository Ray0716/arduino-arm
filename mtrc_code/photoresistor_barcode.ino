//photoresistor low: 300
//        high: 600
const int midpoint = 0;
const int key[] = {0, 1, 0, 1, 1, 0, 0, 1};

const int photoresistor_1 = A5;
const int photoresistor_2 = A4;

int reading[2];

void takeReading(){
  int val1 = analogRead(photoresistor_1);
  int val2 = analogRead(photoresistor_2);
  
  if(val1 > 7){
    reading[0] = 1;
  } 
  if(val1 == 0){
    reading[0] = 0;
  }


  
  if(val2 > 7){
    reading[1] = 1;
  } 
  if(val2 == 0){
    reading[1] = 0;
  }
}

void setup(){
  pinMode(11, OUTPUT);
  pinMode(A5, INPUT);
    Serial.begin(9600);
}

void loop(){
takeReading();
int val = analogRead(A5);
int vall = analogRead(A4);
const int outpdata[] = {val, vall};
  Serial.print(val);
  Serial.print("   ");
  Serial.print(vall);
  Serial.print(" || ");
  Serial.print(reading[0]);
  Serial.print("   ");
  Serial.println(reading[1]);
  if (reading[0] == 0 and reading[1] == 1){
    digitalWrite(11, HIGH);
    delay(100);
    digitalWrite(11, LOW);
    delay(1000);
    
  }
  
}
