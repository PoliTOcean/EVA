#define dirPin 2               // Direction PIN
#define stepPin 3              // Step PIN
#define stepsPerRevolution 400 // Number of Steps for a Total Round
#define totalRound 227         // Number of Rounds to drain
#define forwardPin 4           // Status of the command
#define backwardPin 5
#define Enable 6
int presentTotalRound = 0; // Variable in which is stored the actual number of round
bool suca = false;
bool sputa = false;
bool moveON = false;
bool fineCorsaSuca = false;
bool fineCorsaSputa = false;

void setup()
{
  // Declare pins as output:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(forwardPin, INPUT);
  pinMode(backwardPin, INPUT);
  Serial.begin(9600);
}
void loop()
{
  sputa = digitalRead(forwardPin);
  suca = digitalRead(backwardPin);
  if (suca && !sputa)
  {
    digitalWrite(dirPin, LOW);
    digitalWrite(Enable, LOW);
    moveON = true;
    if (fineCorsaSuca)
    {
      fineCorsaSuca = false;
    }
    sucaFun();
  }
  else if (sputa && !suca)
  {
    digitalWrite(dirPin, HIGH);
    digitalWrite(Enable, LOW);
    moveON = true;
    if (fineCorsaSputa)
    {
      fineCorsaSputa = false;
    }
    sputaFun();
  }
  else if ((sputa && suca) || (!sputa && !suca))
  {
    digitalWrite(Enable, HIGH); // Stepper has !Enable
    moveON = false;
  }
  if (presentTotalRound <= totalRound && presentTotalRound >= 0 && moveON)
  {
    // These four lines result in 1 step with the minimum possible of delay:
    if (suca)
      if (presentTotalRound == totalRound)
      {
        fineCorsaSuca = true;
      }
      else
      {
        presentTotalRound++;
        fineCorsaSuca = false;
        fineCorsaSputa = false;
      }
    else if (sputa)
    {
      if (presentTotalRound == 0)
      {
        fineCorsaSputa = true;
      }
      else
      {
        presentTotalRound--;
        fineCorsaSputa = false;
        fineCorsaSuca = false;
      }
    }
  }
}

  void sucaFun(){
    for (int i = 0; i <= stepsPerRevolution; i++)
    {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(400);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(400);
    }
  }

  void sputaFun(){
    for (int i = 0; i <= stepsPerRevolution; i++)
    {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(400);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(400);
    }
  }