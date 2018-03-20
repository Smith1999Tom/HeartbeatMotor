#include <math.h>

const int motorPin = 9;
const int potPin = 2;
const int buttonPin = 4;
double potValue = 0;
double Speed1 = 0;

int buttonPreviousState = 0;
int buttonCurrentState = 0;
boolean buttonLatch = false;

double sinY = 0;
double sinX = 0;
const double pi = 3.1415;

boolean runProgram = true;

void setup()
{
  // Set up the motor pin to be an output:
  pinMode(motorPin, OUTPUT);
  pinMode(potPin, INPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}
void loop()
{
  determineButtonState();
  if(runProgram)
  {
    motorOnThenOffWithSpeed();
  }
  else
  {
    analogWrite(motorPin, 0);
  }
  delay(10);
}

void motorOnThenOffWithSpeed()
{
  potValue = analogRead(potPin);  //Get value(0-1024) of potentiometer
  
  Speed1 = (255)*(potValue/1024);  // between 0 (stopped) and 255 (full speed)
  
  sinY = fabs(sin(sinX * (pi/180)) );  //Sin function smooths out motor speed.
  sinX += 10;
  
  Speed1 *= sinY; //Apply sin function to motor speed.
  int Time1 = 300;  // milliseconds for speed 1
  
  
  analogWrite(motorPin, Speed1);  // turns the motor On
  delay(Time1);                   // delay for onTime milliseconds

  if(sinX > 360)  //Stop sinX from becoming too large.
  {
    sinX = 0;
  }
}

void determineButtonState()
{
  buttonCurrentState = digitalRead(buttonPin);

  if(buttonCurrentState != buttonPreviousState) //If button has been pressed
  {
    if(buttonCurrentState == HIGH && buttonLatch == false)  //Latch button to on
    {
      runProgram = true;
      buttonLatch = true;
    }
    else if (buttonCurrentState == HIGH && buttonLatch == true) //Latch button to off
    {
      runProgram = false;
      buttonLatch = false;
    }
   buttonPreviousState = buttonCurrentState;
    
  }

  
}

