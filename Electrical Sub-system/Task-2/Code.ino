/*
This is the code for task-2 of the recruitments, here we have created an obstacle avoiding bot using 3 HC-SR04 Ultrasonic Sensors which detect obstacles 
and accordingly navigate the bot through the obstacles.

The 3 sensors are mounted in three directions - front, left and right for better visualisation of obstacles in the path and accordingly planning the path
which the bot will take. Say the bot is moving straight forward, then in the path if it detect any obstacle within the range of 20 cm in any of the sensors,
it will alert the arduino and then the direction in which the obstacle distance is maximum, it will change its direction to that.

Motors are controlled using L293D Motor Driver where the INPUT pins are connected directly to the arduino's digital pin controlling the motors which are
connected to the OUTPUT pins of the driver. Then there are Enable pins which are used to control the speed of motors via PWM signals
*/

//L293D Motor Driver Control
const int LeftMotorForward = 7; //Controls the output for OUTPUT1
const int LeftMotorBackward = 8; //Controls the output for OUTPUT2
const int RightMotorForward = 13; //Controls the output for OUTPUT3
const int RightMotorBackward = 12; //Controls the output for OUTPUT4
const int ENA = 5; //Controls the PWM Signal controlling the speed for OUTPUT1 AND OUTPUT2
const int ENB = 6; //Controls the PWM Signal controlling the speed for OUTPUT3 AND OUTPUT4

// Front Ultrasonic Sensor
#define trigFront 3
#define echoFront 10

// Right Ultrasonic Sensor
#define trigRight 4
#define echoRight 9

// Left Ultrasonic Sensor
#define trigLeft 2
#define echoLeft 11

#define maximum_distance 200
boolean goesForward = false;

void setup() 
{
  //defining the pintype for various OUTPUTs
  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);

  //defining the pintype for various PWM OUTPUTs
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  //defining the pintype for various ultrasonic pins
  pinMode(trigFront, OUTPUT);
  pinMode(echoFront, INPUT);
  pinMode(trigRight, OUTPUT);
  pinMode(echoRight, INPUT);
  pinMode(trigLeft, OUTPUT);
  pinMode(echoLeft, INPUT);
}

void loop() 
{
  int distanceRight = readPing(trigRight, echoRight); //mneasures right direction distance
  int distanceLeft = readPing(trigLeft, echoLeft); //measures left direction distance
  int distanceFront = readPing(trigFront, echoFront); //measures front direction distance
  delay(50);

  // If any ultrasonic sensor detects obstacle closer than 20cm
  if (distanceFront <= 20 || distanceLeft <= 20 || distanceRight <= 20) {
    moveStop();
    delay(500); //delay for better stability while switching between two functions
    moveBackward();
    delay(500); //delay for better stability while switching between two functions
    moveStop();
    delay(500); //delay for better stability while switching between two functions

    // Decide turn direction based on more open side
    if (distanceRight > distanceLeft) 
    {
      turnRight();
    } 
    
    else 
    {
      turnLeft();
    }

    moveStop();
  } 
  
  else //if no object is detetected in the path
  {
    moveForward();
  }
}

int readPing(int trigPin, int echoPin) //function for taking data from the sensor
{
  long duration;
  int cm;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000);  // 30ms timeout
  cm = duration * 0.034 / 2;

  if (cm == 0 || cm > maximum_distance) //defining a certain threshold distance for maximum reading
  {
    cm = 250; // No valid reading
  }
  return cm;
}

void moveStop() //stopping the car 
{
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void moveForward() //car moves forward
{
  if (!goesForward) 
  {
    goesForward = true;
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);
    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW);
    analogWrite(ENA, 200);
    analogWrite(ENB, 200);
  }
}

void moveBackward() //car moves backward
{
  goesForward = false;
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
}

void turnRight() //car turns right
{
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
  delay(500);
}

void turnLeft() //car turns left
{
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
  delay(500);
}
