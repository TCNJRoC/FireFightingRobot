/*PINOUTS
M1=
E1=

M=
E2=

left sensor = 13
middle sensor = 12
right sensor = 11   

OTHER INFO
digitalWrite(M2,LOW); LOW = FRONT, HIGH = BACK  
nalogWrite(E1, value);  value is speeed between 0 and 255


*/
const int E1 = 20;
const int M1 = 21;
const int E2 = 19;                         
const int M2 = 18;  

const int leftSensor = 13;
const int midSensor = 12;
const int rightSensor = 11;

const int flameSensor = A5;

int leftCm = 0;
int midCm = 0;
int rightCM = 0;

int flameNum = 0;

// [ BATTERY POWER ] [ COMMON GROUND ] [ ARDUINO POWER ]

void setup() {
      pinMode(M1, OUTPUT);   
      pinMode(M2, OUTPUT); 
      Serial.begin(9600);
}

void loop() 
{
  leftCm = getSensorValuecm(leftSensor);
  midCm = getSensorValuecm(midSensor);
  rightCM = getSensorValuecm(rightSensor);

  flameNum = analogRead(flameSensor);
  if (flameNum > 50)
  {
    //fan goes off
  }
  Serial.print(midCm);
  Serial.println();

  
  
  if (leftCm > 5 && rightCM > 5 && midCm > 5)
  {
    foreward();
  }
  else if (leftCm < 5 && rightCM > 5 && midCm < 5)
  {
    turnRight();
  }
  else{
    analogWrite(E1, 0);   
    analogWrite(E2, 0);
  }
  
}

void turnRight()
{
    digitalWrite(M1,LOW);   
    digitalWrite(M2,HIGH);
    analogWrite(E1, 255);   
    analogWrite(E2, 255);
    delay(1000);
    analogWrite(E1, 0);   
    analogWrite(E2, 0);
}

void foreward()
{
    digitalWrite(M1,LOW);  //LOW = FOREQARD 
    digitalWrite(M2,LOW);  //HIGH =  BACKWARDS
    analogWrite(E1, 255);   
    analogWrite(E2, 255);
  
}
int getSensorValuecm(int sensor)
{
  int duration = 0;
  int cm = 0;
  
  pinMode(sensor, OUTPUT);
  digitalWrite(sensor, LOW);
  delayMicroseconds(2);
  digitalWrite(sensor, HIGH);
  delayMicroseconds(5);
  digitalWrite(sensor, LOW);

  pinMode(sensor, INPUT);
  duration = pulseIn(sensor, HIGH);
  cm = convertToCm(duration);
  return cm;
}

int convertToCm(int microseconds) 
{
  return microseconds / 29 / 2;
}

