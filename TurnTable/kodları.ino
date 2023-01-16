#define EN 8

//Direction pin
#define X_DIR 5

//Step pin
#define X_STP 2

//A498
int delayTime = 4000   //4000 -8000 arası
;
int stps=100;
int potVal;
int potPin = A0;
int top;
void step(boolean dir, byte dirPin, byte stepperPin, int steps)
{
  digitalWrite(dirPin, dir);
  delay(0);
  for (int i = 0; i< steps; i++)
  {
    digitalWrite(stepperPin, HIGH);
    delayMicroseconds(top);
    digitalWrite(stepperPin, LOW);
    delayMicroseconds(top);
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(potPin,INPUT);
  pinMode(X_DIR, OUTPUT); pinMode(X_STP,OUTPUT);
  pinMode(EN, OUTPUT);
  digitalWrite(EN,LOW);
}
void loop()
{
  potVal = analogRead(potPin);
  top = potVal * 4 + delayTime;
  Serial.println(top);
  step(true, X_DIR, X_STP, stps);
  delay(0);
  step(true, X_DIR, X_STP, stps);
  delay(0);
}
