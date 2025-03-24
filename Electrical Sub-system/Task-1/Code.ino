/*
The the below code is for task-1 of recruitments where millis function is used to dim various LEDs for specific period of time. How this works is like say 
take example of led1, we have defined a variable prevMillisL1 which is for storing the currentMillis value when led1 is turned on, then there is 
currentMillis which basically starts counting time, now whenever the difference between the two (i.e..currentMillis - prevMillis1) is 2000 (intervalL1) it 
tells the arduino to turn it on and off and then the currentMillis value is recorded into the prevMillis1 (basically its value gets updated) and the cycle 
continues, again when next time the difference between them becomes 2000, it again turns on the led and then off and the prevMillis variable updates its 
value to that currentMillis value.

Similar logic works in case of led2 and led3.
*/

int L1 = 5; //led1
int L2 = 6; //led2
int L3 = 7; //led3

unsigned long prevMillisL1 = 0;
unsigned long prevMillisL2 = 0;
unsigned long prevMillisL3 = 0;

int intervalL1 = 2000; //dim led1 for 2 seconds before turning on
bool l1State = LOW;

bool l2State = LOW;
int intervalL2 = 3000; //dim led2 for 3 seconds before turning on

int l3OffTimes[] = {1000, 2000, 3000, 4000, 5000}; //dim the led3 in a pattern of increasing seconds upto 5
int l3Index = 0;
bool l3IsOn = false;
int IntervalL3 = 1000;
int  l3LastMillis = 0;

void setup() 
{
  //defining the pintype of LEDs
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);
}

void loop() 
{
  unsigned long currentMillis = millis(); //initiating millis() command

  if (currentMillis - prevMillisL1 >= intervalL1) 
  {
    prevMillisL1 = currentMillis;
    l1State = !l1State;
    digitalWrite(L1, l1State);
  }

  if (currentMillis - prevMillisL2 >= intervalL2) 
  {
    prevMillisL2 = currentMillis;
    l2State = !l2State;
    digitalWrite(L2, l2State);
    intervalL2 = l2State ? 1000 : 3000;
  }

  if (currentMillis - l3LastMillis >= IntervalL3) 
  {
    l3LastMillis = currentMillis;
    if (l3IsOn) 
    {
      l3IsOn = false;
      digitalWrite(L3, LOW);
      l3Index = (l3Index + 1) % 5; 
      IntervalL3 = l3OffTimes[l3Index];
    } 
    
    else 
    {
      l3IsOn = true;
      digitalWrite(L3, HIGH);
      IntervalL3 = 1000; 
    }
  }
}
