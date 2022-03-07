int sensors[] = {9, 2, 3, 4, 5, 6, 7, 8};
int reading[8];
const int key[] = {0, 1};
bool error = false;
 
void scanBarcode(){
  error = false;
  for (int i=0; i < 8; i++){
    if (reading[i] != key[i]){ //if reading is not the same as key
      error = true; //set error flag
      digitalWrite(13, HIGH);   
      delay(1000);              
      digitalWrite(13, LOW);  
      delay(1000); 
    }
  }
}

void setup() {
  pinMode(13, OUTPUT);
  for (int i=0; i<8; i++){
    pinMode(sensors[i], INPUT);
  }
  Serial.begin(9600);
}
 
void loop() {
  digitalWrite(13, HIGH);
  for (int i=0; i<8; i++){ 
    if(digitalRead(sensors[i]) == HIGH){
      reading[i] = 1;
    } else {
      reading[i] = 0;
    }
  }
 for (int i=0; i<8; i++){
  Serial.print(reading[i]);
  Serial.print(" ");
 }
  Serial.println("");
  delay(50);

    }
