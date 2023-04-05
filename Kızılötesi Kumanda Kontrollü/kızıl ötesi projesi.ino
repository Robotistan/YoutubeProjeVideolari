#include <IRremote.h>
#include <IRremoteInt.h>

const int RECV_PIN = 2;


const int SolMotor1 = 5;
const int SolMotor2 = 6;
const int SolMotorEN = 9;
const int SagMotor1 = 7;
const int SagMotor2 = 8;
const int SagMotorEN = 10;

const int echoPin = 11;
const int trigPin = 12;

int Hiz = 255;

IRrecv irrecv(RECV_PIN);
decode_results results;

#define CH1 0xFFA25D
#define CH 0xFF629D
#define CH2 0xFFE21D
#define PREV 0xFF22DD
#define NEXT 0xFF02FD
#define PLAYPAUSE 0xFFC23D
#define VOL1 0xFFE01F
#define VOL2 0xFFA857
#define EQ 0xFF906F
#define BUTON0 0xFF6897 
#define BUTON100 0xFF9867
#define BUTON200 0xFFB04F
#define BUTON1 0xFF30CF
#define BUTON2 0xFF18E7
#define BUTON3 0xFF7A85
#define BUTON4 0xFF10EF
#define BUTON5 0xFF38C7
#define BUTON6 0xFF5AA5
#define BUTON7 0xFF42BD
#define BUTON8 0xFF4AB5
#define BUTON9 0xFF52AD

void setup()
{
  pinMode(SolMotorEN, OUTPUT);
  pinMode(SagMotorEN, OUTPUT);
  pinMode(SolMotor1, OUTPUT);
  pinMode(SolMotor2, OUTPUT);
  pinMode(SagMotor1, OUTPUT);
  pinMode(SagMotor2, OUTPUT);
  
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

  digitalWrite(SolMotorEN, LOW);
  digitalWrite(SagMotorEN, LOW);
  digitalWrite(SolMotor1, LOW);
  digitalWrite(SagMotor1, LOW);
  digitalWrite(SolMotor2, LOW);
  digitalWrite(SagMotor2, LOW);

  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {
  Serial.println(mesafe());
  if (mesafe() > 10)
  {

    if (irrecv.decode(&results))
    {
      if (Hiz >= 0 && Hiz <= 255 && results.value == VOL1)
      {
        Hiz = Hiz - 50;
        if (Hiz < 0)
        Hiz = 0;
      }
      if (Hiz >= 0 && Hiz <= 255 && results.value == VOL2)
      {
        Hiz = Hiz + 50;
        if (Hiz > 255)
        Hiz = 255;
      }
      if (results.value == BUTON2)
      {
        duzgit();
      }
      if (results.value == BUTON8)
      {
        gerigit();
      }
      if (results.value == BUTON4)
      {
        soladon();
      }
      if (results.value == BUTON6)
      {
        sagadon();
      }
      if (results.value == BUTON0)
      {
        dur();
    }
    irrecv.resume();
    }
  }
  else
  dur();
}

void sol_motor(String dir, int spd)
{
  if ( dir == "ILERI")
  {
    digitalWrite(SolMotor1, HIGH);
    digitalWrite(SolMotor2, LOW);
    analogWrite(SolMotorEN, spd);
  }
  if ( dir == "GERI")
  {
    digitalWrite(SolMotor1, LOW);
    digitalWrite(SolMotor2, HIGH);
    analogWrite(SolMotorEN, spd);
  }
}


void sag_motor(String dir, int spd)
{
  if ( dir == "ILERI")
  {
    digitalWrite(SagMotor1, HIGH);
    digitalWrite(SagMotor2, LOW);
    analogWrite(SagMotorEN, spd);
  }

  if ( dir == "GERI")
  {
    digitalWrite(SagMotor1, LOW);
    digitalWrite(SagMotor2, HIGH);
    analogWrite(SagMotorEN, spd);
  }
}

void duzgit()
{
  sag_motor("ILERI", Hiz);
  sol_motor("ILERI", Hiz);
}
void sagadon()
{
  sag_motor("GERI", Hiz);
  sol_motor("ILERI", Hiz);
}
void gerigit()
{
  sag_motor("GERI", Hiz);
  sol_motor("GERI", Hiz);
}
void soladon()
{
  sag_motor("ILERI", Hiz);
  sol_motor("GERI", Hiz);
}

void dur()
{
  sag_motor("ILERI", 0);
  sol_motor("ILERI", 0);
}


int mesafe()
{
  
const int echoPin = 11;
const int trigPin = 12;
  long duration;
  long int distance;
digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration/58,2;
  delay(50);
  if (distance >= 50)
    return 50;
  return distance;
}
