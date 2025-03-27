//declaring all the required pins
int trigPin = 10;
int echoPin = 9;

int input1 = 7;
int input2 = 8;

int ENA = 6;

void setup()
{
  //defining their pin type
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(input1, OUTPUT);
  pinMode(input2, OUTPUT);
  pinMode(ENA, OUTPUT);
}

void loop()
{
  int duration;
  int distance;
 
  //taking data from ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  
  distance = duration * 0.034/2;
  if (distance < 10)
  {
    digitalWrite(input1, LOW);
    digitalWrite(input2, LOW);
  }
  
  if (distance >= 10 && distance < 15)
  {
    digitalWrite(input1, HIGH);
    digitalWrite(input2, LOW);
    //analogWrite(ENA, 1023);
  }
  
  if (distance >= 15 && distance < 20)
  {
    digitalWrite(input1, LOW);
    digitalWrite(input2, HIGH);
    //nalogWrite(ENA, 1023);
  }
  
  else
  {
   	digitalWrite(input1, LOW);
   	digitalWrite(input2, LOW); 
  }
}
