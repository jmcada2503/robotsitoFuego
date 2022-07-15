int speedPin = 11;
int dirPin1 = 12;
int dirPin2 = 13; 
int speedMotor= 255; 

int speedPin2 = 3; 
int dirPin3 = 2; 
int dirPin4 = 4; 





void setup(){
  Serial.begin(9600); 
  pinMode(speedPin, OUTPUT); 
  pinMode(dirPin1, OUTPUT);
  pinMode(dirPin2, OUTPUT); 
  pinMode(speedPin2, OUTPUT); 
  pinMode(dirPin3, OUTPUT);
  pinMode(dirPin4, OUTPUT); 
  
  
}

void loop() {
  digitalWrite(dirPin1, HIGH); 
  digitalWrite(dirPin2, LOW); 
  digitalWrite(dirPin3, HIGH);
  digitalWrite(dirPin4, LOW); 
  analogWrite(speedPin, 255);
  analogWrite(speedPin2, 255); 
  delay(105);
  analogWrite (speedPin, speedMotor);
  analogWrite (speedPin2, speedMotor); 
}
